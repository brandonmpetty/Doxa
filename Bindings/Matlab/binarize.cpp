// Δoxa Binarization Framework
// License: CC0 2025, "Freely you have received; freely give." - Matt 10:8
#include "mex.h"
#include "doxa_mex_utils.hpp"

/// <summary>
/// MEX function to create a new binarized image from a grayscale image.
/// Matlab Signature: binary_image = binarize(algorithm_name, image_matrix, params_struct)
/// </summary>
void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
    // Validate arguments
    if (nrhs < 2 || nrhs > 3) {
        mexErrMsgIdAndTxt("Doxa:binarize:InvalidInput", "Usage: binarize(algorithm_name, image_matrix, params_struct(optional))");
    }

    // 1. Get Algorithm Enum
    std::string algorithmStr = mxArrayToString(prhs[0]);
    Doxa::Algorithms algorithmEnum = DoxaMexUtils::StringToAlgorithmEnum(algorithmStr);

    // 2. Get Input Image
    Doxa::Image grayScaleImage = DoxaMexUtils::MxArrayToDoxaImage(prhs[1]);

    // 3. Get Parameters
    const mxArray* paramsMx = (nrhs == 3) ? prhs[2] : nullptr;
    Doxa::Parameters params = DoxaMexUtils::MxStructToParameters(paramsMx);

    // 4. Create output image and run algorithm
    Doxa::Image binaryImage(grayScaleImage.width, grayScaleImage.height);
    Doxa::IAlgorithm* algorithm = Doxa::BinarizationFactory::Algorithm(algorithmEnum);
    algorithm->Initialize(grayScaleImage);
    algorithm->ToBinary(binaryImage, params);
    delete algorithm;

    // 5. Return the new binary image
    plhs[0] = DoxaMexUtils::DoxaImageToMxArray(binaryImage);
}
