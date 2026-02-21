function metrics = calculatePerformance(gtImage, binaryImage, options)
%CALCULATEPERFORMANCE Calculate binarization quality metrics.
%   metrics = Doxa.calculatePerformance(gt, binary)
%   metrics = Doxa.calculatePerformance(gt, binary, precisionWeights=pw, recallWeights=rw)
%
%   Returns a struct with all standard metrics:
%       accuracy, fm, recall, precision, psnr, nrm, mcc, drdm
%
%   When precisionWeights and recallWeights are provided, pseudo-metrics
%   are also included: pseudoFM, pseudoPrecision, pseudoRecall
%
%   See also Doxa.Image, Doxa.readWeights

    arguments
        gtImage Doxa.Image
        binaryImage Doxa.Image
        options.precisionWeights double = []
        options.recallWeights double = []
    end

    metrics = calculate_performance_mex( ...
        gtImage.getHandle(), binaryImage.getHandle(), ...
        options.precisionWeights, options.recallWeights);
end
