#!/usr/bin/env python3
"""
BinBench CLI — document image binarization, evaluation, and pseudo-weight
generation from the command line.

Powered by the Δoxa Binarization Framework. Released CC0.

A single, self-contained script built on the ``doxapy`` Python bindings. It
replaces the legacy DIBCO command-line utilities with one cross-platform tool:

    binarize   Convert image(s) to binary with any supported algorithm.
    grayscale  Convert color image(s) to grayscale with any supported method.
    evaluate   Score binarized image(s) against a ground truth.
    weights    Generate DIBCO pseudo-F weight files from a ground truth.

Run any command with no arguments (e.g. `binbench binarize`) for its help and the
list of algorithms; `binbench binarize --describe sauvola` describes one algorithm.

Requires Python 3.12+ (the doxapy build targets the stable cp312 ABI) plus
numpy and Pillow. ``doxapy`` is imported normally once installed; until then the
script falls back to a locally built distributable (override with DOXAPY_PATH).
"""

import argparse
import csv
import io
import json
import os
import sys
from pathlib import Path

# Make unicode (Δ, σ, ×, ≤, …) safe to print on legacy Windows consoles.
try:
    sys.stdout.reconfigure(encoding="utf-8")
    sys.stderr.reconfigure(encoding="utf-8")
except Exception:
    pass

APP_NAME = "BinBench CLI"
TAGLINE = "Powered by the Δoxa Binarization Framework — CC0"

# Local fallback for the unpublished doxapy build. Override with DOXAPY_PATH.
DEFAULT_DOXAPY_PATH = r"C:\Users\Brandito\Documents\github\Doxa\Bindings\Python\dist"

IMAGE_EXTS = {".png", ".jpg", ".jpeg", ".bmp", ".tif", ".tiff",
              ".ppm", ".pgm", ".pbm", ".pnm", ".webp", ".gif"}

# PIL modes that are already single-channel: take the channel, skip color→luma.
GRAY_MODES = {"L", "1", "LA", "La", "I", "F"}

# Metrics, in display order, each with a direction (True = higher is better) and a
# one-line gloss. DRDM and pseudo-F-Measure cite the paper that defined them, in the
# same style as the algorithm listing.
METRIC_INFO = [
    ("accuracy", True, "Percent of pixels classified correctly."),
    ("fm", True, "F-Measure — harmonic mean of recall and precision."),
    ("recall", True, "Percent of true foreground pixels recovered."),
    ("precision", True, "Percent of detected foreground pixels that are correct."),
    ("mcc", True, "Matthews correlation coefficient (−1 to 1)."),
    ("psnr", True, "Peak signal-to-noise ratio, in decibels."),
    ("nrm", False, "Negative rate metric — mean false-negative/false-positive rate."),
    ("drdm", False, '"Distance-reciprocal distortion measure for binary document images", 2004.'),
    ("pseudo-fm", True, '"An objective evaluation methodology for document image binarization techniques", 2008.'),
    ("pseudo-precision", True, "Precision weighted toward character strokes."),
    ("pseudo-recall", True, "Recall weighted toward character strokes."),
]
METRIC_NAMES = [m[0] for m in METRIC_INFO]
METRIC_HIGHER = {name: higher for name, higher, _ in METRIC_INFO}  # True = higher is better


# ─── Lazy runtime (doxapy + numpy + Pillow) ──────────────────────────────────
# Imported only when a command actually needs to touch images, so `info` and
# `--help` work with zero heavy dependencies installed.
_RT = {}


def runtime():
    """Return (doxapy, numpy, PIL.Image), importing and caching on first use."""
    if _RT:
        return _RT["doxapy"], _RT["np"], _RT["Image"]

    if sys.version_info < (3, 12):
        sys.exit("BinBench CLI requires Python 3.12+ (doxapy targets the stable cp312 ABI).")

    try:
        import doxapy
    except ImportError:
        dev = os.environ.get("DOXAPY_PATH", DEFAULT_DOXAPY_PATH)
        if dev and os.path.isdir(dev):
            sys.path.insert(0, dev)
        try:
            import doxapy
        except ImportError:
            sys.exit(
                "Could not import 'doxapy'.\n"
                "  • Install it once published:  pip install doxapy\n"
                f"  • Or set DOXAPY_PATH to the doxapy dist folder (tried: {dev})"
            )

    try:
        import numpy as np
        from PIL import Image
    except ImportError as e:
        sys.exit(f"Missing dependency '{e.name}'. Install with:  pip install numpy pillow")

    _RT.update(doxapy=doxapy, np=np, Image=Image)
    return doxapy, np, Image


