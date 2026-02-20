// Δoxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
#include "mex.h"
#include "DoxaMexUtils.hpp"

/// <summary>
/// MEX function to calculate performance metrics between two Doxa.Image handles.
///
/// Signatures:
///   metrics = calculate_performance_mex(gt_handle, bin_handle)
///   metrics = calculate_performance_mex(gt_handle, bin_handle, p_weights, r_weights)
/// </summary>
void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
    if (nrhs != 2 && nrhs != 4) {
        mexErrMsgIdAndTxt("Doxa:calculatePerformance:InvalidInput",
            "Usage: calculate_performance_mex(gt_handle, bin_handle, [p_weights, r_weights])");
    }

    // 1. Get Images from handles
    Doxa::Image* groundTruthImage = DoxaMexUtils::HandleToImage(prhs[0]);
    Doxa::Image* binaryImage = DoxaMexUtils::HandleToImage(prhs[1]);

    if (groundTruthImage->width != binaryImage->width || groundTruthImage->height != binaryImage->height) {
        mexErrMsgIdAndTxt("Doxa:calculatePerformance:MismatchedDimensions",
            "Input images must have the same dimensions.");
    }

    // 2. Compute classifications (with or without pseudo-weights)
    Doxa::ClassifiedPerformance::Classifications classifications;
    bool hasPseudoWeights = false;

    if (nrhs == 4 && !mxIsEmpty(prhs[2]) && !mxIsEmpty(prhs[3])) {
        std::vector<double> precisionWeights = DoxaMexUtils::MxArrayToDoubleVector(prhs[2]);
        std::vector<double> recallWeights = DoxaMexUtils::MxArrayToDoubleVector(prhs[3]);

        Doxa::ClassifiedPerformance::CompareImages(
            classifications, *groundTruthImage, *binaryImage, precisionWeights, recallWeights);
        hasPseudoWeights = true;
    } else {
        Doxa::ClassifiedPerformance::CompareImages(
            classifications, *groundTruthImage, *binaryImage);
    }

    // 3. Build output struct with all metrics
    int numFields = hasPseudoWeights ? 11 : 8;
    const char* fieldNames[] = {
        "accuracy", "fm", "recall", "precision", "psnr", "nrm", "mcc", "drdm",
        "pseudoFM", "pseudoPrecision", "pseudoRecall"
    };

    plhs[0] = mxCreateStructMatrix(1, 1, numFields, fieldNames);

    mxSetField(plhs[0], 0, "accuracy",  mxCreateDoubleScalar(Doxa::ClassifiedPerformance::CalculateAccuracy(classifications)));
    mxSetField(plhs[0], 0, "fm",        mxCreateDoubleScalar(Doxa::ClassifiedPerformance::CalculateFMeasure(classifications)));
    mxSetField(plhs[0], 0, "recall",    mxCreateDoubleScalar(Doxa::ClassifiedPerformance::CalculateRecall(classifications)));
    mxSetField(plhs[0], 0, "precision", mxCreateDoubleScalar(Doxa::ClassifiedPerformance::CalculatePrecision(classifications)));
    mxSetField(plhs[0], 0, "psnr",      mxCreateDoubleScalar(Doxa::ClassifiedPerformance::CalculatePSNR(classifications)));
    mxSetField(plhs[0], 0, "nrm",       mxCreateDoubleScalar(Doxa::ClassifiedPerformance::CalculateNRM(classifications)));
    mxSetField(plhs[0], 0, "mcc",       mxCreateDoubleScalar(Doxa::ClassifiedPerformance::CalculateMCC(classifications)));
    mxSetField(plhs[0], 0, "drdm",      mxCreateDoubleScalar(Doxa::DRDM::CalculateDRDM(*groundTruthImage, *binaryImage)));

    if (hasPseudoWeights) {
        mxSetField(plhs[0], 0, "pseudoFM",        mxCreateDoubleScalar(Doxa::ClassifiedPerformance::CalculatePseudoFMeasure(classifications)));
        mxSetField(plhs[0], 0, "pseudoPrecision",  mxCreateDoubleScalar(Doxa::ClassifiedPerformance::CalculatePseudoPrecision(classifications)));
        mxSetField(plhs[0], 0, "pseudoRecall",     mxCreateDoubleScalar(Doxa::ClassifiedPerformance::CalculatePseudoRecall(classifications)));
    }
}
