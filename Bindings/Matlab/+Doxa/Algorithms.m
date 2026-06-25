classdef Algorithms
    %ALGORITHMS Binarization algorithms available in the Doxa framework.
    %
    %   Global Thresholding:
    %       Doxa.Algorithms.OTSU
    %
    %   Local Adaptive Thresholding:
    %       Doxa.Algorithms.BERNSEN, NIBLACK, SAUVOLA, WOLF, NICK, SU,
    %       TRSINGH, BATAINEH, PHANSALKAR, ISAUVOLA, WAN, GATOS, ADOTSU,
    %       WELLNER, BRADLEY, FENG
    %
    %   Edge-Based Thresholding:
    %       Doxa.Algorithms.XDOG
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
        PHANSALKAR
        ISAUVOLA
        WAN
        GATOS
        ADOTSU
        WELLNER
        BRADLEY
        FENG
        XDOG
    end
end