# ─── Image helpers ───────────────────────────────────────────────────────────

def _as_uint8(np, source):
    """Materialize a writable, C-contiguous uint8 array for doxapy.

    doxapy's nanobind bindings take non-const Pixel8 ndarrays, so the buffer
    must be writable. np.array always copies into a fresh writable buffer
    (np.asarray of a PIL image is read-only) — the same idiom the doxapy tests
    and README use.
    """
    return np.array(source, dtype=np.uint8)


def to_gray(arr3d, gray_name):
    """Convert an RGB/RGBA uint8 array to a 2D grayscale array via doxapy."""
    doxapy, _, _ = runtime()
    algo = getattr(doxapy.GrayscaleAlgorithms, gray_name.upper())
    return doxapy.to_grayscale(algo, arr3d)


def load_gray(path, gray_name):
    """Load any image as a 2D grayscale uint8 array (color → doxapy grayscale)."""
    _, np, Image = runtime()
    img = Image.open(path)
    if img.mode in GRAY_MODES:
        return _as_uint8(np, img if img.mode == "L" else img.convert("L"))
    if img.mode not in ("RGB", "RGBA"):
        img = img.convert("RGB")
    return to_gray(_as_uint8(np, img), gray_name)


def load_color(path):
    """Load an image as a 3D RGB/RGBA uint8 array (already-gray → None)."""
    _, np, Image = runtime()
    img = Image.open(path)
    if img.mode == "L":
        return None  # already grayscale; nothing to convert
    if img.mode not in ("RGB", "RGBA"):
        img = img.convert("RGB")
    return _as_uint8(np, img)


def load_2d(path):
    """Load an image as a single-channel 2D uint8 array (for GT / binary input)."""
    _, np, Image = runtime()
    return _as_uint8(np, Image.open(path).convert("L"))


def save_2d(arr, path):
    _, _, Image = runtime()
    Image.fromarray(arr, "L").save(str(path))


# ─── Path / input helpers ────────────────────────────────────────────────────

def iter_inputs(path_str):
    """Yield image file paths from a file or (non-recursively) a folder."""
    p = Path(path_str)
    if p.is_file():
        return [p]
    if p.is_dir():
        files = sorted(q for q in p.iterdir()
                       if q.is_file() and q.suffix.lower() in IMAGE_EXTS)
        if not files:
            sys.exit(f"No images found in folder: {p}")
        return files
    sys.exit(f"Input not found: {p}")


def resolve_output(in_path, out_arg, suffix, ext, batch):
    """Work out the output file path for a given input under file/folder rules."""
    name = f"{Path(in_path).stem}{suffix}{ext}"
    if out_arg is None:
        return Path(in_path).with_name(name)
    out = Path(out_arg)
    treat_as_dir = batch or out.is_dir() or out_arg.endswith(("/", "\\")) or out.suffix == ""
    if treat_as_dir:
        out.mkdir(parents=True, exist_ok=True)
        return out / name
    out.parent.mkdir(parents=True, exist_ok=True)
    return out


# ─── Parameter parsing ───────────────────────────────────────────────────────

def parse_params(pairs):
    """Build a {name: int|float} parameter dict from -p key=value pairs."""
    params = {}
    for item in pairs or []:
        if "=" not in item:
            sys.exit(f"Bad parameter '{item}'. Use -p name=value (e.g. -p window=25).")
        key, _, val = item.partition("=")
        key, val = key.strip(), val.strip()
        try:
            params[key] = int(val)
        except ValueError:
            try:
                params[key] = float(val)
            except ValueError:
                sys.exit(f"Parameter '{key}' must be a number, got '{val}'.")
    return params


# ─── DIBCO .dat weight files ─────────────────────────────────────────────────

def read_dat(path):
    """Read a DIBCO weight file: whitespace-separated doubles."""
    with open(path, "r") as f:
        return [float(x) for x in f.read().split()]


def write_dat(path, weights):
    """Write weights as whitespace-separated, full-precision doubles (Doxa format)."""
    with open(path, "w") as f:
        f.write(" ".join(repr(float(w)) for w in weights))


