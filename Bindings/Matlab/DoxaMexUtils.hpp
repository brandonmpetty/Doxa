// Δoxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
#ifndef DOXAMEXUTILS_HPP
#define DOXAMEXUTILS_HPP

#include "mex.h"
#include "Doxa/Image.hpp"
#include "Doxa/Parameters.hpp"
#include "Doxa/BinarizationFactory.hpp"
#include "Doxa/ClassifiedPerformance.hpp"
#include "Doxa/DRDM.hpp"
#include "Doxa/Grayscale.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <cstring>

namespace DoxaMexUtils
{
    /// <summary>
    /// Casts a uint64 scalar mxArray handle to a Doxa::Image pointer with validation.
    /// </summary>
    inline Doxa::Image* HandleToImage(const mxArray* arr)
    {
        if (!mxIsUint64(arr) || !mxIsScalar(arr)) {
            mexErrMsgIdAndTxt("Doxa:InvalidHandle", "Expected a Doxa.Image handle (uint64 scalar).");
        }
        uint64_t handle = *static_cast<uint64_t*>(mxGetData(arr));
        if (handle == 0) {
            mexErrMsgIdAndTxt("Doxa:NullHandle", "Image handle is null or has been destroyed.");
        }
        return reinterpret_cast<Doxa::Image*>(static_cast<uintptr_t>(handle));
    }

    /// <summary>
    /// Wraps a Doxa::Image pointer into a uint64 scalar mxArray.
    /// </summary>
    inline mxArray* ImageToHandle(Doxa::Image* image)
    {
        mxArray* arr = mxCreateNumericMatrix(1, 1, mxUINT64_CLASS, mxREAL);
        *static_cast<uint64_t*>(mxGetData(arr)) = static_cast<uint64_t>(reinterpret_cast<uintptr_t>(image));
        return arr;
    }

