from PIL import Image
import numpy as np
import doxapy

# Read an image.  If its color, use one of our many Grayscale algorithms to convert it
def read_image(file, algorithm=doxapy.GrayscaleAlgorithms.MEAN):
    image = Image.open(file)

    # If already in grayscale or binary, do not convert it
    if image.mode == 'L':
        return np.array(image)
    
    # Read the color image
    rgb_image = np.array(image.convert('RGB') if image.mode not in ('RGB', 'RGBA') else image)

    # Use Doxa to convert grayscale
    return doxapy.to_grayscale(algorithm, rgb_image)


# Use Doxa to convert our image into grayscale, if it isn't already
grayscale_image = read_image("2JohnC1V3.png", doxapy.GrayscaleAlgorithms.MEAN)

# Convert the grayscale image to binary, returning a new image
# NOTE: Algorithm parameters are options.  Defaults are provided.
binary_image = doxapy.to_binary(doxapy.Binarization.Algorithms.SAUVOLA, grayscale_image, {"window": 75, "k": 0.2})

# Calculate the binarization performance using a Ground Truth image
groundtruth_image = read_image("2JohnC1V3-GroundTruth.png")
performance = doxapy.calculate_performance(groundtruth_image, binary_image)
print(performance)

# Display our resulting image
Image.fromarray(binary_image).show()

# Example: How to update a grayscale to binary in place
#doxapy.update_to_binary(doxapy.Binarization.Algorithms.SAUVOLA, grayscale_image, {"window": 75, "k": 0.2})

# Example: For testing parameter changes in a tight loop
#binary_image = np.empty(grayscale_image.shape, grayscale_image.dtype)
#sauvola = doxapy.Binarization(doxapy.Binarization.Algorithms.SAUVOLA)
#sauvola.initialize(grayscale_image)
#sauvola.to_binary(binary_image, {"window": 75, "k": 0.2})