# ─── Algorithm metadata (derived from BinBench web reference + algorithms.json) ──
# Each entry: name, year, authors, paper, summary, params=[(name, default, guidance)]
ALGO_INFO = {
    "otsu": {
        "name": "Otsu", "year": 1979, "authors": "N. Otsu",
        "paper": '"A threshold selection method from gray-level histograms," IEEE Trans. SMC, 1979',
        "summary": "Global, parameter-free threshold that maximizes between-class variance of the "
                   "gray-level histogram. Ideal for clean, bimodal documents.",
        "params": [],
    },
    "bernsen": {
        "name": "Bernsen", "year": 1986, "authors": "J. Bernsen",
        "paper": '"Dynamic thresholding of gray-level images," ICPR 1986',
        "summary": "Local contrast method: each pixel's threshold is the midpoint of the local min "
                   "and max, falling back to a global threshold in low-contrast windows.",
        "params": [("window", "25", "Local window size (odd)."),
                   ("threshold", "100", "Global threshold used in low-contrast regions."),
                   ("contrast-limit", "25", "Minimum local contrast required to use the local threshold.")],
    },
    "niblack": {
        "name": "Niblack", "year": 1986, "authors": "W. Niblack",
        "paper": '"An Introduction to Digital Image Processing," Strandberg Publishing, 1986',
        "summary": "The original local adaptive method: threshold = local mean + k·(local standard "
                   "deviation) over a sliding window.",
        "params": [("window", "75", "Local window size (odd)."),
                   ("k", "-0.2", "Weight of the standard deviation in the threshold.")],
    },
    "wellner": {
        "name": "Wellner", "year": 1994, "authors": "P. D. Wellner",
        "paper": '"Interacting with Paper on the DigitalDesk," Ph.D. dissertation, Univ. of Cambridge, 1994 (Ch. 5)',
        "summary": "Single-pass moving-average threshold from the DigitalDesk; marks a pixel "
                   "foreground when it is t% darker than a running average of recent pixels. Very fast.",
        "params": [("s", "auto", "Moving-average stride. Blank = largest power of two ≤ width÷8 (fast shift path)."),
                   ("t", "15", "Percent below the local average to count as foreground.")],
    },
    "sauvola": {
        "name": "Sauvola", "year": 1999, "authors": "J. Sauvola, M. Pietikäinen",
        "paper": '"Adaptive document image binarization," Pattern Recognition, 2000',
        "summary": "The most widely used local method; refines Niblack with a dynamic-range "
                   "normalization term that sharply reduces background noise.",
        "params": [("window", "25", "Local window size (odd)."),
                   ("k", "0.2", "Sensitivity controlling threshold adaptation.")],
    },
    "wolf": {
        "name": "Wolf", "year": 2003, "authors": "C. Wolf, J.-M. Jolion",
        "paper": '"Extraction and Recognition of Artificial Text in Multimedia Documents," Pattern Anal. Appl., 2003',
        "summary": "Sauvola variant that normalizes by the global minimum intensity and maximum local "
                   "standard deviation for better low-contrast handling.",
        "params": [("window", "25", "Local window size (odd)."),
                   ("k", "0.2", "Sensitivity parameter.")],
    },
    "feng": {
        "name": "Feng", "year": 2004, "authors": "M.-L. Feng, Y.-P. Tan",
        "paper": '"Adaptive Binarization Method for Document Image Analysis," ICME 2004',
        "summary": "Local-contrast threshold using mean, std-dev and minimum over a primary window, "
                   "normalized by a secondary-window contrast term. Strong on degraded documents.",
        "params": [("window", "25", "Primary window — 1–2× character size (odd)."),
                   ("secondary-window-multiplier", "3", "Secondary window for Rs, in primary cells across (≥2)."),
                   ("alpha1", "0.12", "Mean weighting (paper: 0.1–0.2)."),
                   ("k1", "0.025", "Contrast coefficient scale (paper: 0.01–0.05)."),
                   ("k2", "0.2", "Minimum coefficient scale (paper: 0.15–0.25)."),
                   ("gamma", "2", "Exponent on the contrast ratio s/Rs."),
                   ("noise-floor", "10", "Lower bound on Rs to suppress noise in blank margins; 0 = paper-faithful.")],
    },
    "gatos": {
        "name": "Gatos", "year": 2006, "authors": "B. Gatos, I. Pratikakis, S. J. Perantonis",
        "paper": '"Adaptive degraded document image binarization," Pattern Recognition, 2006',
        "experimental": True,
        "experimental_note": "The implementation is missing the post-processing steps",
        "summary": "Reconstructs the document background surface and thresholds against it. Built for "
                   "shadows, bleed-through and non-uniform illumination.",
        "params": [("window", "25", "Sauvola window for the rough foreground estimate (odd)."),
                   ("k", "0.2", "Sauvola sensitivity for the rough foreground estimate."),
                   ("glyph", "60", "Estimated character height; background window = glyph×2+1.")],
    },
    "bradley": {
        "name": "Bradley", "year": 2007, "authors": "D. Bradley, G. Roth",
        "paper": '"Adaptive Thresholding Using the Integral Image," J. Graphics Tools, 2007',
        "summary": "Wellner's percent-darker rule with a properly centered integral-image window mean "
                   "— fast and robust to illumination.",
        "params": [("window", "auto", "Local window size. Blank = image width ÷ 8."),
                   ("t", "15", "Percent below the local mean to count as foreground.")],
    },
    "nick": {
        "name": "NICK", "year": 2009, "authors": "K. Khurshid, I. Siddiqi, C. Faure, N. Vincent",
        "paper": '"Comparison of Niblack inspired Binarization methods for ancient documents," SPIE 2009',
        "summary": "Niblack-derived formula tuned for ancient documents, shifting the threshold to cut "
                   "background noise on light images.",
        "params": [("window", "75", "Local window size (odd)."),
                   ("k", "-0.2", "Sensitivity parameter.")],
    },
    "adotsu": {
        "name": "AdOtsu", "year": 2010, "authors": "R. F. Moghaddam, M. Cheriet",
        "paper": '"A multi-scale framework for adaptive binarization of degraded document images," Pattern Recognition, 2010',
        "summary": "Applies Otsu's between-class variance maximization locally within a window, with a "
                   "k factor to adapt to degradation.",
        "params": [("window", "25", "Local window size (odd)."),
                   ("k", "1", "Sensitivity parameter."),
                   ("R", "0.1", "Dynamic-range normalization factor."),
                   ("distance", "auto", "Local search distance. Blank = window ÷ 2.")],
    },
    "su": {
        "name": "Su", "year": 2010, "authors": "B. Su, S. Lu, C. L. Tan",
        "paper": '"Binarization of Historical Document Images Using the Local Maximum and Minimum," DAS 2010',
        "summary": "Three-step pipeline for historical documents that detects stroke edges and "
                   "thresholds using local max/min contrast.",
        "params": [("window", "9", "Local window size (odd)."),
                   ("minN", "9", "Minimum number of foreground neighbors required.")],
    },
    "trsingh": {
        "name": "T.R. Singh", "year": 2011,
        "authors": "T. R. Singh, S. Roy, O. I. Singh, T. Sinam, K. M. Singh",
        "paper": '"A New Local Adaptive Thresholding Technique in Binarization," IJCSI, 2011',
        "summary": "Niblack-family method that swaps the standard deviation for the cheaper mean "
                   "deviation to gain speed.",
        "params": [("window", "25", "Local window size (odd)."),
                   ("k", "0.2", "Sensitivity parameter.")],
    },
    "bataineh": {
        "name": "Bataineh", "year": 2011,
        "authors": "B. Bataineh, S. N. H. S. Abdullah, K. Omar",
        "paper": '"An adaptive local binarization method for document images," 2011',
        "experimental": True,
        "experimental_note": "results do not match the research paper precisely",
        "summary": "Gives good results in practice, but its output does not match the original "
                   "research paper precisely. Parameters are undocumented.",
        "params": [],
    },
    "isauvola": {
        "name": "ISauvola", "year": 2016,
        "authors": "Z. Hadjadj, A. Meziane, Y. Cherfa, M. Cheriet, I. Setitra",
        "paper": '"ISauvola: Improved Sauvola\'s Algorithm for Document Image Binarization," ICIAR 2016',
        "summary": "Wraps Sauvola in a contrast-guided pipeline that suppresses background noise while "
                   "recovering low-contrast text.",
        "params": [("window", "25", "Local window size (odd)."),
                   ("k", "0.2", "Sensitivity parameter.")],
    },
    "wan": {
        "name": "WAN", "year": 2018, "authors": "W. A. Mustafa, M. M. M. A. Kader",
        "paper": '"Binarization of Document Image Using Optimum Threshold Modification," J. Phys.: Conf. Ser., 2018',
        "summary": "Sauvola-family method that boosts the local mean to raise the threshold in "
                   "low-contrast regions and preserve detail.",
        "params": [("window", "25", "Local window size (odd)."),
                   ("k", "0.2", "Sensitivity parameter.")],
    },
    "phansalkar": {
        "name": "Phansalkar", "year": 2011,
        "authors": "N. Phansalkar, S. More, A. Sabale, M. Joshi",
        "paper": '"Adaptive Local Thresholding for Detection of Nuclei in Diversely Stained Cytology Images," ICCSP 2011',
        "summary": "Extends Sauvola with an exponential term that raises the threshold in dark, "
                   "low-contrast regions. Designed for stained color images.",
        "params": [("window", "25", "Local window size (odd)."),
                   ("k", "0.25", "Shape parameter controlling sensitivity."),
                   ("p", "3", "Exponential scaling parameter."),
                   ("q", "10", "Exponential decay parameter.")],
    },
    "xdog": {
        "name": "XDoG", "year": 2012,
        "authors": "H. Winnemöller, J. E. Kyprianidis, S. C. Olsen",
        "paper": '"XDoG: An eXtended difference-of-Gaussians compendium including advanced image stylization," Computers & Graphics, 2012',
        "summary": "Extended Difference-of-Gaussians from image stylization — a sharpened DoG plus soft "
                   "threshold that makes an edge-driven binarizer.",
        "params": [("sigma", "1.0", "Inner Gaussian σ — the finest detail scale."),
                   ("k", "1.8", "Ratio of outer to inner sigma (σ_outer = k·σ)."),
                   ("p", "35", "Edge-sharpening strength; higher exaggerates edges."),
                   ("epsilon", "0.2", "Soft-threshold level on the normalized [0,1] response."),
                   ("phi", "10", "Steepness of the tanh threshold ramp.")],
    },
}

