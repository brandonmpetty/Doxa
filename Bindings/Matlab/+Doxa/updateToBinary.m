function updateToBinary(algorithm, inputImage, options)
%UPDATETOBINARY Binarize a Doxa.Image in-place.
%   Doxa.updateToBinary(Doxa.Algorithms.SAUVOLA, img)
%   Doxa.updateToBinary(Doxa.Algorithms.SAUVOLA, img, window=75, k=0.2)
%
%   Modifies the Doxa.Image directly. No new image is created.
%   See Doxa.binarize for available parameters.
%
%   See also Doxa.Algorithms, Doxa.binarize, Doxa.Image

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
    update_to_binary_mex(char(algorithm), inputImage.getHandle(), params);
end
