function weights = readWeights(filePath)
%READWEIGHTS Load a DIBCO-format weight file for pseudo-metrics.
%   pw = Doxa.readWeights('precision_weights.dat')
%   rw = Doxa.readWeights('recall_weights.dat')
%
%   Returns a double column vector of weights.
%
%   See also Doxa.calculatePerformance

    arguments
        filePath {mustBeTextScalar, mustBeFile}
    end

    fid = fopen(filePath, 'r');
    weights = fscanf(fid, '%f');
    fclose(fid);
end