GRAYSCALE_INFO = [
    ("mean", "Average of the channels."),
    ("qt", "Qt's weighted luma (≈ BT.601 with rounded coefficients)."),
    ("bt601", "ITU-R BT.601 luma — standard-definition video weights."),
    ("bt709", "ITU-R BT.709 luma — high-definition video weights."),
    ("bt2100", "ITU-R BT.2100 luma — HDR/UHD weights."),
    ("value", "HSV Value — the maximum channel."),
    ("luster", "Average of the max and min channels (HSL lightness)."),
    ("lightness", "CIE L* perceptual lightness."),
    ("minavg", "Average of the mean and the minimum channel."),
    ("labdist", "Distance in CIE Lab space."),
]

# Algorithms in publication order (used by every listing).
ALGO_ORDER = [
    "otsu", "bernsen", "niblack", "wellner", "sauvola", "wolf", "feng", "gatos",
    "bradley", "nick", "adotsu", "su", "trsingh", "bataineh", "phansalkar", "xdog",
    "isauvola", "wan",
]
ALGO_NAMES = ALGO_ORDER
GRAYSCALE_NAMES = [g[0] for g in GRAYSCALE_INFO]


def is_experimental(key):
    return ALGO_INFO.get(key, {}).get("experimental", False)


# ─── Command: binarize ───────────────────────────────────────────────────────

