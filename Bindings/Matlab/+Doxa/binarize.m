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
%       p             - Phansalkar: foreground sensitivity (default: 3.0)
%       q             - Phansalkar: background sensitivity (default: 10.0)
%       s             - Wellner: moving-average stride (default: floor-pow2(width/8))
%       t             - Wellner: threshold percentage (default: 15)
%       secondaryWindowMultiplier - Feng: secondary window multiplier in primary cells (default: 3)
%       alpha1        - Feng: mean-shift weight (default: 0.12)
%       k1            - Feng: alpha2 coefficient (default: 0.025)
%       k2            - Feng: alpha3 coefficient (default: 0.2)
%       gamma         - Feng: sRatio exponent (default: 2.0)
%       noiseFloor    - Feng: lower bound on Rs for flat regions (default: 10.0)
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
        options.p = []
        options.q = []
        options.s = []
        options.t = []
        options.secondaryWindowMultiplier = []
        options.alpha1 = []
        options.k1 = []
        options.k2 = []
        options.gamma = []
        options.noiseFloor = []
    end

    params = Doxa.buildParams(options);
    handle = binarize_mex(char(algorithm), inputImage.getHandle(), params);
    outputImage = Doxa.Image.fromHandle(handle);
end
