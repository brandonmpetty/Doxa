// Δoxa Binarization Framework
// License: CC0 2025, "Freely you have received; freely give." - Matt 10:8
#include "mex.h"
#include "doxa_mex_utils.hpp"

/// <summary>
/// MEX function to binarize an image in-place.
/// Matlab Signature: update_in_place(algorithm_name, image_matrix, params_struct)
/// </summary>
void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
    // Validate arguments
    if (nrhs < 2 || nrhs > 3) {
        mexErrMsgIdAndTxt("Doxa:update_in_place:InvalidInput", "Usage: update_in_place(algorithm_name, image_matrix, params_struct(optional))");
    }
    if (nlhs > 0) {
        mexErrMsgIdAndTxt("Doxa:update_in_place:InvalidOutput", "update_in_place modifies the input image and has no return values.");
    }

    // 1. Get Algorithm Enum
    std::string algorithmStr = mxArrayToString(prhs[0]);
    Doxa::Algorithms algorithmEnum = DoxaMexUtils::StringToAlgorithmEnum(algorithmStr);

    // 2. Get Image to modify
    Doxa::Image image = DoxaMexUtils::MxArrayToDoxaImage(prhs[1]);

    // 3. Get Parameters
    const mxArray* paramsMx = (nrhs == 3) ? prhs[2] : nullptr;
    Doxa::Parameters params = DoxaMexUtils::MxStructToParameters(paramsMx);

    // 4. Run algorithm
    Doxa::IAlgorithm* algorithm = Doxa::BinarizationFactory::Algorithm(algorithmEnum);
    algorithm->Initialize(image);
    algorithm->ToBinary(image, params); // Modifies the underlying data of prhs[1]
    delete algorithm;
}