def cmd_binarize(args):
    if args.describe:                         # --describe <algorithm> → one algorithm
        name = args.describe.lower()
        if name not in ALGO_INFO:
            sys.exit(f"Unknown algorithm '{args.describe}'. Run 'binbench binarize' to list them.")
        _print_algorithm_detail(name)
        return
    if not args.input or not args.algorithm:
        sys.exit("Provide an input image and -a <algorithm>. Run 'binbench binarize' for help.")

    algo = args.algorithm.lower()
    if algo not in ALGO_INFO:
        sys.exit(f"Unknown algorithm '{args.algorithm}'. Run 'binbench binarize' to list algorithms.")

    if is_experimental(algo) and not args.experimental:
        note = ALGO_INFO[algo]["experimental_note"]
        sys.exit(f"'{ALGO_INFO[algo]['name']}' is experimental — {note}.\n"
                 f"Re-run with --experimental to use it.")

    doxapy, _, _ = runtime()
    algo_enum = getattr(doxapy.Binarization.Algorithms, algo.upper())
    params = parse_params(args.param)

    inputs = iter_inputs(args.input)
    batch = len(inputs) > 1 or Path(args.input).is_dir()
    for src in inputs:
        gray = load_gray(src, args.grayscale)
        binary = doxapy.to_binary(algo_enum, gray, params)
        dst = resolve_output(src, args.output, args.suffix, ".png", batch)
        save_2d(binary, dst)
        print(f"{src.name}  →  {dst}")


# ─── Command: grayscale ──────────────────────────────────────────────────────

