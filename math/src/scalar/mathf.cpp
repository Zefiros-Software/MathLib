/**
 * @cond ___LICENSE___
 *
 * Copyright (c) 2016-2018 Zefiros Software.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @endcond
 */
#include "math/mathf.h"

#include <assert.h>
#include <cstdlib>

#include <cmath>

BEGIN_MATH_NAMESPACE

F32 Mathf::Acos(F32 f)
{
    assert(f >= -1.0f && f <= 1.0f);
    return acosf(f);
}

F32 Mathf::Asin(F32 f)
{
    assert(f >= -1.0f && f <= 1.0f);
    return asinf(f);
}

F32 Mathf::Atan(F32 f)
{
    return atanf(f);
}

F32 Mathf::Atan2(F32 x, F32 y)
{
    return atan2f(x, y);
}

F32 Mathf::Cos(F32 f)
{
    return cosf(f);
}

F32 Mathf::Sin(F32 f)
{
    return sinf(f);
}

F32 Mathf::Tan(F32 f)
{
    return tanf(f);
}

F64 Mathf::Acos(F64 f)
{
    assert(f >= -1.0f && f <= 1.0f);
    return acos(f);
}

F64 Mathf::Asin(F64 f)
{
    assert(f >= -1.0f && f <= 1.0f);
    return asin(f);
}

F64 Mathf::Atan(F64 f)
{
    return atan(f);
}

F64 Mathf::Atan2(F64 x, F64 y)
{
    return atan2(x, y);
}

F64 Mathf::Cos(F64 f)
{
    return cos(f);
}

F64 Mathf::Sin(F64 f)
{
    return sin(f);
}

F64 Mathf::Tan(F64 f)
{
    return tan(f);
}

F32 Mathf::Ceil(F32 f)
{
    return ceilf(f);
}

F32 Mathf::Floor(F32 f)
{
    return floorf(f);
}


F64 Mathf::Round(F64 f)
{
    return std::round(f);
}

F32 Mathf::Round(F32 f)
{
    return std::round(f);
}

F64 Mathf::Ceil(F64 f)
{
    return ceil(f);
}

F64 Mathf::Floor(F64 f)
{
    return floor(f);
}


F32 Mathf::Trunc(F32 f)
{
    return std::trunc(f);
}


F64 Mathf::Trunc(F64 f)
{
    return std::trunc(f);
}


F64 Mathf::Pow(F64 f, F64 exp)
{
    return std::pow(f, exp);
}

F32 Mathf::Pow(F32 f, F32 exp)
{
    return std::pow(f, exp);
}

F64 Mathf::Rint(F64 x)
{
    return std::rint(x);
}

F32 Mathf::Rint(F32 x)
{
    return std::rint(x);
}



F32 Mathf::Sqrt(F32 f)
{
    assert(f >= 0.0f);

    return std::sqrt(f);
}

F64 Mathf::Sqrt(F64 f)
{
    assert(f >= 0.0f);

    return std::sqrt(f);
}


F32 Mathf::Log(F32 f)
{
    assert(f > 0.0f);
    return logf(f);
}

F32 Mathf::Log2(F32 f)
{
    assert(f > 0.0f);
    return logf(f) / logf(2);
}

F64 Mathf::Log(F64 f)
{
    assert(f > 0.0f);
    return log(f);
}

F64 Mathf::Log2(F64 f)
{
    assert(f > 0.0f);
    return log(f) / log(2);
}

U32 Mathf::Log2(U64 n)
{
    static U32 tab64[64] =
    {
        0, 58, 1, 59, 47, 53, 2, 60, 39, 48, 27, 54, 33, 42, 3, 61,
        51, 37, 40, 49, 18, 28, 20, 55, 30, 34, 11, 43, 14, 22, 4, 62,
        57, 46, 52, 38, 26, 32, 41, 50, 36, 17, 19, 29, 10, 13, 21, 56,
        45, 25, 31, 35, 16, 9, 12, 44, 24, 15, 8, 23, 7, 6, 5, 63
    };

    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n |= n >> 32;
    return tab64[(n * 0x03f6eaf2cd271461) >> 58];
}

U32 Mathf::Log2(U32 f)
{
    U32 s, t;

    t = (f > 0xffff) << 4;
    f >>= t;
    s = (f > 0xff) << 3;
    f >>= s, t |= s;
    s = (f > 0xf) << 2;
    f >>= s, t |= s;
    s = (f > 0x3) << 1;
    f >>= s, t |= s;

    return (t | (f >> 1));
}

F32 Mathf::Log10(F32 f)
{
    assert(f > 0.0f);
    return log10f(f);
}

F64 Mathf::Log10(F64 f)
{
    assert(f > 0.0f);
    return log10(f);
}

bool Mathf::IsPow2(U32 n)
{
    return (!(n & (n - 1)) && n);
}

U32 Mathf::NextPow2(U32 x)
{
    U32 y = x - 1;
    y |= y >> 1;
    y |= y >> 2;
    y |= y >> 4;
    y |= y >> 8;
    y |= y >> 16;
    return ++y;
}

F32 Mathf::Abs(F32 f)
{
    return fabsf(f);
}

S32 Mathf::Abs(S32 f)
{
    return abs(f);
}

F64 Mathf::Abs(F64 f)
{
    return fabs(f);
}

S64 Mathf::Abs(S64 f)
{
    return abs(f);
}