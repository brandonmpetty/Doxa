
# BinBench

BinBench is a swiss army knife for binarization research.  Experiment with binary and grayscale image generation and metrics evaluation.

BinBench supports all image formats supported by [Pillow](https://pillow.readthedocs.io/en/stable/handbook/image-file-formats.html), such as: BMP, PNG, TIFF, PBM, and others.

BinBench is powered by the [Δoxa Binarization Framework](https://github.com/brandonmpetty/doxa), an open source library dedicated to exposing paper-locked algorithms to the world.

## Setup

BinBench requires Python 3.12+ and depends on Pillow, NumPy and DoxaPy libraries.

```bash
pip install -r requirements.txt
```

Alternatively, a local Doxa Python build can be used by setting the `DOXAPY_PATH` environment variable.  When set, it takes precedence over any pip-installed DoxaPy.

## Examples

BinBench comes with built-in help and examples.  The examples here show the most common use cases but only scratch the surface of what BinBench can do.  For more detail, run `python binbench.py`.

### Evaluate
---

BinBench comes with a full range of binarization performance metrics.
It is a full replacement for **DIBCO_metrics.exe** and **BinEvalWeights.exe**, wrapped into one fast, cross platform, open source utility.

Generate performance metrics on an image:
```
python binbench.py evaluate groundtruth.png binary.png

image        accuracy↑      fm↑  recall↑  precision↑    mcc↑    psnr↑    nrm↓   drdm↓  pseudo-fm↑  pseudo-precision↑  pseudo-recall↑
-----------  ---------  -------  -------  ----------  ------  -------  ------  ------  ----------  -----------------  --------------
binary.png     97.6715  93.2047  91.3811     95.1025  0.9183  16.3292  0.0481  1.9519     93.3930            93.9983         92.7954
```
<br/>

Generate specific metrics on a set of images in CSV:
```
python binbench.py evaluate groundtruth.pbm image-Sauvola.pbm image-Niblack.pbm -m pseudo-fm,fm,psnr,drdm,mcc --format csv --delim ;

image;pseudo-fm;fm;psnr;drdm;mcc
image-Sauvola.pbm;93.392995;93.204665;16.329214;1.951865;0.918270
image-Niblack.pbm;92.100350;92.548571;15.938734;2.132415;0.910459
```
<br/>

Generate Pseudo Weight files and use them:
```
python binbench.py weights groundtruth.png

python binbench.py evaluate groundtruth.png binary.png --rweights groundtruth_RWeights.dat --pweights groundtruth_PWeights.dat
```

#### DIBCO Metrics

BinBench is bit-exact with both DIBCO tools except when calculating DRDM.  DIBCO_metrics.exe's DRDM suffers from float-drift, leading to a very slight rounding error.

### Binarization
---

BinBench comes with a number of built-in binarization algorithms one can use to experiment with.  This list consists primarily of fast, simple, local adaptive thresholding algorithms.

Get a list of available algorithms:
```
python binbench.py binarize
```
<br/>

Learning about a specific algorithm's parameters:
```
python binbench.py binarize --describe sauvola
```
<br/>

Binarization with defaults:
```
python binbench.py binarize -a sauvola input.png
```
<br/>

A complex example with specified grayscale conversion, binarization parameters, over an entire folder of images:
```
python binbench.py binarize -g labdist -a phansalkar -p window=37 -p k=0.27 ./input -o ./output
```

*NOTE: more details on grayscale by calling **binbench.py grayscale***

#### DIBCO Competition

The (H)DIBCO competition would compare submitted algorithm results against the Otsu global thresholding algorithm and the Sauvola local adaptive thresholding algorithm.  The algorithm parameters for Sauvola were never disclosed, nor was their Sauvola implementation or any of their binarized images.  Their grayscale conversion formula was also never disclosed, but is **BT601**.  BinBench defaults to **MEAN** for grayscale conversion for two reasons:
1. it avoids double grayscale conversion when an RGB image happens to already be grayscale.
2. it produces better results according to "Color-to-Grayscale: Does the Method Matter in Image Recognition?", 2012.

Because the Otsu algorithm is standardized w/o parameters, using a grayscale BT601 conversion will allow you to generate (H)DIBCO paper-exact results.  Sauvola, and other algorithms, does not share that luxury and may differ slightly based on implementation details like border padding, rounding strategies, and hardcoded parameters. 
<br/>

---
BinBench & the Δoxa Binarization Framework, written by Brandon M. Petty, CC0 2026.