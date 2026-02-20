// Δoxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
#include "mex.h"
#include "DoxaMexUtils.hpp"

/// <summary>
/// MEX function to create a new binarized image from a Doxa.Image handle.
/// Matlab Signature: handle = binarize_mex(algorithm_name, image_handle, params_struct)
/// </summary>
void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
    if (nrhs < 2 || nrhs > 3) {
        mexErrMsgIdAndTxt("Doxa:binarize:InvalidInput", "Usage: binarize_mex(algorithm, image_handle, params_struct)");
    }

    // 1. Get Algorithm Enum
    std::string algorithmStr = mxArrayToString(prhs[0]);
    Doxa::Algorithms algorithmEnum = DoxaMexUtils::StringToAlgorithmEnum(algorithmStr);

    // 2. Get Input Image from handle
    Doxa::Image* grayImage = DoxaMexUtils::HandleToImage(prhs[1]);

    // 3. Get Parameters
    const mxArray* paramsMx = (nrhs == 3) ? prhs[2] : nullptr;
    Doxa::Parameters params = DoxaMexUtils::MxStructToParameters(paramsMx);

    // 4. Create output image and run algorithm
    Doxa::Image* binaryImage = new Doxa::Image(grayImage->width, grayImage->height);
    Doxa::IAlgorithm* algorithm = Doxa::BinarizationFactory::Algorithm(algorithmEnum);
    algorithm->Initialize(*grayImage);
    algorithm->ToBinary(*binaryImage, params);
    delete algorithm;

    // 5. Return handle to the new binary image
    plhs[0] = DoxaMexUtils::ImageToHandle(binaryImage);
}
