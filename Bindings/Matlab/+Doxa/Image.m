classdef Image < handle
    %IMAGE Doxa image container wrapping a C++ Doxa::Image.
    %   Handles the column-major (Matlab) to row-major (C++) memory layout
    %   conversion at construction and extraction boundaries.
    %
    %   Construction:
    %       img = Doxa.Image('file.ppm')                     % from file
    %       img = Doxa.Image('file.ppm', Doxa.Grayscale.QT)  % from color file
    %       img = Doxa.Image(gray_uint8)                      % from 2D uint8
    %       img = Doxa.Image(rgb_uint8)                       % from 3D, default grayscale
    %       img = Doxa.Image(rgb_uint8, Doxa.Grayscale.QT)    % from 3D, specific algorithm
    %
    %   Methods:
    %       arr = img.toArray()   % convert back to Matlab uint8 matrix
    %       disp(img)             % display dimensions
    %
    %   See also Doxa.Grayscale, Doxa.binarize

    properties (Access = {?Doxa.Image})
        Handle uint64 = uint64(0)
    end

    methods
        function obj = Image(input, algorithm)
            %IMAGE Construct a Doxa.Image from a file path, 2D, or 3D uint8 array.

            if nargin == 0
                % Internal: empty construction for fromHandle factory
                return;
            end

            % Load from file if given a path
            if ischar(input) || isstring(input)
                input = imread(input);
                % imread returns logical for PBM; scale to 0/255
                if islogical(input)
                    input = uint8(input) * 255;
                end
                input = uint8(input);
            end

            if ~isa(input, 'uint8')
                error('Doxa:Image:InvalidInput', 'Input must be uint8.');
            end

            if ndims(input) == 3
                % Color image: convert to grayscale
                if nargin < 2
                    algorithm = Doxa.Grayscale.MEAN;
                end
                obj.Handle = image_mex('from_grayscale', char(algorithm), input);
            elseif ismatrix(input)
                % 2D grayscale or binary
                obj.Handle = image_mex('create', input);
            else
                error('Doxa:Image:InvalidInput', 'Input must be a 2D or 3D uint8 array.');
            end
        end

        function arr = toArray(obj)
            %TOARRAY Convert back to a Matlab uint8 matrix.
            %   arr = img.toArray()
            obj.checkValid();
            arr = image_mex('to_array', obj.Handle);
        end

        function w = width(obj)
            %WIDTH Image width in pixels.
            obj.checkValid();
            w = image_mex('width', obj.Handle);
        end

        function h = height(obj)
            %HEIGHT Image height in pixels.
            obj.checkValid();
            h = image_mex('height', obj.Handle);
        end

        function disp(obj)
            %DISP Display Doxa.Image summary.
            if obj.Handle == uint64(0)
                fprintf('  Doxa.Image: [empty]\n');
            else
                fprintf('  Doxa.Image: %dx%d uint8\n', obj.width(), obj.height());
            end
        end

        function delete(obj)
            %DELETE Free the underlying C++ image memory.
            if obj.Handle ~= uint64(0)
                image_mex('destroy', obj.Handle);
                obj.Handle = uint64(0);
            end
        end
    end

    methods (Hidden)
        function h = getHandle(obj)
            %GETHANDLE Return the raw uint64 handle for MEX interop.
            obj.checkValid();
            h = obj.Handle;
        end
    end

    methods (Static, Hidden)
        function obj = fromHandle(handle)
            %FROMHANDLE Wrap an existing C++ image pointer without re-transposing.
            obj = Doxa.Image();
            obj.Handle = handle;
        end
    end

    methods (Access = private)
        function checkValid(obj)
            if obj.Handle == uint64(0)
                error('Doxa:Image:InvalidHandle', 'Image has been destroyed or is uninitialized.');
            end
        end
    end
end
