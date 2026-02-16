// ?oxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
// Purpose: Compile-time SIMD detection for SSE2, NEON, and WASM SIMD (128-bit)
#ifndef SIMD_H
#define SIMD_H


namespace Doxa::SIMD
{
    // ============================================================================
    // Compile-Time SIMD Detection
    // ============================================================================
    # define DOXA_SIMD 1

    #if defined(__wasm_simd128__)
        // WebAssembly SIMD128
        #define DOXA_SIMD_WASM 1

    #elif defined(__SSE2__) || (defined(_MSC_VER) && defined(_M_X64))
        // x86-64 with SSE2 (always available on x64, standard since Pentium 4)
        #define DOXA_SIMD_SSE2 1

    #elif defined(__ARM_NEON) || defined(__ARM_NEON__) || defined(__aarch64__)
        // ARM NEON (always available on ARM64/aarch64)
        #define DOXA_SIMD_NEON 1

    #else
        // No SIMD options available
        #undef DOXA_SIMD
    #endif

    // ============================================================================
    // SIMD Width Constant
    // All supported SIMD architectures use 128-bit vectors = 16 bytes
    // ============================================================================

    constexpr int SIMD_WIDTH = 16;

} // namespace Doxa::SIMD


#endif // SIMD_H