    /// <summary>
    /// Creates a new Doxa::Image from a Matlab 2D uint8 array, transposing from column-major to row-major.
    /// </summary>
    inline Doxa::Image* CreateImageFromMxArray(const mxArray* arr)
    {
        if (!mxIsUint8(arr) || mxGetNumberOfDimensions(arr) != 2) {
            mexErrMsgIdAndTxt("Doxa:InvalidImage", "Image must be a 2D uint8 matrix.");
        }
        const mwSize* dims = mxGetDimensions(arr);
        int height = static_cast<int>(dims[0]);
        int width = static_cast<int>(dims[1]);
        const uint8_t* matlabData = static_cast<const uint8_t*>(mxGetData(arr));

        Doxa::Image* image = new Doxa::Image(width, height);

        // Transpose: col-major (Matlab) → row-major (Doxa)
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                image->data[row * width + col] = matlabData[col * height + row];
            }
        }

        return image;
    }

    /// <summary>
    /// Creates a new Matlab 2D uint8 mxArray from a Doxa::Image, transposing from row-major to column-major.
    /// </summary>
    inline mxArray* ImageToMxArray(const Doxa::Image& image)
    {
        mwSize dims[2] = { (mwSize)image.height, (mwSize)image.width };
        mxArray* arr = mxCreateNumericArray(2, dims, mxUINT8_CLASS, mxREAL);
        uint8_t* matlabData = static_cast<uint8_t*>(mxGetData(arr));

        // Transpose: row-major (Doxa) → col-major (Matlab)
        for (int row = 0; row < image.height; ++row) {
            for (int col = 0; col < image.width; ++col) {
                matlabData[col * image.height + row] = image.data[row * image.width + col];
            }
        }

        return arr;
    }

    /// <summary>
    /// Creates a new Doxa::Image from a Matlab 3D uint8 color array by converting to grayscale.
    /// Matlab stores [H,W,C] as C separate column-major planes; Doxa expects interleaved row-major RGB.
    /// </summary>
    inline Doxa::Image* CreateImageFromGrayscale(const mxArray* arr, Doxa::GrayscaleAlgorithms algorithm)
    {
        if (!mxIsUint8(arr)) {
            mexErrMsgIdAndTxt("Doxa:InvalidImage", "Color image must be a uint8 array.");
        }
        mwSize ndims = mxGetNumberOfDimensions(arr);
        const mwSize* dims = mxGetDimensions(arr);

        if (ndims != 3 || (dims[2] != 3 && dims[2] != 4)) {
            mexErrMsgIdAndTxt("Doxa:InvalidImage", "Color image must be [H,W,3] or [H,W,4] uint8.");
        }

        int height = static_cast<int>(dims[0]);
        int width = static_cast<int>(dims[1]);
        int channels = static_cast<int>(dims[2]);
        const uint8_t* matlabData = static_cast<const uint8_t*>(mxGetData(arr));

        int pixelCount = width * height;

        // Reorder Matlab planar col-major to interleaved row-major
        std::vector<Doxa::Pixel8> interleaved(pixelCount * channels);
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                int doxaIdx = (row * width + col) * channels;
                for (int c = 0; c < channels; ++c) {
                    interleaved[doxaIdx + c] = matlabData[c * pixelCount + col * height + row];
                }
            }
        }

        // Convert to grayscale using Doxa
        Doxa::Image* image = new Doxa::Image(width, height);
        Doxa::Grayscale::ToGrayscale(image->data, interleaved.data(), width, height, channels, algorithm);

        return image;
    }

    /// <summary>
    /// Converts a Matlab double array to a std::vector of doubles.
    /// </summary>
    inline std::vector<double> MxArrayToDoubleVector(const mxArray* arr)
    {
        if (!mxIsDouble(arr)) {
            mexErrMsgIdAndTxt("Doxa:InvalidWeights", "Weights must be a double array.");
        }
        double* data = mxGetPr(arr);
        size_t n = mxGetNumberOfElements(arr);
        return std::vector<double>(data, data + n);
    }

    /// <summary>
    /// Converts a Matlab struct into a Doxa::ParameterMap.
    /// </summary>
    /// <summary>
    /// Maps Matlab-friendly field names to C++ parameter names.
    /// Matlab struct fields cannot contain hyphens, so camelCase is mapped here.
    /// </summary>
    inline std::string MapParameterName(const std::string& matlabName)
    {
        static const std::unordered_map<std::string, std::string> nameMap = {
            {"contrastLimit", "contrast-limit"}
        };

        auto it = nameMap.find(matlabName);
        return (it != nameMap.end()) ? it->second : matlabName;
    }

    inline Doxa::Parameters MxStructToParameters(const mxArray* aStruct)
    {
        Doxa::ParameterMap paramMap;
        if (aStruct != nullptr && !mxIsEmpty(aStruct)) {
            if (!mxIsStruct(aStruct)) {
                mexErrMsgIdAndTxt("Doxa:InvalidParams", "Parameters must be a struct.");
            }

            int numFields = mxGetNumberOfFields(aStruct);
            for (int i = 0; i < numFields; ++i) {
                const char* matlabFieldName = mxGetFieldNameByNumber(aStruct, i);
                mxArray* fieldValue = mxGetFieldByNumber(aStruct, 0, i);
                std::string paramName = MapParameterName(matlabFieldName);

                if (mxIsScalar(fieldValue)) {
                    if (mxIsDouble(fieldValue)) {
                        paramMap[paramName] = mxGetScalar(fieldValue);
                    } else { // Treat other numeric types as int
                        paramMap[paramName] = static_cast<int>(mxGetScalar(fieldValue));
                    }
                }
            }
        }
        return Doxa::Parameters(paramMap);
    }

    /// <summary>
    /// Converts a string algorithm name to a Doxa::Algorithms enum.
    /// </summary>
    inline Doxa::Algorithms StringToAlgorithmEnum(const std::string& algorithmStr)
    {
        static const std::unordered_map<std::string, Doxa::Algorithms> algorithmMap = {
            {"OTSU", Doxa::Algorithms::OTSU},       {"BERNSEN", Doxa::Algorithms::BERNSEN},
            {"NIBLACK", Doxa::Algorithms::NIBLACK}, {"SAUVOLA", Doxa::Algorithms::SAUVOLA},
            {"WOLF", Doxa::Algorithms::WOLF},       {"NICK", Doxa::Algorithms::NICK},
            {"SU", Doxa::Algorithms::SU},           {"TRSINGH", Doxa::Algorithms::TRSINGH},
            {"BATAINEH", Doxa::Algorithms::BATAINEH}, {"ISAUVOLA", Doxa::Algorithms::ISAUVOLA},
            {"WAN", Doxa::Algorithms::WAN},         {"GATOS", Doxa::Algorithms::GATOS},
            {"ADOTSU", Doxa::Algorithms::ADOTSU}
        };

        auto it = algorithmMap.find(algorithmStr);
        if (it == algorithmMap.end()) {
            mexErrMsgIdAndTxt("Doxa:UnknownAlgorithm", "Unknown algorithm specified: %s", algorithmStr.c_str());
        }
        return it->second;
    }

    /// <summary>
    /// Converts a string grayscale algorithm name to a Doxa::GrayscaleAlgorithms enum.
    /// </summary>
    inline Doxa::GrayscaleAlgorithms StringToGrayscaleEnum(const std::string& algorithmStr)
    {
        static const std::unordered_map<std::string, Doxa::GrayscaleAlgorithms> grayscaleMap = {
            {"MEAN", Doxa::GrayscaleAlgorithms::MEAN},
            {"QT", Doxa::GrayscaleAlgorithms::QT},
            {"BT601", Doxa::GrayscaleAlgorithms::BT601},
            {"BT709", Doxa::GrayscaleAlgorithms::BT709},
            {"BT2100", Doxa::GrayscaleAlgorithms::BT2100},
            {"VALUE", Doxa::GrayscaleAlgorithms::VALUE},
            {"LUSTER", Doxa::GrayscaleAlgorithms::LUSTER},
            {"LIGHTNESS", Doxa::GrayscaleAlgorithms::LIGHTNESS},
            {"MINAVG", Doxa::GrayscaleAlgorithms::MINAVG}
        };

        auto it = grayscaleMap.find(algorithmStr);
        if (it == grayscaleMap.end()) {
            mexErrMsgIdAndTxt("Doxa:UnknownGrayscale", "Unknown grayscale algorithm: %s", algorithmStr.c_str());
        }
        return it->second;
    }
}

#endif // DOXAMEXUTILS_HPP
