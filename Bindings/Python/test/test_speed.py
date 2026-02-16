"""
Speed Tests for DoxaPy

Measures execution time for:
- Sauvola binarization
- WAN binarization
- GlobalThresholding (Otsu) binarization
- DRDM calculation
- Classified Performance calculation

Run with: python test_speed.py
"""

import unittest
import time
import numpy as np
from PIL import Image
import os
import sys

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'build')))  # Linux .so
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'build', 'Release')))  # Windows .pyd

import doxapy

# Get the absolute path to the RESOURCES directory
RESOURCES_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', '..', 'Doxa.Test', 'Resources'))

# Number of iterations for timing
WARMUP_ITERATIONS = 3
TIMING_ITERATIONS = 10


def read_image(file):
    """Read image and convert to grayscale using Qt method."""
    full_path = os.path.join(RESOURCES_DIR, os.path.basename(file))
    # Grayscale Conversion: Qt method
    return (np.dot(np.array(Image.open(full_path).convert('RGB')), [11, 16, 5]).astype(np.uint16) // 32).astype(np.uint8)


def measure_time(func, warmup=WARMUP_ITERATIONS, iterations=TIMING_ITERATIONS):
    """Measure execution time of a function."""
    # Warmup runs
    for _ in range(warmup):
        func()

    # Timed runs
    times = []
    for _ in range(iterations):
        start = time.perf_counter()
        func()
        end = time.perf_counter()
        times.append((end - start) * 1000)  # Convert to ms

    return {
        'min': min(times),
        'max': max(times),
        'avg': sum(times) / len(times),
        'median': sorted(times)[len(times) // 2]
    }


def format_results(name, results, image_shape):
    """Format timing results as a string."""
    pixels = image_shape[0] * image_shape[1]
    mpixels = pixels / 1_000_000
    throughput = mpixels / (results['avg'] / 1000)
    return (
        f"\n{name}\n"
        f"  Image size: {image_shape[1]}x{image_shape[0]} ({mpixels:.2f} MP)\n"
        f"  Min:    {results['min']:8.3f} ms\n"
        f"  Max:    {results['max']:8.3f} ms\n"
        f"  Avg:    {results['avg']:8.3f} ms\n"
        f"  Median: {results['median']:8.3f} ms\n"
        f"  Throughput: {throughput:.2f} MP/s"
    )


class DoxaPySpeedTests(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        """Load test images once for all tests."""
        print("\n" + "=" * 60)
        print("DoxaPy Speed Tests")
        print("=" * 60)
        print(f"\nWarmup iterations: {WARMUP_ITERATIONS}")
        print(f"Timing iterations: {TIMING_ITERATIONS}")
        print("\nLoading test images...")

        cls.image = read_image("2JohnC1V3.ppm")
        cls.groundtruth_image = read_image("2JohnC1V3-GroundTruth.pbm")

        print(f"Grayscale image shape: {cls.image.shape}")
        print(f"Ground truth shape: {cls.groundtruth_image.shape}")

        # Create a binary image for performance metric tests
        cls.binary_image = np.empty(cls.image.shape, cls.image.dtype)
        params = {"window": 27, "k": 0.10}
        sauvola = doxapy.Binarization(doxapy.Binarization.Algorithms.SAUVOLA)
        sauvola.initialize(cls.image)
        sauvola.to_binary(cls.binary_image, params)

        print("\n" + "-" * 60)
        print("BINARIZATION ALGORITHMS")
        print("-" * 60)

    def test_sauvola_speed(self):
        """Measure Sauvola binarization speed."""
        binary_image = np.empty(self.image.shape, self.image.dtype)
        params = {"window": 75, "k": 0.2}

        sauvola = doxapy.Binarization(doxapy.Binarization.Algorithms.SAUVOLA)
        sauvola.initialize(self.image)

        def run():
            sauvola.to_binary(binary_image, params)

        results = measure_time(run)
        print(format_results("Sauvola", results, self.image.shape))
        self.assertGreater(results['avg'], 0)

    def test_wan_speed(self):
        """Measure WAN binarization speed."""
        binary_image = np.empty(self.image.shape, self.image.dtype)
        params = {"window": 75, "k": 0.2}

        wan = doxapy.Binarization(doxapy.Binarization.Algorithms.WAN)
        wan.initialize(self.image)

        def run():
            wan.to_binary(binary_image, params)

        results = measure_time(run)
        print(format_results("WAN", results, self.image.shape))
        self.assertGreater(results['avg'], 0)

    def test_otsu_speed(self):
        """Measure Otsu (GlobalThresholding) binarization speed."""
        binary_image = np.empty(self.image.shape, self.image.dtype)
        params = {}

        otsu = doxapy.Binarization(doxapy.Binarization.Algorithms.OTSU)
        otsu.initialize(self.image)

        def run():
            otsu.to_binary(binary_image, params)

        results = measure_time(run)
        print(format_results("Otsu (GlobalThresholding)", results, self.image.shape))
        self.assertGreater(results['avg'], 0)

    def test_drdm_speed(self):
        """Measure DRDM calculation speed."""
        print("\n" + "-" * 60)
        print("PERFORMANCE METRICS")
        print("-" * 60)

        def run():
            doxapy.calculate_performance_ex(self.groundtruth_image, self.binary_image, drdm=True)

        results = measure_time(run)
        print(format_results("DRDM", results, self.image.shape))
        self.assertGreater(results['avg'], 0)

    def test_classified_performance_speed(self):
        """Measure Classified Performance calculation speed (all metrics except DRDM)."""
        def run():
            doxapy.calculate_performance_ex(
                self.groundtruth_image, self.binary_image,
                accuracy=True, fm=True, psnr=True, nrm=True, mcc=True
            )

        results = measure_time(run)
        print(format_results("ClassifiedPerformance (no DRDM)", results, self.image.shape))
        self.assertGreater(results['avg'], 0)

    def test_full_performance_speed(self):
        """Measure full performance calculation speed (all metrics including DRDM)."""
        def run():
            doxapy.calculate_performance(self.groundtruth_image, self.binary_image)

        results = measure_time(run)
        print(format_results("Full Performance (all metrics)", results, self.image.shape))
        self.assertGreater(results['avg'], 0)

    @classmethod
    def tearDownClass(cls):
        print("\n" + "=" * 60)
        print("Speed tests completed")
        print("=" * 60)


if __name__ == '__main__':
    unittest.main(verbosity=2)
