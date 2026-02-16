// Δoxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
// Purpose: Unified 128-bit SIMD operations for SSE2, NEON, and WASM SIMD
#ifndef SIMDOPS_HPP
#define SIMDOPS_HPP

#include "SIMD.h"

// ============================================================================
// Platform-Specific Includes
// ============================================================================

#if defined(DOXA_SIMD_SSE2)
    #include <emmintrin.h>
#elif defined(DOXA_SIMD_NEON)
    #include <arm_neon.h>
#elif defined(DOXA_SIMD_WASM)
    #include <wasm_simd128.h>
#endif


namespace Doxa::SIMD
{
    // ============================================================================
    // Vector Type Definition
    // ============================================================================

    #if defined(DOXA_SIMD_SSE2)
        typedef __m128i vec128;
    #elif defined(DOXA_SIMD_NEON)
        typedef uint8x16_t vec128;
    #elif defined(DOXA_SIMD_WASM)
        typedef v128_t vec128;
    #endif

    // ============================================================================
    // Unified SIMD Macros
    // These provide a common interface across SSE2, NEON, and WASM SIMD.
    // Only macros that are actually used in the codebase are defined.
    // ============================================================================

    #if defined(DOXA_SIMD_SSE2)
        // SSE2 implementations
        #define VEC_LOAD(ptr)         _mm_loadu_si128((const __m128i*)(ptr))
        #define VEC_STORE(ptr, v)     _mm_storeu_si128((__m128i*)(ptr), v)
        #define VEC_SPLAT_U8(val)     _mm_set1_epi8((char)(val))
        #define VEC_CMPEQ_U8(a, b)    _mm_cmpeq_epi8(a, b)
        #define VEC_MIN_U8(a, b)      _mm_min_epu8(a, b)
        #define VEC_AND(a, b)         _mm_and_si128(a, b)
        #define VEC_ANDNOT(a, b)      _mm_andnot_si128(a, b)  // ~a & b
        #define VEC_NOT(a)            _mm_xor_si128(a, _mm_set1_epi8(-1))
        #define VEC_ALL_TRUE_U8(v)    (_mm_movemask_epi8(v) == 0xFFFF)
        #define VEC_LOAD_2x64(p0, p1) _mm_unpacklo_epi64( \
            _mm_loadl_epi64((const __m128i*)(p0)), \
            _mm_loadl_epi64((const __m128i*)(p1)))

    #elif defined(DOXA_SIMD_NEON)
        // ARM NEON implementations
        #define VEC_LOAD(ptr)         vld1q_u8((const uint8_t*)(ptr))
        #define VEC_STORE(ptr, v)     vst1q_u8((uint8_t*)(ptr), v)
        #define VEC_SPLAT_U8(val)     vdupq_n_u8(val)
        #define VEC_CMPEQ_U8(a, b)    vceqq_u8(a, b)
        #define VEC_MIN_U8(a, b)      vminq_u8(a, b)
        #define VEC_AND(a, b)         vandq_u8(a, b)
        #define VEC_ANDNOT(a, b)      vbicq_u8(b, a)  // b & ~a (note: reversed args)
        #define VEC_NOT(a)            vmvnq_u8(a)
        #define VEC_ALL_TRUE_U8(v)    (vminvq_u8(v) == 0xFF)
        #define VEC_LOAD_2x64(p0, p1) vcombine_u8(vld1_u8(p0), vld1_u8(p1))

    #elif defined(DOXA_SIMD_WASM)
        // WebAssembly SIMD implementations
        #define VEC_LOAD(ptr)         wasm_v128_load(ptr)
        #define VEC_STORE(ptr, v)     wasm_v128_store(ptr, v)
        #define VEC_SPLAT_U8(val)     wasm_i8x16_splat(val)
        #define VEC_CMPEQ_U8(a, b)    wasm_i8x16_eq(a, b)
        #define VEC_MIN_U8(a, b)      wasm_u8x16_min(a, b)
        #define VEC_AND(a, b)         wasm_v128_and(a, b)
        #define VEC_ANDNOT(a, b)      wasm_v128_andnot(b, a)  // b & ~a
        #define VEC_NOT(a)            wasm_v128_not(a)
        #define VEC_ALL_TRUE_U8(v)    (wasm_i8x16_bitmask(v) == 0xFFFF)
        #define VEC_LOAD_2x64(p0, p1) wasm_v128_load64_lane(p1, wasm_v128_load64_zero(p0), 1)
    #endif

    #if defined(DOXA_SIMD)
        // Check if all bytes in two vectors are equal
        #define VEC_ALL_EQ_U8(a, b)   VEC_ALL_TRUE_U8(VEC_CMPEQ_U8(a, b))
    #endif

    // ============================================================================
    // Helper Functions - Platform-Specific Implementations
    // ============================================================================

    #if defined(DOXA_SIMD)

        // Horizontal Sum of Bytes
        inline int vec_hsum_u8(vec128 v) {
            #if defined(DOXA_SIMD_SSE2)
                vec128 sad = _mm_sad_epu8(v, _mm_setzero_si128());
                return _mm_cvtsi128_si32(sad) + _mm_extract_epi16(sad, 4);

            #elif defined(DOXA_SIMD_NEON)
                return vaddvq_u8(v);

            #elif defined(DOXA_SIMD_WASM)
                vec128 sum16 = wasm_u16x8_extadd_pairwise_u8x16(v);
                vec128 sum32 = wasm_i32x4_extadd_pairwise_i16x8(sum16);

                return wasm_i32x4_extract_lane(sum32, 0) +
                       wasm_i32x4_extract_lane(sum32, 1) +
                       wasm_i32x4_extract_lane(sum32, 2) +
                       wasm_i32x4_extract_lane(sum32, 3);
            #endif
        }

    #endif // DOXA_SIMD


} // namespace Doxa::SIMD


#endif // SIMDOPS_HPP
