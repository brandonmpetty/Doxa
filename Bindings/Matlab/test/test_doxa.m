classdef testUpdateToBinary < matlab.unittest.TestCase
    methods (Test)
        function testBinarization(testCase)
            imageMatrix = uint8(rand(512, 512) * 255);
            algorithm = ImageBinarization.SAUVOLA;
            ImageBinarization.updateToBinary(imageMatrix, algorithm);
        end
    end
end
