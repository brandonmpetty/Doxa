% Doxa Binarization Framework - MATLAB Demo
%
% This demo shows how to read an image, convert it to grayscale, binarize it,
% and calculate performance metrics using the Doxa framework.
%
% Requirements:
%   - Build the MEX files: cmake --preset matlab && cmake --build build-matlab --config Release
%   - Add the MEX output directory to the MATLAB path

% Read a color image and convert to grayscale
img = Doxa.Image('../../Doxa.Test/Resources/2JohnC1V3.ppm', Doxa.Grayscale.QT);

% Binarize using the Sauvola algorithm
binary = Doxa.binarize(Doxa.Algorithms.SAUVOLA, img, window=27, k=0.1);

% Load a ground truth image and calculate performance
gt = Doxa.Image('../../Doxa.Test/Resources/2JohnC1V3-GroundTruth.pbm');

% Example: Pseudo-metrics with weight files
pw = Doxa.readWeights('../../Doxa.Test/Resources/2JohnC1V3-GroundTruth_PWeights.dat');
rw = Doxa.readWeights('../../Doxa.Test/Resources/2JohnC1V3-GroundTruth_RWeights.dat');
metrics = Doxa.calculatePerformance(gt, binary, precisionWeights=pw, recallWeights=rw);

disp('Performance Metrics:');
disp(metrics);

% Display results
figure('Name', 'Doxa Binarization Demo');
subplot(1, 3, 1);
imshow(imread('../../Doxa.Test/Resources/2JohnC1V3.ppm'));
title('Original');

subplot(1, 3, 2);
imshow(img.toArray());
title('Grayscale');

subplot(1, 3, 3);
imshow(binary.toArray());
title('Sauvola Binary');

% Example: In-place binarization (modifies the image directly)
% Doxa.updateToBinary(Doxa.Algorithms.SAUVOLA, img, window=75, k=0.2);
