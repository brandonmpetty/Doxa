import unittest
from PIL import Image, ImageChops
import numpy as np
import os

import sys
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'build'))) # Linux .so
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'build', 'Release'))) # Windows .pyd

import doxapy

# Get the absolute path to the RESOURCES directory (at project root)
RESOURCES_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', '..', 'Doxa.Test', 'Resources'))

def read_image(file):
    # Use the absolute path to the README directory
    full_path = os.path.join(RESOURCES_DIR, os.path.basename(file))
    # Grayscale Conversion: Qt
    return (np.dot(np.array(Image.open(full_path).convert('RGB')), [11, 16, 5]).astype(np.uint16) // 32).astype(np.uint8)
    #return np.array(Image.open(full_path).convert('L'))


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

        # Update the grayscale image to binary
        doxapy.Binarization.update_to_binary(doxapy.Binarization.Algorithms.SAUVOLA, image, params)

        # Ensure they are equal
        self.assertTrue((binary_image == image).all())

        # Compare againts our control
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
        doxapy.Binarization.update_to_binary(doxapy.Binarization.Algorithms.SAUVOLA, image, params)

        # Functions under test
        performanceAll = doxapy.calculate_performance(groundtruth_image, image)
        performance = doxapy.calculate_performance_ex(groundtruth_image, image, drdm=True, psnr=True)

        # Assert All
        self.assertAlmostEqual(performanceAll.get("accuracy"), 97.671, 2)
        self.assertAlmostEqual(performanceAll.get("fm"), 93.204, 2)
        self.assertAlmostEqual(performanceAll.get("psnr"), 16.329, 2)
        self.assertAlmostEqual(performanceAll.get("nrm"), 0.048, 2)
        self.assertAlmostEqual(performanceAll.get("mcc"), 0.918, 2)
        self.assertAlmostEqual(performanceAll.get("drdm"), 2.209, 2)

        # Assert Partial
        self.assertEqual(performance.get("accuracy"), None)
        self.assertEqual(performance.get("fm"), None)
        self.assertEqual(performance.get("nrm"), None)
        self.assertEqual(performance.get("mcc"), None)
        self.assertEqual(performance.get("psnr"), performanceAll.get("psnr"))
        self.assertEqual(performance.get("drdm"), performanceAll.get("drdm"))


if __name__ == '__main__':
    unittest.main()