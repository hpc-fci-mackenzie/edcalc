/*
 * File:   edcalc.c
 * Author: lfuso
 * From: https://github.com/LeoFuso/edcalc
 *
 * Created on 2017-11-30
 */

#include "edcalc.h"

double e_intrinsic(const double *x,const double *y, size_t n);

double euclidean_baseline(const double *x,const double *y, size_t n)
{
    double result = 0;
    for(int i = 0; i < n; ++i){
        const double num = x[i] - y[i];
        result += num * num;
    }
    return result;
}

double e_intrinsic(const double *x,const double *y, size_t n)
{
    double result = 0;
    __m128 euclidean = _mm_setzero_ps();

    for (; n>3; n-=4) {
        const __m128 a = _mm_loadu_ps(x);
        const __m128 b = _mm_loadu_ps(y);
        const __m128 sub = _mm_sub_ps(a,b);
        const __m128 sqrt = _mm_mul_ps(sub, sub);
        euclidean = _mm_add_ps(euclidean, sqrt);
        x+=4;
        y+=4;
    }
    const __m128 shuffle1 = _mm_shuffle_ps(euclidean, euclidean, _MM_SHUFFLE(1,0,3,2));
    const __m128 sum1 = _mm_add_ps(euclidean, shuffle1);
    const __m128 shuffle2 = _mm_shuffle_ps(sum1, sum1, _MM_SHUFFLE(2,3,0,1));
    const __m128 sum2 = _mm_add_ps(sum1, shuffle2);
    _mm_store_ss(&result,sum2);
    //    _mm_empty();
    if (n)
        result += euclidean_baseline(x, y, n);	// remaining 1-3 entries

    return result;
}

double euclidean_sse(const double *x, const double *y, size_t dim)
{
    double (*euclidean_sse)(const double*, const double*,size_t) = euclidean_baseline;
//#ifdef __SSE__
    euclidean_sse = e_intrinsic;
//#endif
    return euclidean_sse(x, y, dim);
}