def cmd_grayscale(args):
    if not args.input or not args.algorithm:
        sys.exit("Provide an input image and -a <method>. Run 'binbench grayscale' for help.")

    gray_name = args.algorithm.lower()
    if gray_name not in GRAYSCALE_NAMES:
        sys.exit(f"Unknown grayscale method '{args.algorithm}'. Run 'binbench grayscale' to list methods.")

    runtime()  # fail fast if deps/doxapy missing
    inputs = iter_inputs(args.input)
    batch = len(inputs) > 1 or Path(args.input).is_dir()
    for src in inputs:
        color = load_color(src)
        gray = load_2d(src) if color is None else to_gray(color, gray_name)
        dst = resolve_output(src, args.output, args.suffix, ".png", batch)
        save_2d(gray, dst)
        print(f"{src.name}  →  {dst}")


# ─── Command: evaluate ───────────────────────────────────────────────────────

def cmd_evaluate(args):
    requested = _resolve_metrics(args.metrics)
    wants_pseudo = any(m.startswith("pseudo") for m in requested)

    doxapy, np, _ = runtime()
    gt = load_2d(args.gt)

    precision_w, recall_w = [], []
    if wants_pseudo:
        if args.pweights and args.rweights:
            precision_w, recall_w = read_dat(args.pweights), read_dat(args.rweights)
        elif args.pweights or args.rweights:
            sys.exit("Pseudo metrics need BOTH --pweights and --rweights, or neither (auto-generate).")
        else:
            precision_w, recall_w = doxapy.generate_pseudo_weights(gt)

    flags = {m.replace("-", "_"): True for m in requested}

    images = []
    for arg in args.results:
        images.extend(iter_inputs(arg))

    rows = []
    for img_path in images:
        binary = load_2d(img_path)
        if binary.shape != gt.shape:
            print(f"! skip {img_path.name}: size {binary.shape[1]}×{binary.shape[0]} "
                  f"≠ ground truth {gt.shape[1]}×{gt.shape[0]}", file=sys.stderr)
            continue
        metrics = doxapy.calculate_performance_ex(
            gt, binary, precision_weights=precision_w, recall_weights=recall_w, **flags)
        row = {"image": img_path.name}
        for m in requested:
            row[m] = metrics.get(m.replace("-", "_"))
        rows.append(row)

    if not rows:
        sys.exit("No images evaluated.")
    _emit_metrics(rows, requested, args.format, args.output, args.delim)


def _resolve_metrics(spec):
    if not spec:                              # -m omitted → report every metric
        return list(METRIC_NAMES)
    out = []
    for raw in spec.split(","):
        m = raw.strip().lower()
        if not m:
            continue
        if m not in METRIC_NAMES:
            sys.exit(f"Unknown metric '{m}'. Valid: {', '.join(METRIC_NAMES)}.")
        out.append(m)
    return out or list(METRIC_NAMES)


def _fmt_metric(name, value):
    if value is None:
        return "—"
    if name == "psnr":
        return f"{value:.4f}"
    if name == "mcc":
        return f"{value:.4f}"
    return f"{value:.4f}"


def _emit_metrics(rows, metrics, fmt, output, delim=","):
    if fmt == "json":
        text = json.dumps(rows, indent=2)
        _write_text(text + "\n", output)
        return
    if fmt == "csv":
        buf = io.StringIO()
        writer = csv.writer(buf, delimiter=delim)
        writer.writerow(["image"] + metrics)
        for r in rows:
            writer.writerow([r["image"]] + [
                ("" if r[m] is None else f"{r[m]:.6f}") for m in metrics])
        _write_text(buf.getvalue(), output)
        return

    # table — flag each metric column with ↑/↓ so good direction is obvious
    headers = ["image"] + [f"{m}{'↑' if METRIC_HIGHER[m] else '↓'}" for m in metrics]
    table = [headers]
    for r in rows:
        table.append([r["image"]] + [_fmt_metric(m, r[m]) for m in metrics])
    widths = [max(len(str(row[i])) for row in table) for i in range(len(headers))]
    lines = []
    for ri, row in enumerate(table):
        cells = [str(c).ljust(widths[0]) if i == 0 else str(c).rjust(widths[i])
                 for i, c in enumerate(row)]
        lines.append("  ".join(cells))
        if ri == 0:
            lines.append("  ".join("-" * widths[i] for i in range(len(headers))))
    _write_text("\n".join(lines) + "\n", output)


def _write_text(text, output):
    if output:
        Path(output).parent.mkdir(parents=True, exist_ok=True)
        Path(output).write_text(text, encoding="utf-8")
        print(f"Wrote {output}")
    else:
        sys.stdout.write(text)


# ─── Command: weights ────────────────────────────────────────────────────────

