// Δoxa Binarization Framework
// License: CC0 2025, "Freely you have received; freely give." - Matt 10:8
#include "mex.h"
#include "doxa_mex_utils.hpp"

/// <summary>
/// MEX function to calculate performance metrics between two images.
/// Matlab Signature: metrics_struct = calculate_performance(ground_truth_matrix, binary_image_matrix)
/// </summary>
void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
    // Validate arguments
    if (nrhs != 2) {
        mexErrMsgIdAndTxt("Doxa:calculate_performance:InvalidInput", "Usage: calculate_performance(ground_truth_matrix, binary_image_matrix)");
    }

    // 1. Get Images
    Doxa::Image groundTruthImage = DoxaMexUtils::MxArrayToDoxaImage(prhs[0]);
    Doxa::Image binaryImage = DoxaMexUtils::MxArrayToDoxaImage(prhs[1]);

    if (groundTruthImage.width != binaryImage.width || groundTruthImage.height != binaryImage.height) {
        mexErrMsgIdAndTxt("Doxa:calculate_performance:MismatchedDimensions", "Input images must have the same dimensions.");
    }

    // 2. Calculate all metrics
    Doxa::ClassifiedPerformance::Classifications classifications;
	Doxa::ClassifiedPerformance::CompareImages(classifications, groundTruthImage, binaryImage);

    // 3. Create output struct
    const char* fieldnames[] = {"accuracy", "fm", "psnr", "nrm", "mcc", "drdm"};
    plhs[0] = mxCreateStructMatrix(1, 1, 6, fieldnames);

    mxSetField(plhs[0], 0, "accuracy", mxCreateDoubleScalar(Doxa::ClassifiedPerformance::CalculateAccuracy(classifications)));
    mxSetField(plhs[0], 0, "fm", mxCreateDoubleScalar(Doxa::ClassifiedPerformance::CalculateFMeasure(classifications)));
    mxSetField(plhs[0], 0, "psnr", mxCreateDoubleScalar(Doxa::ClassifiedPerformance::CalculatePSNR(classifications)));
    mxSetField(plhs[0], 0, "nrm", mxCreateDoubleScalar(Doxa::ClassifiedPerformance::CalculateNRM(classifications)));
    mxSetField(plhs[0], 0, "mcc", mxCreateDoubleScalar(Doxa::ClassifiedPerformance::CalculateMCC(classifications)));
    mxSetField(plhs[0], 0, "drdm", mxCreateDoubleScalar(Doxa::DRDM::CalculateDRDM(groundTruthImage, binaryImage)));
}
