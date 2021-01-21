from PIL import Image
import numpy as np
import DoxaPy


def ReadImage(file):
    return np.array(Image.open(file).convert('L'))

# Read our target image and setup an output image buffer
grayScaleImage = ReadImage("2JohnC1V3.png")
binaryImage = np.empty(grayScaleImage.shape, grayScaleImage.dtype)

# Pick an algorithm from the DoxaPy library and convert the image to binary
sauvola = DoxaPy.Binarization(DoxaPy.Binarization.Algorithms.SAUVOLA)
sauvola.Initialize(grayScaleImage)
sauvola.ToBinary(binaryImage)

# Calculate the binarization performance using a Ground Truth image
groundTruthImage = ReadImage("2JohnC1V3-GroundTruth.png")
performance = DoxaPy.CalculatePerformance(groundTruthImage, binaryImage)
print(performance)

# Display our resulting image
Image.fromarray(binaryImage).show() 