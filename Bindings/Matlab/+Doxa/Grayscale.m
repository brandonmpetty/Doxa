classdef Grayscale
    %GRAYSCALE Grayscale conversion algorithms available in the Doxa framework.
    %
    %   Algorithms:
    %       Doxa.Grayscale.MEAN      - Mean of R, G, B (Gleam/Intensity)
    %       Doxa.Grayscale.QT        - Qt framework formula (default)
    %       Doxa.Grayscale.BT601     - ITU-R BT.601 (NTSC)
    %       Doxa.Grayscale.BT709     - ITU-R BT.709 (sRGB)
    %       Doxa.Grayscale.BT2100    - ITU-R BT.2100
    %       Doxa.Grayscale.VALUE     - HSV Value (max channel)
    %       Doxa.Grayscale.LUSTER    - HLS Lightness
    %       Doxa.Grayscale.LIGHTNESS - CIELAB/CIELUV Lightness
    %       Doxa.Grayscale.MINAVG    - Min-Average (for multi-color text)
    %
    %   See also Doxa.Image

    enumeration
        MEAN
        QT
        BT601
        BT709
        BT2100
        VALUE
        LUSTER
        LIGHTNESS
        MINAVG
    end
end
