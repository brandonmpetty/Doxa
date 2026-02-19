import unittest
from PIL import Image, ImageChops
import numpy as np
import os

import sys
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'dist')))

import doxapy

# Get the absolute path to the RESOURCES directory (at project root)
RESOURCES_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', '..', 'Doxa.Test', 'Resources'))

def read_image(file, algorithm=doxapy.GrayscaleAlgorithms.QT):
    full_path = os.path.join(RESOURCES_DIR, os.path.basename(file))
    image = Image.open(full_path)

    # If already in grayscale or binary, do not convert it
    if image.mode == 'L':
        return np.array(image)
    
    # Read the color image
    rgb_image = np.array(image.convert('RGB') if image.mode not in ('RGB', 'RGBA') else image)

    # Use Doxa to convert to grayscale
    return doxapy.to_grayscale(algorithm, rgb_image)

def read_weights(file):
    full_path = os.path.join(RESOURCES_DIR, os.path.basename(file))
    return doxapy.read_weights(full_path)


class DoxaPyTests(unittest.TestCase):
    def test_binarization(self):

        # Read in a color image, transforming it into a grayscale image
        image = read_image("2JohnC1V3.ppm")

        # Create a new binary image
        binary_image = np.empty(image.shape, image.dtype)

        params = {"window": 27, "k": 0.10}
        sauvola = doxapy.Binarization(doxapy.Binarization.Algorithms.SAUVOLA)
        sauvola.initialize(image)
        sauvola.to_binary(binary_image, params)

        # Update the grayscale image to binary in-place
        doxapy.update_to_binary(doxapy.Binarization.Algorithms.SAUVOLA, image, params)

        # Ensure they are equal
        self.assertTrue((binary_image == image).all())

        # Compare against our control
        expected_image_path = os.path.join(RESOURCES_DIR, os.path.basename("2JohnC1V3-Sauvola.pbm"))
        expected_image = Image.open(expected_image_path)
        #expected_image.save("expected_image.png")
        
        output_image = Image.fromarray(binary_image)
        #output_image.save('output_image.png')

        diff = ImageChops.difference(expected_image, output_image);
        #diff.show()
        self.assertIsNone(diff.getbbox())


    def test_performance(self):

        # Setup
        image = read_image("2JohnC1V3.ppm")
        groundtruth_image = read_image("2JohnC1V3-GroundTruth.pbm")
        params = {"window": 27, "k": 0.10}
        doxapy.update_to_binary(doxapy.Binarization.Algorithms.SAUVOLA, image, params)

        # Functions under test
        performanceAll = doxapy.calculate_performance(groundtruth_image, image)
        performance = doxapy.calculate_performance_ex(groundtruth_image, image, drdm=True, psnr=True)

        # Assert All
        self.assertAlmostEqual(performanceAll.get("accuracy"), 97.671, 2)
        self.assertAlmostEqual(performanceAll.get("fm"), 93.204, 2)
        self.assertAlmostEqual(performanceAll.get("recall"), 91.3811, 2)
        self.assertAlmostEqual(performanceAll.get("precision"), 95.1025, 2)
        self.assertAlmostEqual(performanceAll.get("psnr"), 16.329, 2)
        self.assertAlmostEqual(performanceAll.get("nrm"), 0.048, 2)
        self.assertAlmostEqual(performanceAll.get("mcc"), 0.918, 2)
        self.assertAlmostEqual(performanceAll.get("drdm"), 1.9519, 3)

        # Assert Partial
        self.assertEqual(performance.get("accuracy"), None)
        self.assertEqual(performance.get("fm"), None)
        self.assertEqual(performance.get("nrm"), None)
        self.assertEqual(performance.get("mcc"), None)
        self.assertEqual(performance.get("psnr"), performanceAll.get("psnr"))
        self.assertEqual(performance.get("drdm"), performanceAll.get("drdm"))


    def test_pseudo_performance(self):

        # Setup
        image = read_image("2JohnC1V3.ppm")
        groundtruth_image = read_image("2JohnC1V3-GroundTruth.pbm")
        params = {"window": 27, "k": 0.10}
        doxapy.update_to_binary(doxapy.Binarization.Algorithms.SAUVOLA, image, params)

        # Load pseudo weights
        p_weights = read_weights("2JohnC1V3-GroundTruth_PWeights.dat")
        r_weights = read_weights("2JohnC1V3-GroundTruth_RWeights.dat")

        # Calculate performance with pseudo weights
        performance = doxapy.calculate_performance(groundtruth_image, image, p_weights, r_weights)

        # Assert pseudo metrics
        self.assertAlmostEqual(performance.get("pseudo_fm"), 93.393, 2)
        self.assertAlmostEqual(performance.get("pseudo_recall"), 92.7954, 2)
        self.assertAlmostEqual(performance.get("pseudo_precision"), 93.9983, 2)


if __name__ == '__main__':
    unittest.main()