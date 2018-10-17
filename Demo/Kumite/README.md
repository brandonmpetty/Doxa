# Kumite v1.0
## Introduction
Kumite is a demo application showing how to use the [Δoxa Binarization Framework](https://github.com/brandonmpetty/Doxa) for binarization performance analysis.
It differs from the PerformanceMetrics application in that it will test every permutation of Window Size and K-Value within a set range.

**Performance Metrics**
* Overall Accuracy
* F-Measure
* Peak Signal-To-Noise Ratio (PSNR)
* Distance-Reciprocal Distortion Measure (DRDM) - "An Objective Distortion Measure for Binary Document Images Based on Human Visual Perception", 2002.

**Native Image Support**
* Portable Any-Map: PBM (P4), 8-bit PGM (P5), PPM (P6), PAM (P7)

## Overview
Kumite is an over the top, Bloodsport themed, application.
Each supported algorithm has been given an exclusive invitation to the Kumite.
As with every good fighter, it must train.  Here, detailed performance information will be gathered for every Window Size and K-Value permutation, for each specified algorithm.
Each algorithm can optionally output 5 CSV files; one for each performance measure.
After each algorithm is done, its performance data is analyzed and ranked.
The best performing parameters for each algorithm then go on to compete against the best of the best.
While this application does not take itself too seriously, the analytics produced by this tool has the potential to provide invaluable insights into these algorithms.

### Example
This is an example of what you can expect when running this application.

```
C:\>Kumite.exe --source "<dir>\UnitTests\Resources\2JohnC1V3.pam" --groundtruth "<dir>\UnitTests\Resources\2JohnC1V3-GroundTruth.pam" --output "<dir>\Demo\Kumite\Samples"
Algorithm      Window         K              Accuracy       F-Measure      PSNR           DRDM           Time
Wolf           20             0.18           97.6978        93.3284        16.3785        1.94460        0.0302862
Sauvola        26             0.10           97.6712        93.2038        16.3286        1.95214        0.0154719
Nick           44             -0.10          97.6295        93.0466        16.2515        1.96813        0.0141377
Niblack        223            -0.61          97.4521        92.5476        15.9382        2.13264        0.0145479
```

The list above hightlights both the power and weakness of Performance Measure Ranking.
Ranking provides a very simple solution for judging performance without creating an explicit measure bias.
The problem is that an implicit bias is there and can be easily demonstrated.


### Goals
* Provide a HTML/JS file that can read in the CSVs and help graphically visualize the data.
* ~~Refactor the binarization methods to take in a precalculated Integral Image to reduce runtime by over 50%.~~

## License
CC0 - Brandon M. Petty, 2018

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

[View Online](https://creativecommons.org/publicdomain/zero/1.0/legalcode)

"*Freely you have received; freely give.*" - Matt 10:8