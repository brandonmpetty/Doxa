import unittest
from PIL import Image
import numpy as np
import os

import sys
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'build', 'Release')))

import doxapy

# Get the absolute path to the README directory (at project root)
README_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', '..', 'README'))

def read_image(file):
    # Use the absolute path to the README directory
    full_path = os.path.join(README_DIR, os.path.basename(file))
    return np.array(Image.open(full_path).convert('L'))


class DoxaPyTests(unittest.TestCase):
    def test_binarization(self):

        # Read a PNG as a grayscale image
        image = read_image("2JohnC1V3.png")

        # Create a new binary image
        binary_image = np.empty(image.shape, image.dtype)
        sauvola = doxapy.Binarization(doxapy.Binarization.Algorithms.SAUVOLA)
        sauvola.initialize(image)
        sauvola.to_binary(binary_image, {"window": 75, "k": 0.2})

        # Update the grayscale image to binary
        doxapy.Binarization.update_to_binary(doxapy.Binarization.Algorithms.SAUVOLA, image)

        # Ensure they are equal
        self.assertTrue((binary_image == image).all())

    def test_performance(self):

        # Setup
        image = read_image("2JohnC1V3.png")
        groundtruth_image = read_image("2JohnC1V3-GroundTruth.png")
        doxapy.Binarization.update_to_binary(doxapy.Binarization.Algorithms.SAUVOLA, image)

        # Functions under test
        performanceAll = doxapy.calculate_performance(groundtruth_image, image)
        performance = doxapy.calculate_performance_ex(groundtruth_image, image, drdm=True, psnr=True)

        # Assert All
        self.assertAlmostEqual(performanceAll.get("accuracy"), 97.095, 2)
        self.assertAlmostEqual(performanceAll.get("fm"), 91.036, 2)
        self.assertAlmostEqual(performanceAll.get("psnr"), 15.368, 2)
        self.assertAlmostEqual(performanceAll.get("nrm"), 0.079, 2)
        self.assertAlmostEqual(performanceAll.get("mcc"), 0.897, 2)
        self.assertAlmostEqual(performanceAll.get("drdm"), 2.789, 2)

        # Assert Partial
        self.assertEqual(performance.get("accuracy"), None)
        self.assertEqual(performance.get("fm"), None)
        self.assertEqual(performance.get("nrm"), None)
        self.assertEqual(performance.get("mcc"), None)
        self.assertEqual(performance.get("psnr"), performanceAll.get("psnr"))
        self.assertEqual(performance.get("drdm"), performanceAll.get("drdm"))


if __name__ == '__main__':
    unittest.main()