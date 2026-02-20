// Δoxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
#include "mex.h"
#include "DoxaMexUtils.hpp"

/// <summary>
/// MEX gateway for Doxa.Image lifecycle management.
/// Dispatches on an action string to create, convert, extract, or destroy images.
///
/// Actions:
///   handle = image_mex('create', uint8_2d_array)
///   handle = image_mex('from_grayscale', algorithm_str, uint8_3d_array)
///   uint8_2d = image_mex('to_array', handle)
///   width = image_mex('width', handle)
///   height = image_mex('height', handle)
///   image_mex('destroy', handle)
/// </summary>
void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
    if (nrhs < 1) {
        mexErrMsgIdAndTxt("Doxa:Image:InvalidInput", "Usage: image_mex(action, ...)");
    }

    std::string action = mxArrayToString(prhs[0]);

    if (action == "create")
    {
        // create(uint8_2d_array) → handle
        if (nrhs != 2) {
            mexErrMsgIdAndTxt("Doxa:Image:InvalidInput", "Usage: image_mex('create', uint8_2d_array)");
        }

        Doxa::Image* image = DoxaMexUtils::CreateImageFromMxArray(prhs[1]);
        plhs[0] = DoxaMexUtils::ImageToHandle(image);
    }
    else if (action == "from_grayscale")
    {
        // from_grayscale(algorithm_str, uint8_3d_array) → handle
        if (nrhs != 3) {
            mexErrMsgIdAndTxt("Doxa:Image:InvalidInput", "Usage: image_mex('from_grayscale', algorithm, color_array)");
        }

        std::string algorithmStr = mxArrayToString(prhs[1]);
        Doxa::GrayscaleAlgorithms algorithm = DoxaMexUtils::StringToGrayscaleEnum(algorithmStr);

        Doxa::Image* image = DoxaMexUtils::CreateImageFromGrayscale(prhs[2], algorithm);
        plhs[0] = DoxaMexUtils::ImageToHandle(image);
    }
    else if (action == "to_array")
    {
        // to_array(handle) → uint8_2d_array
        if (nrhs != 2) {
            mexErrMsgIdAndTxt("Doxa:Image:InvalidInput", "Usage: image_mex('to_array', handle)");
        }

        Doxa::Image* image = DoxaMexUtils::HandleToImage(prhs[1]);
        plhs[0] = DoxaMexUtils::ImageToMxArray(*image);
    }
    else if (action == "width")
    {
        // width(handle) → double
        if (nrhs != 2) {
            mexErrMsgIdAndTxt("Doxa:Image:InvalidInput", "Usage: image_mex('width', handle)");
        }

        Doxa::Image* image = DoxaMexUtils::HandleToImage(prhs[1]);
        plhs[0] = mxCreateDoubleScalar(static_cast<double>(image->width));
    }
    else if (action == "height")
    {
        // height(handle) → double
        if (nrhs != 2) {
            mexErrMsgIdAndTxt("Doxa:Image:InvalidInput", "Usage: image_mex('height', handle)");
        }

        Doxa::Image* image = DoxaMexUtils::HandleToImage(prhs[1]);
        plhs[0] = mxCreateDoubleScalar(static_cast<double>(image->height));
    }
    else if (action == "destroy")
    {
        // destroy(handle) → void
        if (nrhs != 2) {
            mexErrMsgIdAndTxt("Doxa:Image:InvalidInput", "Usage: image_mex('destroy', handle)");
        }

        Doxa::Image* image = DoxaMexUtils::HandleToImage(prhs[1]);
        delete image;
    }
    else
    {
        mexErrMsgIdAndTxt("Doxa:Image:UnknownAction", "Unknown action: %s", action.c_str());
    }
}
