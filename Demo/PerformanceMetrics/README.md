# PerformanceMetrics v1.0
## Introduction
PerformanceMetrics is a demo application showing how to use the [Δoxa Binarization Framework](https://github.com/brandonmpetty/Doxa) for binarization performance analysis.

**Performance Metrics**
* Overall Accuracy
* F-Measure
* Peak Signal-To-Noise Ratio (PSNR)
* Negative Rate Metric (NRM)
* Distance-Reciprocal Distortion Measure (DRDM) - "An Objective Distortion Measure for Binary Document Images Based on Human Visual Perception", 2002.

**Native Image Support**
* Portable Any-Map: PBM (P4), 8-bit PGM (P5), PPM (P6), PAM (P7)

## Overview
The goal of this application is to show how easily one can create a fairly powerful application using ΔBF.
Not only is the application fast but the 64b Release binary is only 37KB without any external dependencies!
Don't want to download and install an 800MB+ MATLAB runtime to run a closed source H-DIBCO metrics tool?  Try this!
The only catch to this tool is that it has limited native image format support.

### Example
This is an example of what you can expect when running this application.

```
PerformanceMetrics.exe <path>\UnitTests\Resources\2JohnC1V3-GroundTruth.pam <path>\UnitTests\Resources\2JohnC1V3-Wolf.pam

Accuracy:       97.6747
F-Measure:      93.2996
PSNR:           16.3352
DRDM:           1.96513
```

### Goals
* Add support for comparing multiple targets against one ground truth image

## License
CC0 - Brandon M. Petty, 2017

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

[View Online](https://creativecommons.org/publicdomain/zero/1.0/legalcode)

"*Freely you have received; freely give.*" - Matt 10:8