def cmd_weights(args):
    doxapy, _, _ = runtime()
    for src in iter_inputs(args.input):
        gt = load_2d(src)
        precision_w, recall_w = doxapy.generate_pseudo_weights(gt)
        out_dir = Path(args.output) if args.output else Path(src).parent
        out_dir.mkdir(parents=True, exist_ok=True)
        r_path = out_dir / f"{Path(src).stem}_RWeights.dat"
        p_path = out_dir / f"{Path(src).stem}_PWeights.dat"
        write_dat(r_path, recall_w)      # R = recall
        write_dat(p_path, precision_w)   # P = precision
        print(f"{src.name}  →  {r_path.name}, {p_path.name}  ({len(recall_w)} weights each)")


# ─── Reference output (shown by a bare command or `--help [NAME]`) ───────────

def _paper_title(key):
    """The paper's title alone (the quoted portion of the stored citation)."""
    return ALGO_INFO[key]["paper"].split(',"')[0].lstrip('"')


def _binarize_epilog():
    lines = ["Algorithms (the name you pass to -a):"]
    for k in ALGO_ORDER:
        mark = "  (experimental)" if is_experimental(k) else ""
        lines.append(f'  {k:<12} "{_paper_title(k)}", {ALGO_INFO[k]["year"]}.{mark}')
    lines += [
        "",
        "Experimental algorithms need --experimental to run.",
        "Details for one algorithm (parameters + paper):  binbench binarize --describe <name>",
        "Example:  binbench binarize page.png -a sauvola -p window=25 -p k=0.2",
    ]
    return "\n".join(lines)


def _print_algorithm_detail(key):
    a = ALGO_INFO[key]
    print(f"{a['name']}  ({a['year']})        [name to type: {key}]")
    print()
    print(f"  Authors: {a['authors']}")
    print(f"  Paper:   {a['paper']}")
    if is_experimental(key):
        print(f"  ⚠ Experimental — {a['experimental_note']}. Pass --experimental to run it.")
    print()
    print(f"  {a['summary']}")
    print()
    if a["params"]:
        print("  Parameters:")
        pw = max(len(p[0]) for p in a["params"])
        dw = max(len(p[1]) for p in a["params"])
        for pname, default, guidance in a["params"]:
            print(f"    {pname.ljust(pw)}  (default {default.ljust(dw)})  {guidance}")
        ex = " ".join(f"-p {p[0]}={p[1]}" for p in a["params"] if p[1] != "auto")
        print()
        print(f"  Try:  binbench binarize page.png -a {key} {ex}".rstrip())
    else:
        print("  Parameters: none.")
        print(f"\n  Try:  binbench binarize page.png -a {key}")


def _grayscale_epilog():
    gw = max(len(name) for name, _ in GRAYSCALE_INFO)
    lines = ["Methods (the name you pass to -a):"]
    for name, desc in GRAYSCALE_INFO:
        lines.append(f"  {name.ljust(gw)}  {desc}")
    lines += [
        "",
        "Example:  binbench grayscale page.png -a bt601",
    ]
    return "\n".join(lines)


def _evaluate_epilog():
    mw = max(len(name) for name, _, _ in METRIC_INFO)
    lines = ["Metrics (the name you pass to -m; default is all).",
             "↑ higher is better, ↓ lower is better:"]
    for name, higher_better, desc in METRIC_INFO:
        arrow = "↑" if higher_better else "↓"
        lines.append(f"  {name.ljust(mw)}  {arrow} {desc}")
    lines += [
        "",
        "Pseudo metrics need precision/recall weights (auto-generated, or pass --pweights/--rweights).",
        "Example:  binbench evaluate gt.png result.png -m fm,drdm",
    ]
    return "\n".join(lines)


# ─── Argument parsing ────────────────────────────────────────────────────────

