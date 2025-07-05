// Δoxa Binarization Framework
// License: CC0 2025, "Freely you have received; freely give." - Matt 10:8
#ifndef DOXAMEXUTILS_HPP
#define DOXAMEXUTILS_HPP

#include "mex.h"
#include "Doxa/Image.hpp"
#include "Doxa/Parameters.hpp"
#include "Doxa/BinarizationFactory.hpp"
#include "Doxa/ClassifiedPerformance.hpp"
#include "Doxa/DRDM.hpp"
#include <string>
#include <unordered_map>

namespace DoxaMexUtils
{
    /// <summary>
    /// Converts a Matlab mxArray matrix into a Doxa::Image by reference, avoiding a deep copy.
    /// </summary>
    inline Doxa::Image MxArrayToDoxaImage(const mxArray* arr)
    {
        if (!mxIsUint8(arr) || mxGetNumberOfDimensions(arr) != 2) {
            mexErrMsgIdAndTxt("Doxa:InvalidImage", "Image must be a 2D uint8 matrix.");
        }
        const mwSize* dims = mxGetDimensions(arr);
        // Matlab stores matrices in column-major order, so dimensions are swapped.
        int width = static_cast<int>(dims[1]);
        int height = static_cast<int>(dims[0]);
        uint8_t* imageData = static_cast<uint8_t*>(mxGetData(arr));

        return Doxa::Image::Reference(width, height, reinterpret_cast<Doxa::Pixel8*>(imageData));
    }

    /// <summary>
    /// Converts a Doxa::Image into a new Matlab mxArray matrix.
    /// </summary>
    inline mxArray* DoxaImageToMxArray(const Doxa::Image& image)
    {
        mwSize dims[2] = { (mwSize)image.height, (mwSize)image.width };
        mxArray* arr = mxCreateNumericArray(2, dims, mxUINT8_CLASS, mxREAL);
        Doxa::Pixel8* outputData = reinterpret_cast<Doxa::Pixel8*>(mxGetData(arr));
        
        // The Doxa image is already in column-major format compatible with MATLAB
        std::memcpy(outputData, image.data, image.size);

        return arr;
    }

    /// <summary>
    /// Converts a Matlab struct into a Doxa::ParameterMap.
    /// </summary>
    inline Doxa::Parameters MxStructToParameters(const mxArray* aStruct)
    {
        Doxa::ParameterMap paramMap;
        if (aStruct != nullptr && !mxIsEmpty(aStruct)) {
            if (!mxIsStruct(aStruct)) {
                mexErrMsgIdAndTxt("Doxa:InvalidParams", "Parameters must be a struct.");
            }

            int numFields = mxGetNumberOfFields(aStruct);
            for (int i = 0; i < numFields; ++i) {
                const char* fieldName = mxGetFieldNameByNumber(aStruct, i);
                mxArray* fieldValue = mxGetFieldByNumber(aStruct, 0, i);

                if (mxIsScalar(fieldValue)) {
                    if (mxIsDouble(fieldValue)) {
                        paramMap[fieldName] = mxGetScalar(fieldValue);
                    } else { // Treat other numeric types as int
                        paramMap[fieldName] = static_cast<int>(mxGetScalar(fieldValue));
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
}

#endif // DOXAMEXUTILS_HPP
