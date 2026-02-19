# DoxaPy

## Introduction
DoxaPy is an image binarization library focusing on local adaptive thresholding algorithms. In English, this means that it has the ability to turn a color or gray scale image into a black and white image.

**Algorithms**
* Otsu - "A threshold selection method from gray-level histograms", 1979.
* Bernsen - "Dynamic thresholding of gray-level images", 1986.
* Niblack - "An Introduction to Digital Image Processing", 1986.
* Sauvola - "Adaptive document image binarization", 1999.
* Wolf - "Extraction and Recognition of Artificial Text in Multimedia Documents", 2003.
* Gatos - "Adaptive degraded document image binarization", 2005. (Partial)
* NICK - "Comparison of Niblack inspired Binarization methods for ancient documents", 2009.
* AdOtsu - "A multi-scale framework for adaptive binarization of degraded document images", 2010.
* Su - "Binarization of Historical Document Images Using the Local Maximum and Minimum", 2010.
* T.R. Singh - "A New local Adaptive Thresholding Technique in Binarization", 2011.
* Bataineh - "An adaptive local binarization method for document images based on a novel thresholding method and dynamic windows", 2011. (unreproducible)
* ISauvola - "ISauvola: Improved Sauvola's Algorithm for Document Image Binarization", 2016.
* WAN - "Binarization of Document Image Using Optimum Threshold Modification", 2018.

**Optimizations**
* Shafait - "Efficient Implementation of Local Adaptive Thresholding Techniques Using Integral Images", 2008.
* Petty - An algorithm for efficiently calculating the min and max of a local window.  Unpublished, 2019.
* Chan - "Memory-efficient and fast implementation of local adaptive binarization methods", 2019.
* SIMD - SSE2, ARM NEON

**Performance Metrics**
* Overall Accuracy
* F-Measure, Precision, Recall
* Pseudo F-Measure, Precision, Recall - "Performance Evaluation Methodology for Historical Document Image Binarization", 2013.
* Peak Signal-To-Noise Ratio (PSNR)
* Negative Rate Metric (NRM)
* Matthews Correlation Coefficient (MCC)
* Distance-Reciprocal Distortion Measure (DRDM) - "An Objective Distortion Measure for Binary Document Images Based on Human Visual Perception", 2002.


## Overview
DoxaPy uses the Δoxa Binarization Framework for quickly processing python Image files.  It is comprised of three major sets of algorithms: Color to Grayscale, Grayscale to Binary, and Performance Metrics.  It can be used as a full DIBCO Metrics replacement that is significantly smaller, faster, and easier to integrate into existing projects.

### Example
This short demo uses DoxaPy to read in a color image, converts it to binary, and then compares it to a Ground Truth image in order to calculate performance.

```python
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


# Read our target image and convert it to grayscale
grayscale_image = read_image("2JohnC1V3.png")

# Convert the grayscale image to a binary image (algorithm parameters optional)
binary_image = doxapy.to_binary(doxapy.Binarization.Algorithms.SAUVOLA, grayscale_image, {"window": 75, "k": 0.2})

# Calculate the binarization performance using a Ground Truth image
groundtruth_image = read_image("2JohnC1V3-GroundTruth.png")
performance = doxapy.calculate_performance(groundtruth_image, binary_image)
print(performance)

# Display our resulting image
Image.fromarray(binary_image).show()
```

### DoxaPy Notebook
For more details, open the [DoxaPy Notebook](https://github.com/brandonmpetty/Doxa/blob/master/Bindings/Python/DoxaPy.ipynb) and to get an interactive demo.


## Building and Test
DoxaPy supports 64b Linux, Windows, and Mac OSX on Python 3.x. Starting with DoxaPy 0.9.4, Python 3.12 and above are supported with full ABI compatibility. This means that new versions of DoxaPy will only be published due to feature enhancements, not Python version support.

**Build from Project Root**
```bash
# From the Doxa project root
git clone --depth 1 https://github.com/brandonmpetty/Doxa.git
cd Doxa
cmake --preset python
cmake --build build-python --config Release
ctest --test-dir build-python -C Release
```

**Local Package Build**
```bash
python -m build
```

## License
CC0 - Brandon M. Petty, 2026

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

[View Online](https://creativecommons.org/publicdomain/zero/1.0/legalcode)

"*Freely you have received; freely give.*" - Matt 10:8