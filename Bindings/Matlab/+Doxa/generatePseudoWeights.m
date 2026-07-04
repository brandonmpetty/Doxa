function [precisionWeights, recallWeights] = generatePseudoWeights(gtImage)
%GENERATEPSEUDOWEIGHTS Generate pseudo precision/recall weights from a ground truth.
%   [pw, rw] = Doxa.generatePseudoWeights(gt)
%
%   Generates the pseudo-metric weight maps from just a ground truth image,
%   just as if they had been read from .dat files. The returned double column
%   vectors plug straight into Doxa.calculatePerformance:
%
%       [pw, rw] = Doxa.generatePseudoWeights(gt);
%       metrics  = Doxa.calculatePerformance(gt, binary, ...
%                      precisionWeights=pw, recallWeights=rw);
%
%   See also Doxa.Image, Doxa.calculatePerformance, Doxa.readWeights

    arguments
        gtImage Doxa.Image
    end

    [precisionWeights, recallWeights] = pseudo_weights_mex(gtImage.getHandle());
end
