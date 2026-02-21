function outputImage = binarize(algorithm, inputImage, options)
%BINARIZE Convert a grayscale Doxa.Image to binary.
%   binary = Doxa.binarize(Doxa.Algorithms.SAUVOLA, img)
%   binary = Doxa.binarize(Doxa.Algorithms.SAUVOLA, img, window=75, k=0.2)
%
%   Common parameters (defaults vary by algorithm):
%       window        - Local window size in pixels (default: 75)
%       k             - Sensitivity parameter (default: 0.2)
%
%   Algorithm-specific parameters:
%       threshold     - Bernsen: global threshold (default: 100)
%       contrastLimit - Bernsen: contrast limit (default: 25)
%       R             - AdOtsu: range parameter (default: 0.1)
%       distance      - AdOtsu: grid distance (default: window/2)
%       minN          - Su: minimum neighborhood (default: window)
%       glyph         - Gatos: estimated stroke width (default: 60)
%
%   See also Doxa.Algorithms, Doxa.updateToBinary, Doxa.Image

    arguments
        algorithm Doxa.Algorithms
        inputImage Doxa.Image
        options.window = []
        options.k = []
        options.threshold = []
        options.contrastLimit = []
        options.R = []
        options.distance = []
        options.minN = []
        options.glyph = []
    end

    params = Doxa.buildParams(options);
    handle = binarize_mex(char(algorithm), inputImage.getHandle(), params);
    outputImage = Doxa.Image.fromHandle(handle);
end
