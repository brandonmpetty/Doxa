// Δoxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
#include "mex.h"
#include "DoxaMexUtils.hpp"
#include "Doxa/PseudoWeights.hpp"

/// <summary>
/// MEX function to generate pseudo precision/recall weights from a Doxa.Image ground truth.
/// The weights are returned as double column vectors, ready to pass to
/// calculate_performance_mex for pseudo-metrics - no .dat file required.
///
/// Signature:
///   [p_weights, r_weights] = pseudo_weights_mex(gt_handle)
/// </summary>
void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
    if (nrhs != 1) {
        mexErrMsgIdAndTxt("Doxa:pseudoWeights:InvalidInput",
            "Usage: pseudo_weights_mex(gt_handle)");
    }

    // 1. Get ground truth Image from handle
    Doxa::Image* groundTruthImage = DoxaMexUtils::HandleToImage(prhs[0]);

    // 2. Generate both weight maps (recall chain is computed once and reused)
    std::vector<double> gw, pw;
    Doxa::PseudoWeights::Generate(gw, pw, *groundTruthImage);

    // 3. Return as double column vectors (precision first, then recall)
    plhs[0] = DoxaMexUtils::DoubleVectorToMxArray(pw);

    if (nlhs > 1) {
        plhs[1] = DoxaMexUtils::DoubleVectorToMxArray(gw);
    }
}
