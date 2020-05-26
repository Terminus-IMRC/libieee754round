
#include <cmath>

#include <immintrin.h>


#define DO_ARITH(rnd, expr) \
        do { \
            const unsigned old = _MM_GET_ROUNDING_MODE(); \
            _MM_SET_ROUNDING_MODE(rnd); \
            expr; \
            _MM_SET_ROUNDING_MODE(old); \
        } while (0)


#define DECLARE_1ARG(name, dtype, atype, func) \
        dtype name##_rn(const atype x) \
        { \
            dtype y; \
            DO_ARITH(_MM_ROUND_NEAREST, y = func(x)); \
            return y; \
        } \
        dtype name##_rd(const atype x) \
        { \
            dtype y; \
            DO_ARITH(_MM_ROUND_DOWN, y = func(x)); \
            return y; \
        } \
        dtype name##_ru(const atype x) \
        { \
            dtype y; \
            DO_ARITH(_MM_ROUND_UP, y = func(x)); \
            return y; \
        } \
        dtype name##_rz(const atype x) \
        { \
            dtype y; \
            DO_ARITH(_MM_ROUND_TOWARD_ZERO, y = func(x)); \
            return y; \
        }


#define DECLARE_2ARG(name, dtype, atype1, atype2, func) \
        dtype name##_rn(const atype1 x, const atype2 y) \
        { \
            dtype z; \
            DO_ARITH(_MM_ROUND_NEAREST, z = func(x, y)); \
            return z; \
        } \
        dtype name##_rd(const atype1 x, const atype2 y) \
        { \
            dtype z; \
            DO_ARITH(_MM_ROUND_DOWN, z = func(x, y)); \
            return z; \
        } \
        dtype name##_ru(const atype1 x, const atype2 y) \
        { \
            dtype z; \
            DO_ARITH(_MM_ROUND_UP, z = func(x, y)); \
            return z; \
        } \
        dtype name##_rz(const atype1 x, const atype2 y) \
        { \
            dtype z; \
            DO_ARITH(_MM_ROUND_TOWARD_ZERO, z = func(x, y)); \
            return z; \
        } \


template <typename T, typename U, typename V>
static inline
T add_tmpl(const U x, const V y)
{
    return x + y;
}


template <typename T, typename U, typename V>
static inline
T sub_tmpl(const U x, const V y)
{
    return x - y;
}


template <typename T, typename U, typename V>
static inline
T mul_tmpl(const U x, const V y)
{
    return x * y;
}


template <typename T, typename U, typename V>
static inline
T div_tmpl(const U x, const V y)
{
    return x / y;
}


template <typename T, typename U>
static inline
T rcp_tmpl(const U x)
{
    return 1 / x;
}


extern "C" {

    DECLARE_1ARG(nearbyint, double, double, nearbyint);
    DECLARE_1ARG(nearbyintf, float, float, nearbyintf);

    DECLARE_1ARG(rint, double, double, rint);
    DECLARE_1ARG(rintf, float, float, rintf);

    DECLARE_1ARG(lrint, long, double, lrint);
    DECLARE_1ARG(lrintf, long, float, lrintf);
    DECLARE_1ARG(llrint, long long, double, llrint);
    DECLARE_1ARG(llrintf, long long, float, llrintf);

    DECLARE_2ARG(add, double, double, double, (add_tmpl <double, double, double>));
    DECLARE_2ARG(addf, float, float, float, (add_tmpl <float, float, float>));

    DECLARE_2ARG(sub, double, double, double, (sub_tmpl <double, double, double>));
    DECLARE_2ARG(subf, float, float, float, (sub_tmpl <float, float, float>));

    DECLARE_2ARG(mul, double, double, double, (mul_tmpl <double, double, double>));
    DECLARE_2ARG(mulf, float, float, float, (mul_tmpl <float, float, float>));

    DECLARE_2ARG(div, double, double, double, (div_tmpl <double, double, double>));
    DECLARE_2ARG(divf, float, float, float, (div_tmpl <float, float, float>));

    DECLARE_1ARG(rcp, double, double, (rcp_tmpl <double, double>));
    DECLARE_1ARG(rcpf, float, float, (rcp_tmpl <float, float>));

}
