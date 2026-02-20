classdef Algorithms
    %ALGORITHMS Binarization algorithms available in the Doxa framework.
    %
    %   Global Thresholding:
    %       Doxa.Algorithms.OTSU
    %
    %   Local Adaptive Thresholding:
    %       Doxa.Algorithms.BERNSEN, NIBLACK, SAUVOLA, WOLF, NICK, SU,
    %       TRSINGH, BATAINEH, ISAUVOLA, WAN, GATOS, ADOTSU
    %
    %   See also Doxa.binarize

    enumeration
        OTSU
        BERNSEN
        NIBLACK
        SAUVOLA
        WOLF
        NICK
        SU
        TRSINGH
        BATAINEH
        ISAUVOLA
        WAN
        GATOS
        ADOTSU
    end
end
