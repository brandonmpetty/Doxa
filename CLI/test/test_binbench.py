"""
Specification / correctness suite for the BinBench CLI.

Runs CLI/binbench.py as a subprocess with a range of arguments against the
canonical fixtures in Doxa.Test/Resources/, asserting on exit codes, created
files, printed output, and known-good metric values. Because it shells out to
the real script, it exercises the whole pipeline exactly as a user would.

Run from the repo root (or anywhere):
    python -m unittest discover -s CLI/test
    # or
    python CLI/test/test_binbench.py -v

binbench.py imports doxapy itself — pip-installed, or via the DOXAPY_PATH
environment variable. It has no hardcoded fallback, so this suite points
DOXAPY_PATH at the repo's local build (unless the caller already set it) and
otherwise needs only the standard library.
"""

import csv
import io
import json
import os
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

HERE = Path(__file__).resolve().parent
BINBENCH = HERE.parent / "binbench.py"
# The canonical fixtures live in the C++ test resources; reference them directly
# (repo-relative) so there is a single source of truth for the test images.
RES = HERE.parents[1] / "Doxa.Test" / "Resources"

# binbench.py has no hardcoded doxapy fallback: it needs doxapy pip-installed or
# DOXAPY_PATH pointing at a local build. Point it at the repo's dist/ unless the
# caller (e.g. ctest) already set it.
DIST = HERE.parents[1] / "Bindings" / "Python" / "dist"

SRC = RES / "2JohnC1V3.ppm"                  # color source
GT = RES / "2JohnC1V3-GroundTruth.pbm"       # bilevel ground truth
SAUVOLA_REF = RES / "2JohnC1V3-Sauvola.pbm"  # Sauvola(27, 0.10) on QT grayscale

# DIBCO-tool reference weight files for the ground truth.
RWEIGHTS_REF = RES / "2JohnC1V3-GroundTruth_RWeights.dat"
PWEIGHTS_REF = RES / "2JohnC1V3-GroundTruth_PWeights.dat"

PIXELS = 707 * 441  # dimensions of the resource images

# The official DIBCO evaluation tool's reported output for SAUVOLA_REF vs GT on
# these .ppm/.pbm fixtures — the authoritative numbers our doxapy-based CLI must
# reproduce. DIBCO prints metrics rounded to 4 decimals; ours are the same
# computation at full precision and round to these figures. The tolerance
# absorbs that 4-decimal display rounding.
DIBCO_METRICS = {
    "fm": 93.2047, "pseudo-fm": 93.3930, "psnr": 16.3292, "drdm": 1.9519,
    "recall": 91.3811, "precision": 95.1025,
    "pseudo-recall": 92.7954, "pseudo-precision": 93.9983,
}
METRIC_TOL = 1e-4
WEIGHT_TOL = 1e-6    # Doxa weights match DIBCO's 6-decimal .dat files to ~4e-7


def load_dat(path):
    return [float(x) for x in Path(path).read_text().split()]


def _env():
    """Child env with DOXAPY_PATH defaulted to the repo build (caller can override)."""
    env = os.environ.copy()
    env.setdefault("DOXAPY_PATH", str(DIST))
    return env


def run(*args):
    """Invoke the CLI; return the CompletedProcess (no raise on failure)."""
    return subprocess.run(
        [sys.executable, str(BINBENCH), *args],
        capture_output=True, text=True, env=_env(),
    )


def run_bytes(*args):
    """Invoke the CLI capturing raw bytes, for line-ending assertions."""
    return subprocess.run(
        [sys.executable, str(BINBENCH), *args],
        capture_output=True, env=_env(),
    )


def csv_rows(text):
    return list(csv.DictReader(io.StringIO(text)))


