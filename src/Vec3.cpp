#include <ran/Vec3.hpp>

#include <immintrin.h>
#include <math.h>

namespace ran {

Vec3::Vec3 (float f) {
    __m128 xmm = _mm_set1_ps(f);
    _mm_store_ps(dim, xmm);
    dim[3] = 0.f;
}

Vec3::Vec3 (const Vec3 &vec) {
    for (int i = 0; i < 4; i++) {
        dim[i] = vec.dim[i];
    }
}

Vec3::Vec3 (float x, float y, float z)
    : x(x), y(y), z(z) {
    dim[3] = 0.f;
}

void Vec3::add (const Vec3 &vec) __restrict {
    for (int i = 0; i < 4; i++) {
        dim[i] += vec.dim[i];
    }
}

void Vec3::sub (const Vec3 &vec) __restrict {
    for (int i = 0; i < 4; i++) {
        dim[i] -= vec.dim[i];
    }
}

void Vec3::multiply (float f) {
    for (int i = 0; i < 4; i++) {
        dim[i] *= f;
    }
}

void Vec3::cross (const Vec3 &vec) {
    __m128 xmm1 = _mm_load_ps(dim);
    __m128 xmm2 = _mm_load_ps(vec.dim);
    // Shuffle
    __m128 xmm3 = _mm_shuffle_ps(xmm1, xmm1, _MM_SHUFFLE(3, 0, 2, 1));
    __m128 xmm4 = _mm_shuffle_ps(xmm2, xmm2, _MM_SHUFFLE(3, 1, 0, 2));
    __m128 xmm5 = _mm_shuffle_ps(xmm1, xmm1, _MM_SHUFFLE(3, 1, 0, 2));
    __m128 xmm6 = _mm_shuffle_ps(xmm2, xmm2, _MM_SHUFFLE(3, 0, 2, 1));
    // (x1y2, x2y0, x0y1)
    xmm1 = _mm_mul_ps(xmm3, xmm4);
    // (x2y1, x0y2, x1y0)
    xmm2 = _mm_mul_ps(xmm5, xmm6);
    // Subtract
    xmm1 = _mm_sub_ps(xmm1, xmm2);
    _mm_store_ps(dim, xmm1);
}

void Vec3::invert () {
    for (int i = 0; i < 4; i++) {
        dim[i] = 1. / dim[i];
    }
}

void Vec3::normalize () {
    __m128 xmm1 = _mm_load_ps(dim);
    // Square
    __m128 xmm2 = _mm_mul_ps(xmm1, xmm1);
    // Horizontal add
    xmm2 = _mm_hadd_ps(xmm2, xmm2);
    xmm2 = _mm_hadd_ps(xmm2, xmm2);
    // Inverse square root
    xmm2 = _mm_rsqrt_ps(xmm2);
    // Multiply
    xmm1 = _mm_mul_ps(xmm1, xmm2);
    _mm_store_ps(dim, xmm1);
}

float Vec3::dot (const Vec3 &vec) const {
    __m128 xmm1 = _mm_load_ps(dim);
    __m128 xmm2 = _mm_load_ps(vec.dim);
    // Multiply
    xmm1 = _mm_mul_ps(xmm1, xmm2);
    // Horizontal add
    xmm1 = _mm_hadd_ps(xmm1, xmm1);
    xmm1 = _mm_hadd_ps(xmm1, xmm1);
    return _mm_cvtss_f32(xmm1);
}

float Vec3::magnitude () const {
    __m128 xmm = _mm_load_ps(dim);
    // Square
    xmm = _mm_mul_ps(xmm, xmm);
    // Horizontal add
    xmm = _mm_hadd_ps(xmm, xmm);
    xmm = _mm_hadd_ps(xmm, xmm);
    // Square root
    xmm = _mm_sqrt_ps(xmm);
    return _mm_cvtss_f32(xmm);
}

bool Vec3::zero () const {
    __m128 xmm = _mm_load_ps(dim);
    // Horizontal add
    xmm = _mm_hadd_ps(xmm, xmm);
    xmm = _mm_hadd_ps(xmm, xmm);
    float sum = _mm_cvtss_f32(xmm);
    return !sum;
}

}