def build_parser():
    parser = argparse.ArgumentParser(
        prog="binbench",
        description=f"{APP_NAME} — {TAGLINE}",
        epilog="Run a command with no arguments to see its help, e.g. 'binbench binarize'.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        add_help=False,   # the help is the bare command; no -h noise anywhere
    )
    sub = parser.add_subparsers(dest="command", metavar="<command>")

    raw = argparse.RawDescriptionHelpFormatter

    # binarize
    b = sub.add_parser("binarize", help="Convert image(s) to binary.", formatter_class=raw,
                       add_help=False, description="Convert document image(s) to black & white.",
                       usage=("binbench binarize <input> -a <algorithm> [-o OUTPUT] [-p KEY=VALUE]\n"
                              "                         [-g METHOD] [--suffix SUFFIX] [--experimental]\n"
                              "                         [--describe ALGORITHM]"),
                       epilog=_binarize_epilog())
    b.add_argument("input", nargs="?", help="Input image file or folder.")
    b.add_argument("-o", "--output", help="Output file or folder (default: alongside input).")
    b.add_argument("-a", "--algorithm", help="Binarization algorithm (run 'binbench binarize' to list).")
    b.add_argument("-p", "--param", action="append", metavar="KEY=VALUE",
                   help="Algorithm parameter, repeatable (e.g. -p window=25 -p k=0.2).")
    b.add_argument("-g", "--grayscale", default="mean", metavar="METHOD",
                   help="Grayscale method for color input (default: mean).")
    b.add_argument("--suffix", default="_bin", help="Output filename suffix (default: _bin).")
    b.add_argument("--experimental", action="store_true",
                   help="Enable experimental algorithms.")
    b.add_argument("--describe", metavar="ALGORITHM",
                   help="Print one algorithm's parameters and paper, then exit.")
    b.set_defaults(func=cmd_binarize)

    # grayscale
    g = sub.add_parser("grayscale", help="Convert color image(s) to grayscale.", formatter_class=raw,
                       add_help=False, description="Convert color image(s) to grayscale.",
                       usage="binbench grayscale <input> -a <method> [-o OUTPUT] [--suffix SUFFIX]",
                       epilog=_grayscale_epilog())
    g.add_argument("input", nargs="?", help="Input image file or folder.")
    g.add_argument("-o", "--output", help="Output file or folder (default: alongside input).")
    g.add_argument("-a", "--algorithm", help="Grayscale method (run 'binbench grayscale' to list).")
    g.add_argument("--suffix", default="_gray", help="Output filename suffix (default: _gray).")
    g.set_defaults(func=cmd_grayscale)

    # evaluate
    e = sub.add_parser("evaluate", help="Score binarized image(s) against a ground truth.",
                       add_help=False, formatter_class=raw, epilog=_evaluate_epilog(),
                       usage=("binbench evaluate <gt> <results...> [-m METRICS] [--pweights PWEIGHTS]\n"
                              "                         [--rweights RWEIGHTS] [--format {table,csv,json} [--delim CHAR]] [-o OUTPUT]"))
    e.add_argument("gt", help="Ground truth (bilevel) image.")
    e.add_argument("results", nargs="+", help="Binarized result image(s) or folder(s) to score.")
    e.add_argument("-m", "--metrics", default=None,
                   help="Comma list of metrics to report (default: all; run "
                        "'binbench evaluate' to list them).")
    e.add_argument("--pweights", help="Precision weight .dat (pseudo metrics).")
    e.add_argument("--rweights", help="Recall weight .dat (pseudo metrics).")
    e.add_argument("--format", choices=["table", "csv", "json"], default="table",
                   help="Output format (default: table).")
    e.add_argument("--delim", default=",", metavar="CHAR",
                   help="Field delimiter for --format csv (default: ','; use ';' for DIBCO/locale CSV).")
    e.add_argument("-o", "--output", help="Write output to a file instead of stdout.")
    e.set_defaults(func=cmd_evaluate)

    # weights
    w = sub.add_parser("weights", help="Generate pseudo-F weight files from a ground truth.",
                       add_help=False, usage="binbench weights <input> [-o OUTPUT]")
    w.add_argument("input", help="Ground truth image file or folder.")
    w.add_argument("-o", "--output", help="Output folder (default: alongside input).")
    w.set_defaults(func=cmd_weights)

    return parser, {"binarize": b, "grayscale": g, "evaluate": e, "weights": w}


def main(argv=None):
    argv = list(sys.argv[1:] if argv is None else argv)
    parser, subs = build_parser()
    # The whole help model: nothing, or a lone verb, prints help; anything else runs.
    if not argv:
        parser.print_help()
    elif len(argv) == 1 and argv[0] in subs:
        subs[argv[0]].print_help()
    else:
        args = parser.parse_args(argv)
        try:
            args.func(args)
        except FileNotFoundError as e:
            sys.exit(f"File not found: {e.filename}")
        except OSError as e:
            # Unreadable/unwritable path or a file that isn't a valid image
            # (PIL's UnidentifiedImageError, permissions, etc. are all OSError).
            sys.exit(f"Could not process file: {e}")
    print()  # trailing blank line so output doesn't butt against the next prompt


if __name__ == "__main__":
    main()