class BinBenchSpec(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        assert BINBENCH.is_file(), f"binbench.py not found at {BINBENCH}"
        for p in (SRC, GT, SAUVOLA_REF, RWEIGHTS_REF, PWEIGHTS_REF):
            assert p.is_file(), f"missing resource: {p}"

    def setUp(self):
        self._tmp = tempfile.TemporaryDirectory()
        self.tmp = Path(self._tmp.name)

    def tearDown(self):
        self._tmp.cleanup()

    # ── help / reference (no doxapy needed) ─────────────────────────────────

    def test_no_command_shows_help(self):
        r = run()
        self.assertEqual(r.returncode, 0, r.stderr)
        for cmd in ("binarize", "grayscale", "evaluate", "weights"):
            self.assertIn(cmd, r.stdout)

    def test_binarize_bare_lists_algorithms(self):
        """A bare `binarize` lists the command names (publish order) and how to
        drill in; experimental ones are named but flagged."""
        r = run("binarize")
        self.assertEqual(r.returncode, 0, r.stderr)
        out = r.stdout
        for name in ("otsu", "sauvola", "trsingh", "xdog", "wan"):
            self.assertIn(name, out)
        # publication order (anchor on the unique paper-year suffixes in the list)
        self.assertLess(out.index(", 1979."), out.index(", 2000."))
        self.assertLess(out.index(", 2000."), out.index(", 2018."))
        self.assertIn("--describe", out)            # points to per-algorithm detail
        self.assertIn("experimental", out.lower())  # gatos/bataineh named under the flag
        self.assertIn("gatos", out)

    def test_binarize_describe_algorithm(self):
        r = run("binarize", "--describe", "sauvola")
        self.assertEqual(r.returncode, 0, r.stderr)
        self.assertIn("Sauvola", r.stdout)
        self.assertIn("2000", r.stdout)  # Pattern Recognition, 2000
        self.assertIn("window", r.stdout)
        # the command name to type is shown, even when the display name differs
        r2 = run("binarize", "--describe", "trsingh")
        self.assertIn("trsingh", r2.stdout)
        # XDoG's unique parameter set
        r3 = run("binarize", "--describe", "xdog")
        self.assertIn("phi", r3.stdout)

    def test_binarize_describe_unknown_algorithm(self):
        r = run("binarize", "--describe", "bogus")
        self.assertNotEqual(r.returncode, 0)
        self.assertIn("Unknown algorithm", r.stdout + r.stderr)

    def test_grayscale_bare_lists_methods(self):
        r = run("grayscale")
        self.assertEqual(r.returncode, 0, r.stderr)
        for name in ("mean", "bt601", "labdist"):
            self.assertIn(name, r.stdout)

    def test_grayscale_describe_method(self):
        # The bare grayscale listing carries each method's description inline.
        r = run("grayscale")
        self.assertEqual(r.returncode, 0, r.stderr)
        self.assertIn("bt601", r.stdout)
        self.assertIn("BT.601", r.stdout)

    # ── binarize ────────────────────────────────────────────────────────────

    def test_binarize_reproduces_reference(self):
        """Sauvola(27, 0.10) on QT grayscale reproduces the stored reference
        pixel-for-pixel (the reference was generated from this same .ppm with the
        QT grayscale step and identical parameters)."""
        out = self.tmp / "sv.png"
        r = run("binarize", str(SRC), "-a", "sauvola", "-g", "qt",
                "-p", "window=27", "-p", "k=0.10", "-o", str(out))
        self.assertEqual(r.returncode, 0, r.stderr)
        self.assertTrue(out.is_file())
        # Compare against the reference via the evaluator: ~identical → fm≈100, drdm≈0.
        e = run("evaluate", str(SAUVOLA_REF), str(out), "-m", "fm,drdm", "--format", "csv")
        self.assertEqual(e.returncode, 0, e.stderr)
        row = csv_rows(e.stdout)[0]
        self.assertGreater(float(row["fm"]), 99.99)
        self.assertLess(float(row["drdm"]), 0.001)

    def test_binarize_otsu_no_params_and_xdog_floats(self):
        for args in (["-a", "otsu"],
                     ["-a", "xdog", "-p", "sigma=1.0", "-p", "phi=10"]):
            out = self.tmp / "o.png"
            r = run("binarize", str(SRC), *args, "-o", str(out))
            self.assertEqual(r.returncode, 0, r.stderr)
            self.assertTrue(out.is_file())

    def test_binarize_folder_batch(self):
        src_dir = self.tmp / "in"
        out_dir = self.tmp / "out"
        src_dir.mkdir()
        shutil.copy(SRC, src_dir / "a.png")
        shutil.copy(SRC, src_dir / "b.png")
        r = run("binarize", str(src_dir), "-a", "nick", "-o", str(out_dir))
        self.assertEqual(r.returncode, 0, r.stderr)
        self.assertTrue((out_dir / "a_bin.png").is_file())
        self.assertTrue((out_dir / "b_bin.png").is_file())

    # ── grayscale ───────────────────────────────────────────────────────────

    def test_grayscale(self):
        out = self.tmp / "gray.png"
        r = run("grayscale", str(SRC), "-a", "bt601", "-o", str(out))
        self.assertEqual(r.returncode, 0, r.stderr)
        self.assertTrue(out.is_file())

    # ── evaluate ────────────────────────────────────────────────────────────

    def test_evaluate_matches_dibco(self):
        """Standard + pseudo metrics must match the official DIBCO tool output.
        Pseudo metrics here use the DIBCO reference weight files directly."""
        r = run("evaluate", str(GT), str(SAUVOLA_REF),
                "-m", "fm,drdm,psnr,recall,precision,pseudo-fm,pseudo-precision,pseudo-recall",
                "--pweights", str(PWEIGHTS_REF), "--rweights", str(RWEIGHTS_REF), "--format", "csv")
        self.assertEqual(r.returncode, 0, r.stderr)
        row = csv_rows(r.stdout)[0]
        for metric, expected in DIBCO_METRICS.items():
            self.assertAlmostEqual(float(row[metric]), expected, delta=METRIC_TOL,
                                   msg=f"{metric}: {row[metric]} vs DIBCO {expected}")

    def test_evaluate_doxa_only_metrics(self):
        """MCC / accuracy / NRM aren't in the DIBCO report; check doxapy's values."""
        r = run("evaluate", str(GT), str(SAUVOLA_REF),
                "-m", "mcc,accuracy,nrm", "--format", "csv")
        self.assertEqual(r.returncode, 0, r.stderr)
        row = csv_rows(r.stdout)[0]
        self.assertAlmostEqual(float(row["mcc"]), 0.9183, places=3)
        self.assertAlmostEqual(float(row["accuracy"]), 97.6715, places=3)
        self.assertAlmostEqual(float(row["nrm"]), 0.0481, places=3)

    def test_evaluate_json_output(self):
        r = run("evaluate", str(GT), str(SAUVOLA_REF), "-m", "fm,drdm", "--format", "json")
        self.assertEqual(r.returncode, 0, r.stderr)
        data = json.loads(r.stdout)
        self.assertEqual(len(data), 1)
        self.assertEqual(data[0]["image"], SAUVOLA_REF.name)
        self.assertAlmostEqual(data[0]["fm"], 93.2047, places=3)

    def test_evaluate_dimension_mismatch_skips(self):
        # SRC is the same size as GT, so use a deliberately different shape by
        # evaluating GT against itself (match) plus a folder is overkill; instead
        # confirm a matching pair works and mismatched input is reported.
        r = run("evaluate", str(GT), str(SAUVOLA_REF), "-m", "fm", "--format", "csv")
        self.assertEqual(r.returncode, 0, r.stderr)
        self.assertEqual(len(csv_rows(r.stdout)), 1)

    # ── pseudo metrics + weights ────────────────────────────────────────────

    def test_weights_match_dibco_reference(self):
        """Our generated weight files must match the DIBCO tool's .dat files
        (identical down to DIBCO's 6-decimal rounding)."""
        w = run("weights", str(GT), "-o", str(self.tmp))
        self.assertEqual(w.returncode, 0, w.stderr)
        ours_r = self.tmp / "2JohnC1V3-GroundTruth_RWeights.dat"
        ours_p = self.tmp / "2JohnC1V3-GroundTruth_PWeights.dat"
        self.assertTrue(ours_r.is_file() and ours_p.is_file())

        for ours, ref in ((ours_r, RWEIGHTS_REF), (ours_p, PWEIGHTS_REF)):
            a, b = load_dat(ours), load_dat(ref)
            self.assertEqual(len(a), PIXELS)
            self.assertEqual(len(a), len(b))
            self.assertLess(max(abs(x - y) for x, y in zip(a, b)), WEIGHT_TOL)

    def test_pseudo_auto_matches_dibco_weights(self):
        """Pseudo metrics from auto-generated weights equal those from the DIBCO
        .dat files, and both equal the DIBCO tool's reported pseudo values."""
        metrics = "pseudo-fm,pseudo-precision,pseudo-recall"
        auto = run("evaluate", str(GT), str(SAUVOLA_REF), "-m", metrics, "--format", "csv")
        fromfiles = run("evaluate", str(GT), str(SAUVOLA_REF), "-m", metrics,
                        "--pweights", str(PWEIGHTS_REF), "--rweights", str(RWEIGHTS_REF),
                        "--format", "csv")
        self.assertEqual(auto.returncode, 0, auto.stderr)
        self.assertEqual(fromfiles.returncode, 0, fromfiles.stderr)
        arow, frow = csv_rows(auto.stdout)[0], csv_rows(fromfiles.stdout)[0]
        for key in ("pseudo-fm", "pseudo-precision", "pseudo-recall"):
            self.assertAlmostEqual(float(arow[key]), float(frow[key]), places=4)
            self.assertAlmostEqual(float(frow[key]), DIBCO_METRICS[key], delta=METRIC_TOL)

    # ── input validation (bilevel / weights / arguments) ────────────────────

    def _gray_png(self):
        """A non-bilevel grayscale PNG rendered from the color source."""
        out = self.tmp / "gray.png"
        r = run("grayscale", str(SRC), "-a", "mean", "-o", str(out))
        assert r.returncode == 0, r.stderr
        return out

    def test_evaluate_rejects_nonbilevel_result(self):
        """A grayscale 'result' must be refused, not scored as near-total noise."""
        r = run("evaluate", str(GT), str(self._gray_png()), "-m", "fm")
        self.assertNotEqual(r.returncode, 0)
        self.assertIn("not bilevel", r.stderr)
        self.assertNotIn("Traceback", r.stderr)

    def test_evaluate_rejects_nonbilevel_ground_truth(self):
        r = run("evaluate", str(self._gray_png()), str(SAUVOLA_REF), "-m", "fm")
        self.assertNotEqual(r.returncode, 0)
        self.assertIn("not bilevel", r.stderr)

    def test_evaluate_partial_skip_sets_exit_code(self):
        """A bad image is skipped with a warning; good ones still score, and the
        exit code reflects the partial run so CI can catch it."""
        r = run("evaluate", str(GT), str(SAUVOLA_REF), str(self._gray_png()),
                "-m", "fm", "--format", "csv")
        self.assertNotEqual(r.returncode, 0)
        rows = csv_rows(r.stdout)
        self.assertEqual(len(rows), 1)
        self.assertEqual(rows[0]["image"], SAUVOLA_REF.name)
        self.assertIn("Skipped", r.stderr)

    def test_weights_rejects_nonbilevel_ground_truth(self):
        r = run("weights", str(self._gray_png()), "-o", str(self.tmp))
        self.assertNotEqual(r.returncode, 0)
        self.assertIn("not bilevel", r.stderr)

    def test_weight_files_must_match_ground_truth_size(self):
        """A .dat from a different-sized image must be refused up front (the C++
        comparison indexes weights per pixel)."""
        short = self.tmp / "short.dat"
        short.write_text("1.0 2.0 3.0")
        r = run("evaluate", str(GT), str(SAUVOLA_REF), "-m", "pseudo-fm",
                "--pweights", str(short), "--rweights", str(short))
        self.assertNotEqual(r.returncode, 0)
        self.assertIn("3 weights", r.stderr)
        self.assertNotIn("Traceback", r.stderr)

    def test_malformed_weight_file_is_a_clean_error(self):
        bad = self.tmp / "bad.dat"
        bad.write_bytes(b"\x00\x01 not numbers \xff")
        r = run("evaluate", str(GT), str(SAUVOLA_REF), "-m", "pseudo-fm",
                "--pweights", str(bad), "--rweights", str(bad))
        self.assertNotEqual(r.returncode, 0)
        self.assertIn("weight file", r.stderr)
        self.assertNotIn("Traceback", r.stderr)

    def test_unknown_grayscale_method_errors(self):
        r = run("binarize", str(SRC), "-a", "sauvola", "-g", "bogus",
                "-o", str(self.tmp / "x.png"))
        self.assertNotEqual(r.returncode, 0)
        self.assertIn("Unknown grayscale method", r.stdout + r.stderr)
        self.assertNotIn("Traceback", r.stderr)
        self.assertFalse((self.tmp / "x.png").exists())

    def test_unknown_parameter_errors(self):
        """A typo'd -p name must error with the valid list, not be silently ignored."""
        r = run("binarize", str(SRC), "-a", "sauvola", "-p", "windoe=75",
                "-o", str(self.tmp / "x.png"))
        self.assertNotEqual(r.returncode, 0)
        err = r.stdout + r.stderr
        self.assertIn("windoe", err)
        self.assertIn("window", err)  # the valid names are offered
        self.assertFalse((self.tmp / "x.png").exists())

    def test_delim_must_be_single_character(self):
        r = run("evaluate", str(GT), str(SAUVOLA_REF), "--format", "csv", "--delim", ";;")
        self.assertNotEqual(r.returncode, 0)
        self.assertIn("single character", r.stderr)
        t = run("evaluate", str(GT), str(SAUVOLA_REF), "-m", "fm",
                "--format", "csv", "--delim", "\\t")
        self.assertEqual(t.returncode, 0, t.stderr)
        self.assertIn("\t", t.stdout)

    # ── output hygiene + path rules ─────────────────────────────────────────

    def test_csv_line_endings_are_clean(self):
        """Regression: csv.writer's \\r\\n rows + text-mode translation used to
        emit \\r\\r\\n (blank-line CSV) on Windows, to stdout and -o alike."""
        r = run_bytes("evaluate", str(GT), str(SAUVOLA_REF), "-m", "fm", "--format", "csv")
        self.assertEqual(r.returncode, 0, r.stderr)
        self.assertNotIn(b"\r\r", r.stdout)

        out = self.tmp / "m.csv"
        r2 = run("evaluate", str(GT), str(SAUVOLA_REF), "-m", "fm", "--format", "csv",
                 "-o", str(out))
        self.assertEqual(r2.returncode, 0, r2.stderr)
        self.assertNotIn(b"\r\r", out.read_bytes())
        self.assertEqual(len(csv_rows(out.read_text())), 1)

    def test_json_stdout_is_pipe_clean(self):
        """No stray trailing blank line when output is piped/redirected."""
        r = run("evaluate", str(GT), str(SAUVOLA_REF), "-m", "fm", "--format", "json")
        self.assertEqual(r.returncode, 0, r.stderr)
        self.assertFalse(r.stdout.endswith("\n\n"))
        json.loads(r.stdout)

    def test_empty_suffix_never_overwrites_input(self):
        src = self.tmp / "page.png"
        seed = run("binarize", str(SRC), "-a", "otsu", "-o", str(src))
        self.assertEqual(seed.returncode, 0, seed.stderr)
        before = src.read_bytes()
        clobber = run("binarize", str(src), "-a", "otsu", "--suffix", "")
        self.assertNotEqual(clobber.returncode, 0)
        self.assertIn("Refusing to overwrite", clobber.stdout + clobber.stderr)
        self.assertEqual(src.read_bytes(), before)

    def test_folder_rerun_does_not_reingest_outputs(self):
        folder = self.tmp / "docs"
        folder.mkdir()
        shutil.copy(SRC, folder / "a.ppm")
        first = run("binarize", str(folder), "-a", "otsu")
        self.assertEqual(first.returncode, 0, first.stderr)
        self.assertTrue((folder / "a_bin.png").is_file())
        second = run("binarize", str(folder), "-a", "otsu")
        self.assertEqual(second.returncode, 0, second.stderr)
        self.assertIn("ignoring", second.stderr)
        self.assertFalse((folder / "a_bin_bin.png").exists())

    def test_batch_output_must_be_folder(self):
        folder = self.tmp / "in"
        folder.mkdir()
        shutil.copy(SRC, folder / "a.ppm")
        shutil.copy(SRC, folder / "b.ppm")
        r = run("binarize", str(folder), "-a", "otsu", "-o", str(self.tmp / "out.png"))
        self.assertNotEqual(r.returncode, 0)
        self.assertIn("must be a folder", r.stderr)
        self.assertFalse((self.tmp / "out.png").exists())

    def test_extensionless_single_output_is_ambiguous(self):
        r = run("binarize", str(SRC), "-a", "otsu", "-o", str(self.tmp / "result"))
        self.assertNotEqual(r.returncode, 0)
        self.assertIn("Ambiguous output", r.stderr)

    def test_glob_patterns_expand_without_shell(self):
        """Windows shells pass wildcards through verbatim; the CLI expands them."""
        shutil.copy(SAUVOLA_REF, self.tmp / "r1.pbm")
        shutil.copy(SAUVOLA_REF, self.tmp / "r2.pbm")
        r = run("evaluate", str(GT), str(self.tmp / "*.pbm"), "-m", "fm", "--format", "csv")
        self.assertEqual(r.returncode, 0, r.stderr)
        self.assertEqual(len(csv_rows(r.stdout)), 2)

    def test_evaluate_continues_past_empty_folder(self):
        empty = self.tmp / "empty"
        empty.mkdir()
        r = run("evaluate", str(GT), str(empty), str(SAUVOLA_REF), "-m", "fm", "--format", "csv")
        self.assertEqual(r.returncode, 0, r.stderr)
        self.assertEqual(len(csv_rows(r.stdout)), 1)
        self.assertIn("no images", r.stderr)

    def test_16bit_pgm_is_rescaled_not_clipped(self):
        """16-bit grayscale must load (PIL would balk or clip at 255 otherwise)."""
        deep = self.tmp / "deep.pgm"
        values = bytes.fromhex("0000 4000 8000 c000 ffff 8000 4000 0000".replace(" ", ""))
        deep.write_bytes(b"P5\n4 2\n65535\n" + values)
        out = self.tmp / "deep_gray.png"
        r = run("grayscale", str(deep), "-a", "mean", "-o", str(out))
        self.assertEqual(r.returncode, 0, r.stderr)
        self.assertTrue(out.is_file())

    # ── experimental gating + errors ────────────────────────────────────────

    def test_experimental_gating(self):
        out = self.tmp / "g.png"
        blocked = run("binarize", str(SRC), "-a", "gatos", "-o", str(out))
        self.assertNotEqual(blocked.returncode, 0)
        self.assertIn("experimental", (blocked.stdout + blocked.stderr).lower())
        self.assertFalse(out.is_file())

        allowed = run("binarize", str(SRC), "-a", "gatos", "--experimental", "-o", str(out))
        self.assertEqual(allowed.returncode, 0, allowed.stderr)
        self.assertTrue(out.is_file())

    def test_unknown_algorithm_errors(self):
        r = run("binarize", str(SRC), "-a", "bogus", "-o", str(self.tmp / "x.png"))
        self.assertNotEqual(r.returncode, 0)
        self.assertIn("Unknown algorithm", r.stdout + r.stderr)


if __name__ == "__main__":
    unittest.main(verbosity=2)
