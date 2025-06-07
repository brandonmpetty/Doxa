#include "mex.h"
#include "Doxa/BinarizationFactory.hpp"
#include "Doxa/ClassifiedPerformance.hpp"
#include "Doxa/DRDM.hpp"

using namespace Doxa;


// Main entry point for the MEX function
void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]) {
    // Input validation
    if (nrhs < 2 || nrhs > 3) {
        mexErrMsgIdAndTxt("update_to_binary:InvalidInput", 
            "Usage: update_to_binary(algorithm, imageMatrix, paramsStruct(optional))");
    }

    // 1. Extract algorithm string
    if (!mxIsChar(prhs[0])) {
        mexErrMsgIdAndTxt("update_to_binary:InvalidAlgorithm", "Algorithm must be a string.");
    }
    std::string algorithmStr(mxArrayToString(prhs[0]));

    // Map algorithm strings to C++ enum values
    Algorithms algorithm;
    if (algorithmStr == "SAUVOLA") {
        algorithm = Algorithms::SAUVOLA;
    } else if (algorithmStr == "NIBLACK") {
        algorithm = Algorithms::NIBLACK;
    } else {
        mexErrMsgIdAndTxt("update_to_binary:UnknownAlgorithm", "Unsupported algorithm: %s", algorithmStr.c_str());
    }

    // 2. Extract image matrix
    if (!mxIsUint8(prhs[1]) || mxGetNumberOfDimensions(prhs[1]) != 2) {
        mexErrMsgIdAndTxt("update_to_binary:InvalidImage", 
            "Image must be a 2D uint8 matrix.");
    }
    const mwSize* dims = mxGetDimensions(prhs[1]);
    int height = static_cast<int>(dims[0]);
    int width = static_cast<int>(dims[1]);
    uint8_t* imageData = static_cast<uint8_t*>(mxGetData(prhs[1]));

    // Wrap the image in the C++ Image reference class
    Image image = Image::Reference(width, height, reinterpret_cast<Pixel8*>(imageData));

    // 3. Extract optional parameters
    ParameterMap params;
    if (nrhs == 3 && !mxIsEmpty(prhs[2])) {
        if (!mxIsStruct(prhs[2])) {
            mexErrMsgIdAndTxt("update_to_binary:InvalidParams", "Parameters must be a struct.");
        }

        mxArray* field;
        const char* fieldName;
        mwSize numFields = mxGetNumberOfFields(prhs[2]);
        for (mwSize i = 0; i < numFields; ++i) {
            fieldName = mxGetFieldNameByNumber(prhs[2], i);
            field = mxGetFieldByNumber(prhs[2], 0, i);

            if (mxIsDouble(field)) {
                params[fieldName] = mxGetScalar(field);
            } else if (mxIsInt32(field)) {
                params[fieldName] = static_cast<int>(mxGetScalar(field));
            } else {
                mexErrMsgIdAndTxt("update_to_binary:InvalidParamValue", 
                    "Only double and int32 parameter types are supported.");
            }
        }
    }

    // 4. Call the C++ library function
    IAlgorithm* algorithmPtr = BinarizationFactory::Algorithm(algorithm);
	algorithmPtr->Initialize(image);
	algorithmPtr->ToBinary(image, params);

    // 5. Return the updated binary image (in-place modification)
    //plhs[0] = mxDuplicateArray(prhs[1]); // Return the same input matrix as output
}
