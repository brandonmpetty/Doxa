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

Exit status: 0 on success; 1 on any error or partial result (some images
skipped or failed); 2 on a command-line usage error.

Requires Python 3.12+ (the doxapy build targets the stable cp312 ABI) plus
numpy and Pillow. ``doxapy`` is imported normally once installed; to run against a
local, unpublished build, set the DOXAPY_PATH environment variable to its dist
folder — it takes precedence over any pip-installed copy.
"""

import argparse
import csv
import errno
import functools
import glob
import io
import json
import os
import re
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

IMAGE_EXTS = {".png", ".jpg", ".jpeg", ".bmp", ".tif", ".tiff",
              ".ppm", ".pgm", ".pbm", ".pnm", ".webp", ".gif"}

# PIL modes that are already single-channel: take the channel, skip color→luma.
# (High-depth modes like I;16 are rescaled to L by _open_image before this check.)
GRAY_MODES = {"L", "1", "LA", "La"}


# ─── Reference data: metrics, algorithms, grayscale methods ─────────────────

# Metrics, in display order, each with a direction (True = higher is better)
# and a one-line gloss; DRDM and pseudo-FM name their defining paper.
METRIC_INFO = [
    ("accuracy", True, "Percent of pixels classified correctly."),
    ("fm", True, "F-Measure — harmonic mean of recall and precision."),
    ("recall", True, "Percent of true foreground pixels recovered."),
    ("precision", True, "Percent of detected foreground pixels that are correct."),
    ("mcc", True, "Matthews correlation coefficient (−1 to 1)."),
    ("psnr", True, "Peak signal-to-noise ratio, in decibels."),
    ("nrm", False, "Negative rate metric — mean false-negative/false-positive rate."),
    ("drdm", False, "Distance-Reciprocal Distortion Measure (Lu et al., 2004) — perceptual distortion."),
    ("pseudo-fm", True, "Stroke-weighted F-Measure (Ntirogiannis et al., 2008)."),
    ("pseudo-precision", True, "Precision weighted toward character strokes."),
    ("pseudo-recall", True, "Recall weighted toward character strokes."),
]
METRIC_NAMES = [m[0] for m in METRIC_INFO]
METRIC_HIGHER = {name: higher for name, higher, _ in METRIC_INFO}  # True = higher is better

# Algorithm metadata (derived from BinBench web reference + algorithms.json).
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
        "name": "Sauvola", "year": 2000, "authors": "J. Sauvola, M. Pietikäinen",
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
        "experimental_note": "the implementation is missing the paper's post-processing steps",
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
        "experimental": True,
        "experimental_note": "under review for paper correctness; default parameters are likely correct, but k ≠ 1 may be off",
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
GRAYSCALE_NAMES = [g[0] for g in GRAYSCALE_INFO]


def _is_experimental(key):
    return ALGO_INFO.get(key, {}).get("experimental", False)


# ─── Lazy runtime (doxapy + numpy + Pillow) ──────────────────────────────────
# Imported only when a command actually touches images, so bare-command help
# and the reference listings work with zero heavy dependencies installed.

@functools.cache
def _runtime():
    """Import and return (doxapy, numpy, PIL.Image); cached after the first call."""
    if sys.version_info < (3, 12):
        sys.exit("BinBench CLI requires Python 3.12+ (doxapy targets the stable cp312 ABI).")

    dev = os.environ.get("DOXAPY_PATH")
    if dev:
        if not os.path.isdir(dev):
            sys.exit(f"DOXAPY_PATH is not a folder: {dev}")
        sys.path.insert(0, dev)  # a local dev build outranks any pip-installed doxapy

    try:
        import doxapy
    except ImportError as e:
        sys.exit(
            f"Could not import 'doxapy' ({e}).\n"
            "  • Install it once published:  pip install doxapy\n"
            "  • Or set the DOXAPY_PATH environment variable to a local doxapy build (dist) folder."
        )

    try:
        import numpy as np
        from PIL import Image
    except ImportError as e:
        sys.exit(f"Missing dependency '{e.name}'. Install with:  pip install numpy pillow")

    return doxapy, np, Image


# ─── Image helpers ───────────────────────────────────────────────────────────

def _as_uint8(source):
    """Materialize a writable, C-contiguous uint8 array for doxapy.

    doxapy's nanobind bindings take non-const Pixel8 ndarrays, so the buffer
    must be writable. np.array always copies into a fresh writable buffer
    (np.asarray of a PIL image is read-only) — the same idiom the doxapy tests
    and README use.
    """
    _, np, _ = _runtime()
    return np.array(source, dtype=np.uint8)


def _open_image(path):
    """Open an image, normalizing the modes PIL's convert() mishandles.

    Palette images honor their transparency (instead of exposing the palette
    slot's opaque color), and 16/32-bit grayscale is rescaled to 8 bits
    (convert("L") would clip everything above 255).
    """
    _, np, Image = _runtime()
    img = Image.open(path)
    if img.mode == "P":
        img = img.convert("RGBA" if "transparency" in img.info else "RGB")
    elif img.mode == "F":
        raise OSError(errno.EINVAL, "32-bit float images are not supported; "
                                    "convert the image to 8- or 16-bit first", str(path))
    elif img.mode.startswith("I"):
        arr = (np.clip(np.asarray(img, dtype=np.int64), 0, 65535) * 255 + 32767) // 65535
        img = Image.fromarray(arr.astype(np.uint8))
    return img


def _to_gray(arr3d, gray_name):
    """Convert an RGB/RGBA uint8 array to a 2D grayscale array via doxapy."""
    doxapy, _, _ = _runtime()
    algo = getattr(doxapy.GrayscaleAlgorithms, gray_name.upper())
    return doxapy.to_grayscale(algo, arr3d)


def _load_gray(path, gray_name):
    """Load any image as a 2D grayscale uint8 array (color → doxapy grayscale)."""
    img = _open_image(path)
    if img.mode in GRAY_MODES:
        return _as_uint8(img if img.mode == "L" else img.convert("L"))
    if img.mode not in ("RGB", "RGBA"):
        img = img.convert("RGB")
    return _to_gray(_as_uint8(img), gray_name)


def _load_color(path):
    """Load an image as a 3D RGB/RGBA uint8 array (already-gray → None)."""
    img = _open_image(path)
    if img.mode in GRAY_MODES:
        return None  # already single-channel; nothing to convert
    if img.mode not in ("RGB", "RGBA"):
        img = img.convert("RGB")
    return _as_uint8(img)


def _load_2d(path):
    """Load an image as a single-channel 2D uint8 array (for GT / binary input)."""
    return _as_uint8(_open_image(path).convert("L"))


def _bilevel_problem(arr):
    """Return None when arr is bilevel (only 0/255), else a short diagnosis.

    The C++ comparison counts a pixel as ink only when it is exactly 0 and as
    correct only on exact byte equality, so anything in between — JPEG
    artifacts, anti-aliased edges, 0/1-valued data — silently scores as a
    near-total mismatch. Better to refuse it here. Callers add the remedy,
    which differs for ground truths and results.
    """
    _, np, _ = _runtime()
    if bool(((arr == 0) | (arr == 255)).all()):
        return None
    values = np.unique(arr)
    head = ", ".join(map(str, values[:6])) + (", …" if values.size > 6 else "")
    return f"{values.size} gray levels ({head})"


def _save_2d(arr, path):
    _, _, Image = _runtime()
    Image.fromarray(arr).save(str(path))


# ─── Path / input helpers ────────────────────────────────────────────────────

def _collect_inputs(path_str, required=True):
    """Return image file paths from a file, a folder (non-recursive), or a glob.

    Globs are expanded here because Windows shells pass wildcards through
    verbatim. With required=False an empty folder is a warning instead of an
    error, so a multi-folder evaluate can keep going.
    """
    p = Path(path_str)
    if p.is_file():
        return [p]
    if p.is_dir():
        files = sorted(q for q in p.iterdir()
                       if q.is_file() and q.suffix.lower() in IMAGE_EXTS)
        if not files:
            if required:
                sys.exit(f"No images found in folder: {p}")
            print(f"! no images found in folder: {p}", file=sys.stderr)
        return files
    matches = [Path(m) for m in sorted(glob.glob(path_str))]
    files = [m for m in matches if m.is_file() and m.suffix.lower() in IMAGE_EXTS]
    if files:
        return files
    sys.exit(f"No images match: {path_str}" if matches else f"Input not found: {path_str}")


def _resolve_output(in_path, out_arg, suffix, ext, batch):
    """Work out the output file path for a given input under file/folder rules.

    -o is a folder when it already exists as one, ends with a path separator,
    or we are in batch mode (where it must be a folder). A lone extension-less
    name is refused as ambiguous rather than guessed at. Whatever the rules
    yield, the input file itself is never overwritten.
    """
    in_path = Path(in_path)
    name = f"{in_path.stem}{suffix}{ext}"
    if out_arg is None:
        out = in_path.with_name(name)
    else:
        out = Path(out_arg)
        if batch and out.suffix and not out.is_dir():
            sys.exit(f"-o must be a folder when processing multiple images: {out_arg}")
        if batch or out.is_dir() or out_arg.endswith(("/", "\\")):
            out.mkdir(parents=True, exist_ok=True)
            out = out / name
        elif out.suffix:
            out.parent.mkdir(parents=True, exist_ok=True)
        else:
            sys.exit(f"Ambiguous output '{out_arg}': add a file extension to write a file, "
                     f"or a trailing '{os.sep}' to write into a folder.")
    if out.resolve() == in_path.resolve():
        sys.exit(f"Refusing to overwrite the input: {in_path} — use -o or a non-empty --suffix.")
    return out


# ─── Parameter parsing ───────────────────────────────────────────────────────

def _parse_params(pairs):
    """Build a {name: int|float} parameter dict from -p key=value pairs."""
    params = {}
    for item in pairs or []:
        if "=" not in item:
            sys.exit(f"Invalid parameter '{item}'. Use -p name=value (e.g. -p window=25).")
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

def _read_dat(path):
    """Read a DIBCO weight file: whitespace-separated doubles."""
    try:
        with open(path, "r") as f:
            return [float(x) for x in f.read().split()]
    except ValueError:  # also covers UnicodeDecodeError for binary junk
        sys.exit(f"{path}: not a weight file (expected whitespace-separated numbers).")


def _write_dat(path, weights):
    """Write weights as whitespace-separated, full-precision doubles (Doxa format)."""
    with open(path, "w") as f:
        f.write(" ".join(repr(float(w)) for w in weights))


# ─── Command: binarize ───────────────────────────────────────────────────────

def _drop_prior_outputs(inputs, input_arg, suffix):
    """Drop this tool's earlier outputs (files already carrying the suffix) from a folder scan.

    Without this, re-running over the same folder re-binarizes its own results
    into e.g. page_bin_bin.png.
    """
    if not suffix or not Path(input_arg).is_dir():
        return inputs
    kept = [p for p in inputs if not p.stem.endswith(suffix)]
    if len(kept) != len(inputs):
        print(f"! ignoring {len(inputs) - len(kept)} '*{suffix}' file(s) from an earlier run",
              file=sys.stderr)
        if not kept:
            sys.exit(f"No images to process: {input_arg} contains only '*{suffix}' outputs.")
    return kept


def _process_images(args, convert):
    """Convert each input with convert(src) and save it under the output rules.

    A file that fails to load or convert is reported and skipped so one bad
    image cannot abort a batch; any failure makes the exit code non-zero.
    """
    inputs = _drop_prior_outputs(_collect_inputs(args.input), args.input, args.suffix)
    batch = len(inputs) > 1 or Path(args.input).is_dir()
    failures = 0
    for src in inputs:
        dst = _resolve_output(src, args.output, args.suffix, ".png", batch)
        try:
            _save_2d(convert(src), dst)
        except OSError as e:
            failures += 1
            print(f"! {src.name}: {e.strerror or e}", file=sys.stderr)
            continue
        print(f"{src.name}  →  {dst}")
    if failures:
        sys.exit(f"{failures} of {len(inputs)} image(s) failed.")


def cmd_binarize(args):
    if args.describe:                         # --describe <algorithm> → one algorithm
        name = args.describe.lower()
        if name not in ALGO_INFO:
            sys.exit(f"Unknown algorithm '{args.describe}'. Run 'binbench binarize' to list algorithms.")
        _print_algorithm_detail(name)
        return
    if not args.input or not args.algorithm:
        sys.exit("Provide an input image and -a <algorithm>. Run 'binbench binarize' for help.")

    algo = args.algorithm.lower()
    if algo not in ALGO_INFO:
        sys.exit(f"Unknown algorithm '{args.algorithm}'. Run 'binbench binarize' to list algorithms.")

    gray_name = args.grayscale.lower()
    if gray_name not in GRAYSCALE_NAMES:
        sys.exit(f"Unknown grayscale method '{args.grayscale}'. Run 'binbench grayscale' to list methods.")

    if _is_experimental(algo) and not args.experimental:
        note = ALGO_INFO[algo]["experimental_note"]
        sys.exit(f"'{ALGO_INFO[algo]['name']}' is experimental — {note}.\n"
                 f"Re-run with --experimental to use it.")

    params = _parse_params(args.param)
    known = [p[0] for p in ALGO_INFO[algo]["params"]]
    unknown = [k for k in params if k not in known]
    if unknown:
        detail = f"Valid: {', '.join(known)}" if known else "It takes no parameters"
        sys.exit(f"Unknown parameter(s) for {ALGO_INFO[algo]['name']}: {', '.join(unknown)}.\n"
                 f"{detail} — see 'binbench binarize --describe {algo}'.")

    doxapy, _, _ = _runtime()
    algo_enum = getattr(doxapy.Binarization.Algorithms, algo.upper())
    _process_images(args, lambda src: doxapy.to_binary(algo_enum, _load_gray(src, gray_name), params))


# ─── Command: grayscale ──────────────────────────────────────────────────────

def cmd_grayscale(args):
    if not args.input or not args.algorithm:
        sys.exit("Provide an input image and -a <method>. Run 'binbench grayscale' for help.")

    gray_name = args.algorithm.lower()
    if gray_name not in GRAYSCALE_NAMES:
        sys.exit(f"Unknown grayscale method '{args.algorithm}'. Run 'binbench grayscale' to list methods.")

    _runtime()  # fail fast if deps/doxapy missing

    def convert(src):
        color = _load_color(src)
        return _load_2d(src) if color is None else _to_gray(color, gray_name)

    _process_images(args, convert)


# ─── Command: evaluate ───────────────────────────────────────────────────────

def _load_weights(path, pixel_count):
    """Read a weight .dat, requiring exactly one weight per ground-truth pixel.

    The C++ comparison indexes the weights by pixel, so a file generated from
    a different image would read out of bounds.
    """
    weights = _read_dat(path)
    if len(weights) != pixel_count:
        sys.exit(f"{path}: {len(weights)} weights for a {pixel_count}-pixel ground truth — "
                 f"was it generated from a different image?")
    return weights


def cmd_evaluate(args):
    requested = _resolve_metrics(args.metrics)
    wants_pseudo = any(m.startswith("pseudo") for m in requested)

    doxapy, _, _ = _runtime()
    gt = _load_2d(args.gt)
    problem = _bilevel_problem(gt)
    if problem:
        sys.exit(f"Ground truth {args.gt} is not bilevel — {problem}. "
                 f"Expected only pure black (0) and white (255).")

    precision_w, recall_w = [], []
    if wants_pseudo:
        if args.pweights and args.rweights:
            precision_w = _load_weights(args.pweights, gt.size)
            recall_w = _load_weights(args.rweights, gt.size)
        elif args.pweights or args.rweights:
            sys.exit("Pseudo metrics require both --pweights and --rweights; "
                     "omit both to generate weights from the ground truth.")
        else:
            precision_w, recall_w = doxapy.generate_pseudo_weights(gt)

    flags = {m.replace("-", "_"): True for m in requested}

    images = []
    for arg in args.results:
        images.extend(_collect_inputs(arg, required=False))

    rows, skipped = [], 0
    for img_path in images:
        try:
            binary = _load_2d(img_path)
        except OSError as e:
            print(f"! {img_path.name}: {e.strerror or e}", file=sys.stderr)
            skipped += 1
            continue
        if binary.shape != gt.shape:
            print(f"! {img_path.name}: size {binary.shape[1]}×{binary.shape[0]} "
                  f"≠ ground truth {gt.shape[1]}×{gt.shape[0]}", file=sys.stderr)
            skipped += 1
            continue
        problem = _bilevel_problem(binary)
        if problem:
            print(f"! {img_path.name}: not bilevel — {problem}; binarize it first",
                  file=sys.stderr)
            skipped += 1
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
    if skipped:  # partial evaluation — make it visible to CI via the exit code
        sys.exit(f"Skipped {skipped} of {len(images)} image(s) — see warnings above.")


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


def _fmt_metric(value):
    return "—" if value is None else f"{value:.4f}"


def _emit_metrics(rows, metrics, fmt, output, delim=","):
    if fmt == "json":
        text = json.dumps(rows, indent=2)
        _write_text(text + "\n", output)
        return
    if fmt == "csv":
        buf = io.StringIO()
        # csv defaults to \r\n row endings, which text-mode output would
        # expand again to \r\r\n on Windows — emit \n and let the stream
        # apply the platform convention once.
        writer = csv.writer(buf, delimiter=delim, lineterminator="\n")
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
        table.append([r["image"]] + [_fmt_metric(r[m]) for m in metrics])
    widths = [max(len(str(row[i])) for row in table) for i in range(len(headers))]
    lines = []
    for ri, row in enumerate(table):
        cells = [str(c).ljust(widths[0]) if i == 0 else str(c).rjust(widths[i])
                 for i, c in enumerate(row)]
        lines.append("  ".join(cells))
        if ri == 0:
            lines.append("  ".join("-" * widths[i] for i in range(len(headers))))
    _write_text("\n".join(lines) + "\n", output)


def _write_text(text, path):
    if path:
        Path(path).parent.mkdir(parents=True, exist_ok=True)
        Path(path).write_text(text, encoding="utf-8")
        print(f"Wrote {path}")
    else:
        sys.stdout.write(text)


# ─── Command: weights ────────────────────────────────────────────────────────

def cmd_weights(args):
    doxapy, _, _ = _runtime()
    inputs = _collect_inputs(args.input)
    failures = 0
    for src in inputs:
        try:
            gt = _load_2d(src)
        except OSError as e:
            print(f"! {src.name}: {e.strerror or e}", file=sys.stderr)
            failures += 1
            continue
        problem = _bilevel_problem(gt)
        if problem:
            print(f"! {src.name}: not bilevel — {problem}", file=sys.stderr)
            failures += 1
            continue
        precision_w, recall_w = doxapy.generate_pseudo_weights(gt)
        out_dir = Path(args.output) if args.output else src.parent
        out_dir.mkdir(parents=True, exist_ok=True)
        r_path = out_dir / f"{src.stem}_RWeights.dat"
        p_path = out_dir / f"{src.stem}_PWeights.dat"
        _write_dat(r_path, recall_w)      # R = recall
        _write_dat(p_path, precision_w)   # P = precision
        print(f"{src.name}  →  {r_path.name}, {p_path.name}  ({len(recall_w)} weights each)")
    if failures:
        sys.exit(f"{failures} of {len(inputs)} image(s) failed.")


# ─── Reference output (shown by a bare command or `--help [NAME]`) ───────────

def _paper_title(key):
    """The paper's title alone (the quoted portion of the stored citation)."""
    citation = ALGO_INFO[key]["paper"]
    match = re.match(r'"(.+?),?"', citation)
    return match.group(1) if match else citation


def _binarize_epilog():
    lines = ["Algorithms (the name you pass to -a):"]
    for k in ALGO_ORDER:
        mark = "  (experimental)" if _is_experimental(k) else ""
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
    if _is_experimental(key):
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

def _delim_char(text):
    """argparse type for --delim: exactly one character ('\\t' means a tab)."""
    if text == "\\t":
        return "\t"
    if len(text) != 1:
        raise argparse.ArgumentTypeError("must be a single character")
    return text


def _build_parser():
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
    e.add_argument("--pweights", help="Precision weights — the *_PWeights.dat file (pseudo metrics).")
    e.add_argument("--rweights", help="Recall weights — the *_RWeights.dat file (pseudo metrics).")
    e.add_argument("--format", choices=["table", "csv", "json"], default="table",
                   help="Output format (default: table).")
    e.add_argument("--delim", default=",", metavar="CHAR", type=_delim_char,
                   help="Field delimiter for --format csv (default: ','; use ';' for "
                        "DIBCO-style CSV, '\\t' for tabs).")
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
    parser, subs = _build_parser()
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
            sys.exit(f"File not found: {e.filename or e}")
        except OSError as e:
            # Unreadable/unwritable paths and invalid images (PIL's
            # UnidentifiedImageError, permission errors) are all OSError.
            if e.filename and e.strerror:
                sys.exit(f"Could not process {e.filename}: {e.strerror}")
            sys.exit(f"Could not process file: {e}")
    if sys.stdout.isatty():
        print()  # spacer for interactive use; piped/redirected output stays byte-clean


if __name__ == "__main__":
    main()
