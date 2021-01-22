from PIL import Image
import numpy as np
import doxapy

def read_image(file):
    return np.array(Image.open(file).convert('L'))


# Read our target image and setup an output image buffer
grayscale_image = read_image("2JohnC1V3.png")
binary_image = np.empty(grayscale_image.shape, grayscale_image.dtype)

# Pick an algorithm from the DoxaPy library and convert the image to binary
sauvola = doxapy.Binarization(doxapy.Binarization.Algorithms.SAUVOLA)
sauvola.initialize(grayscale_image)
sauvola.to_binary(binary_image, {"window": 75, "k": 0.2}) # algorithm params are optional

# Calculate the binarization performance using a Ground Truth image
groundtruth_image = read_image("2JohnC1V3-GroundTruth.png")
performance = doxapy.calculate_performance(groundtruth_image, binary_image)
print(performance)

# Display our resulting image
Image.fromarray(binary_image).show()

# Lines 11 - 16 could be replaced with this one-liner, if you want to update the same image.
#doxapy.Binarization.update_to_binary(doxapy.Binarization.Algorithms.SAUVOLA, grayscale_image)
