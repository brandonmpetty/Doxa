// Δoxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
#include "mex.h"
#include "DoxaMexUtils.hpp"

/// <summary>
/// MEX function to binarize a Doxa.Image in-place.
/// Matlab Signature: update_in_place_mex(algorithm_name, image_handle, params_struct)
/// </summary>
void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
    if (nrhs < 2 || nrhs > 3) {
        mexErrMsgIdAndTxt("Doxa:updateToBinary:InvalidInput", "Usage: update_in_place_mex(algorithm, image_handle, params_struct)");
    }
    if (nlhs > 0) {
        mexErrMsgIdAndTxt("Doxa:updateToBinary:InvalidOutput", "updateToBinary modifies the image in-place and has no return values.");
    }

    // 1. Get Algorithm Enum
    std::string algorithmStr = mxArrayToString(prhs[0]);
    Doxa::Algorithms algorithmEnum = DoxaMexUtils::StringToAlgorithmEnum(algorithmStr);

    // 2. Get Image from handle (already row-major, operates in-place)
    Doxa::Image* image = DoxaMexUtils::HandleToImage(prhs[1]);

    // 3. Get Parameters
    const mxArray* paramsMx = (nrhs == 3) ? prhs[2] : nullptr;
    Doxa::Parameters params = DoxaMexUtils::MxStructToParameters(paramsMx);

    // 4. Run algorithm in-place on the C++ buffer
    Doxa::IAlgorithm* algorithm = Doxa::BinarizationFactory::Algorithm(algorithmEnum);
    algorithm->Initialize(*image);
    algorithm->ToBinary(*image, params);
    delete algorithm;
}
