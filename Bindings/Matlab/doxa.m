classdef Doxa
    % Doxa provides a high-level interface to the Doxa Binarization Framework.

    enumeration
        % Binarization algorithms available in the Doxa framework.
        OTSU, BERNSEN, NIBLACK, SAUVOLA, WOLF, NICK, SU, TRSINGH, BATAINEH, ISAUVOLA, WAN, GATOS, ADOTSU
    end

    methods (Static)
        function outputImage = to_binary(algorithm, inputImage, params)
            % TO_BINARY Binarizes a grayscale image, returning a new binary image.
            %   algorithm: An enumeration from Doxa.Algorithms.
            %   inputImage: A 2D uint8 matrix.
            %   params: (Optional) A struct with algorithm-specific parameters.
            if nargin < 3, params = struct(); end
            
            outputImage = binarize(char(algorithm), inputImage, params);
        end

        function update_to_binary(algorithm, imageToUpdate, params)
            % UPDATE_TO_BINARY Binarizes an image in-place.
            %   algorithm: An enumeration from Doxa.Algorithms.
            %   imageToUpdate: A 2D uint8 matrix that will be modified.
            %   params: (Optional) A struct with algorithm-specific parameters.
            if nargin < 3, params = struct(); end

            update_in_place(char(algorithm), imageToUpdate, params);
        end

        function metrics = calculate_performance(groundTruthImage, binaryImage)
            % CALCULATE_PERFORMANCE Calculates metrics between a ground truth and a binary image.
            %   groundTruthImage: A 2D uint8 matrix representing the ideal binary image.
            %   binaryImage: A 2D uint8 matrix produced by a binarization algorithm.
            metrics = calculate_performance(groundTruthImage, binaryImage);
        end
    end
end