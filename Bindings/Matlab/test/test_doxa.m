classdef test_doxa < matlab.unittest.TestCase
    % Test suite for the Doxa Matlab bindings.

    properties
        TestData
    end

    methods (TestClassSetup)
        function addDoxaToPath(testCase)
            % Add the directory containing doxa.m and the MEX files to the path
            baseDir = fileparts(mfilename('fullpath'));
            addpath(baseDir);                         % for doxa.m
            % addpath(fullfile(baseDir, 'Debug'));      % for .mexw64 files in Debug mode
            % addpath(fullfile(baseDir, 'Release'));
            
            % Load test images
            resourceDir = fullfile(baseDir, '..', '..', '..', '..', 'Doxa.Test', 'Resources');

            % Convert to uint8 grayscale - Use Qt algorithm since that was what the PBM were made from
            %testCase.TestData.grayscaleImage = rgb2gray(imread(fullfile(resourceDir, '2JohnC1V3.ppm')));
            rgb = imread(fullfile(resourceDir, '2JohnC1V3.ppm'));
            r = double(rgb(:,:,1));
            g = double(rgb(:,:,2));
            b = double(rgb(:,:,3));
            gray = uint8((r * 11 + g * 16 + b * 5) / 32);
            testCase.TestData.grayscaleImage = gray;

            % Convert a uint8 binary
            testCase.TestData.groundTruth = uint8(imread(fullfile(resourceDir, '2JohnC1V3-GroundTruth.pbm'))) * 255;
            testCase.TestData.sauvolaGroundTruth = uint8(imread(fullfile(resourceDir, '2JohnC1V3-Sauvola.pbm'))) * 255;
        end
    end

    methods (Test)
        function test_to_binary(testCase)
            % Tests the to_binary function for correctness.
            params.window = 27;
            params.k = 0.10;
            
            binaryImage = Doxa.to_binary(Doxa.SAUVOLA, testCase.TestData.grayscaleImage, params);

            %diff = imabsdiff(binaryImage, testCase.TestData.sauvolaGroundTruth);
            %imshow(diff);
            %pause(5);
            
            % Verify that the output is a binary image
            testCase.verifyEqual(unique(binaryImage(:)), uint8([0; 255]));
            
            % Verify against the known-good ground truth image
            testCase.verifyEqual(binaryImage, testCase.TestData.sauvolaGroundTruth, ...
                'The binarized image does not match the ground truth.');
        end

        function test_update_to_binary(testCase)
            % Tests the in-place update function.
            imageToUpdate = testCase.TestData.grayscaleImage;
            params.window = 27;
            params.k = 0.10;

            Doxa.update_to_binary(Doxa.SAUVOLA, imageToUpdate, params);

            testCase.verifyEqual(imageToUpdate, testCase.TestData.sauvolaGroundTruth, ...
                'The in-place binarized image does not match the ground truth.');
        end

        function test_calculate_performance(testCase)
            % Tests the performance calculation.
            metrics = Doxa.calculate_performance(testCase.TestData.groundTruth, testCase.TestData.sauvolaGroundTruth);
            
            testCase.verifyEqual(metrics.accuracy, 97.67, 'RelTol', 1e-2);
            testCase.verifyEqual(metrics.fm, 93.20, 'RelTol', 1e-2);
            testCase.verifyEqual(metrics.psnr, 16.32, 'RelTol', 1e-2);
            testCase.verifyEqual(metrics.nrm, 0.048, 'RelTol', 1e-2);
            testCase.verifyEqual(metrics.mcc, 0.918, 'RelTol', 1e-2);
            testCase.verifyEqual(metrics.drdm, 2.209, 'RelTol', 1e-2);
        end

        function test_all_algorithms_run(testCase)
            % Ensures all algorithms can be called without error.
            algorithms = enumeration('Doxa');
            image = testCase.TestData.grayscaleImage;
            
            for i = 1:length(algorithms)
                alg = algorithms(i);
                testCase.verifyWarningFree(@() Doxa.to_binary(alg, image), ...
                    ['Algorithm ' char(alg) ' failed to run.']);
            end
        end
    end
end