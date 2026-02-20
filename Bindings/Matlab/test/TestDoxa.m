classdef TestDoxa < matlab.unittest.TestCase
    % Test suite for the Doxa Matlab bindings.

    properties
        TestData
    end

    methods (TestClassSetup)
        function loadTestData(testCase)
            % Locate test resources
            baseDir = fileparts(mfilename('fullpath'));
            resourceDir = fullfile(baseDir, '..', '..', 'Doxa.Test', 'Resources');

            % Store resource dir for weight files
            testCase.TestData.resourceDir = resourceDir;

            % Create grayscale image using Qt algorithm (matches ground truth generation)
            rgb = imread(fullfile(resourceDir, '2JohnC1V3.ppm'));
            testCase.TestData.rgb = rgb;
            testCase.TestData.grayscaleImage = Doxa.Image(rgb, Doxa.Grayscale.QT);

            % Load ground truth images
            testCase.TestData.groundTruth = Doxa.Image(fullfile(resourceDir, '2JohnC1V3-GroundTruth.pbm'));
            testCase.TestData.sauvolaGroundTruth = Doxa.Image(fullfile(resourceDir, '2JohnC1V3-Sauvola.pbm'));

            % Keep raw ground truth for comparison
            testCase.TestData.sauvolaGroundTruthArray = ...
                uint8(imread(fullfile(resourceDir, '2JohnC1V3-Sauvola.pbm'))) * 255;
        end
    end

    methods (Test)
        function testBinarize(testCase)
            % Tests the binarize function for correctness.
            binary = Doxa.binarize(Doxa.Algorithms.SAUVOLA, ...
                testCase.TestData.grayscaleImage, window=27, k=0.10);

            result = binary.toArray();

            % Verify binary output (only 0 and 255)
            testCase.verifyEqual(unique(result(:)), uint8([0; 255]));

            % Verify against ground truth
            testCase.verifyEqual(result, testCase.TestData.sauvolaGroundTruthArray, ...
                'Binarized image does not match ground truth.');
        end

        function testUpdateToBinary(testCase)
            % Tests the in-place update function.
            img = Doxa.Image(testCase.TestData.grayscaleImage.toArray());
            Doxa.updateToBinary(Doxa.Algorithms.SAUVOLA, img, window=27, k=0.10);

            testCase.verifyEqual(img.toArray(), testCase.TestData.sauvolaGroundTruthArray, ...
                'In-place binarized image does not match ground truth.');
        end

        function testCalculatePerformance(testCase)
            % Tests performance metrics match Python/C++ expected values.
            metrics = Doxa.calculatePerformance( ...
                testCase.TestData.groundTruth, ...
                testCase.TestData.sauvolaGroundTruth);

            testCase.verifyEqual(metrics.accuracy, 97.671, 'RelTol', 1e-2);
            testCase.verifyEqual(metrics.fm, 93.204, 'RelTol', 1e-2);
            testCase.verifyEqual(metrics.recall, 91.381, 'RelTol', 1e-2);
            testCase.verifyEqual(metrics.precision, 95.103, 'RelTol', 1e-2);
            testCase.verifyEqual(metrics.psnr, 16.329, 'RelTol', 1e-2);
            testCase.verifyEqual(metrics.nrm, 0.048, 'RelTol', 1e-2);
            testCase.verifyEqual(metrics.mcc, 0.918, 'RelTol', 1e-2);
            testCase.verifyEqual(metrics.drdm, 1.952, 'RelTol', 1e-2);
        end

        function testPseudoPerformance(testCase)
            % Tests pseudo-metrics with weight files.
            pWeights = Doxa.readWeights(fullfile( ...
                testCase.TestData.resourceDir, '2JohnC1V3-GroundTruth_PWeights.dat'));
            rWeights = Doxa.readWeights(fullfile( ...
                testCase.TestData.resourceDir, '2JohnC1V3-GroundTruth_RWeights.dat'));

            metrics = Doxa.calculatePerformance( ...
                testCase.TestData.groundTruth, ...
                testCase.TestData.sauvolaGroundTruth, ...
                precisionWeights=pWeights, recallWeights=rWeights);

            testCase.verifyEqual(metrics.pseudoFM, 93.393, 'RelTol', 1e-2);
            testCase.verifyEqual(metrics.pseudoRecall, 92.795, 'RelTol', 1e-2);
            testCase.verifyEqual(metrics.pseudoPrecision, 93.998, 'RelTol', 1e-2);
        end

        function testGrayscale(testCase)
            % Tests grayscale conversion matches manual Qt formula.
            rgb = testCase.TestData.rgb;
            img = Doxa.Image(rgb, Doxa.Grayscale.QT);
            result = img.toArray();

            % Compute expected using Qt formula
            r = double(rgb(:,:,1));
            g = double(rgb(:,:,2));
            b = double(rgb(:,:,3));
            expected = uint8((r * 11 + g * 16 + b * 5) / 32);

            testCase.verifyEqual(result, expected, 'AbsTol', uint8(1), ...
                'Grayscale conversion does not match Qt formula.');
        end

        function testImageFromFile(testCase)
            % Tests that loading from file matches loading from array.
            resourceDir = testCase.TestData.resourceDir;

            imgFromFile = Doxa.Image(fullfile(resourceDir, '2JohnC1V3.ppm'), Doxa.Grayscale.QT);
            imgFromArray = Doxa.Image(imread(fullfile(resourceDir, '2JohnC1V3.ppm')), Doxa.Grayscale.QT);

            testCase.verifyEqual(imgFromFile.toArray(), imgFromArray.toArray(), ...
                'File-based and array-based construction produce different results.');
        end

        function testReadWeights(testCase)
            % Tests weight file loading.
            weights = Doxa.readWeights(fullfile( ...
                testCase.TestData.resourceDir, '2JohnC1V3-GroundTruth_PWeights.dat'));

            testCase.verifyFalse(isempty(weights));
            testCase.verifyTrue(isa(weights, 'double'));
            testCase.verifyGreaterThan(numel(weights), 0);
        end

        function testImageDisplay(testCase)
            % Tests that disp works without error.
            img = testCase.TestData.grayscaleImage;
            testCase.verifyWarningFree(@() disp(img));
        end

        function testAllAlgorithmsRun(testCase)
            % Ensures all algorithms can be called without error.
            algorithms = enumeration('Doxa.Algorithms');
            img = testCase.TestData.grayscaleImage;

            for i = 1:length(algorithms)
                alg = algorithms(i);
                testCase.verifyWarningFree(@() Doxa.binarize(alg, img), ...
                    ['Algorithm ' char(alg) ' failed to run.']);
            end
        end
    end
end
