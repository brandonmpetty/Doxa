classdef Doxa
    enumeration
        SAUVOLA (0)
        NIBLACK (1)
    end
    
    methods (Static)
        function binaryImage = updateToBinary(imageMatrix, algorithm, params)
            % Validate algorithm input
            if ~isa(algorithm, 'ImageBinarization')
                error('ImageBinarization:InvalidAlgorithm', ...
                      'Algorithm must be one of the enumerated types in ImageBinarization.');
            end
            
            % Extract the integer value of the algorithm enum
            algorithmValue = int32(algorithm);
            
            % Call the MEX function
            if nargin < 3 || isempty(params)
                binaryImage = update_to_binary(algorithmValue, imageMatrix);
            else
                binaryImage = update_to_binary(algorithmValue, imageMatrix, params);
            end
        end
    end
end
