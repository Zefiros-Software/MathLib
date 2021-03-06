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

#pragma once
#ifndef __ENGINE_MATRIX3_H__
#define __ENGINE_MATRIX3_H__

#include "math/vec3.h"
#include "math/quaternion.h"

#include <assert.h>
#include <cstddef>

template< class Number >
class Matrix3;

typedef Matrix3< F32 > Mat3f;
typedef Matrix3< F64 > Mat3d;
typedef Matrix3< S32 > Mat3i;
typedef Matrix3< U32 > Mat3u;
typedef Matrix3< Scalar > Mat3;

template< class Number >
class Matrix3
{
    template< class T >
    friend Matrix3< T > operator+(const Matrix3< T > &m1, const Matrix3< T > &m2);

    template< class T >
    friend Matrix3< T > operator-(const Matrix3< T > &m1, const Matrix3< T > &m2);

    template< class T >
    friend Matrix3< T > operator*(const Matrix3< T > &m1, const Matrix3< T > &m2);

    template< class T >
    friend Matrix3< T > operator*(const Matrix3< T > &m, const T s);

    template< class T >
    friend Vector3< T > operator*(const Matrix3< T > &m, const Vector3< T > &v);

public:

    inline Matrix3()
    {
    }

    inline Matrix3(const Quaternion< Number > &q)
    {
        SetRotation(q);
    }

    inline Matrix3(const Number a11, const Number a12, const Number a13,
                   const Number a21, const Number a22, const Number a23,
                   const Number a31, const Number a32, const Number a33)
    {
        SetValue(a11, a12, a13, a21, a22, a23, a31, a32, a33);
    }

    inline Matrix3(const Matrix3 &other)
    {
        mValues[0] = other.mValues[0];
        mValues[1] = other.mValues[1];
        mValues[2] = other.mValues[2];
    }

    inline Matrix3(const Vector3< Number > &v1, const Vector3< Number > &v2, const Vector3< Number > &v3)
    {
        mValues[0] = v1;
        mValues[1] = v2;
        mValues[2] = v3;
    }

    inline Matrix3 &operator=(const Matrix3 &m)
    {
        mValues[0] = m.mValues[0];
        mValues[1] = m.mValues[1];
        mValues[2] = m.mValues[2];

        return *this;
    }

    inline Matrix3 &operator*=(const Matrix3 &m)
    {
        SetValue(m.Dotx(mValues[0]), m.Doty(mValues[0]), m.Dotz(mValues[0]),
                 m.Dotx(mValues[1]), m.Doty(mValues[1]), m.Dotz(mValues[1]),
                 m.Dotx(mValues[2]), m.Doty(mValues[2]), m.Dotz(mValues[2]));

        return *this;
    }

    inline Matrix3 &operator+=(const Matrix3 &m)
    {
        SetValue(mValues[0][0] + m.mValues[0][0], mValues[0][1] + m.mValues[0][1], mValues[0][2] + m.mValues[0][2],
                 mValues[1][0] + m.mValues[1][0], mValues[1][1] + m.mValues[1][1], mValues[1][2] + m.mValues[1][2],
                 mValues[2][0] + m.mValues[2][0], mValues[2][1] + m.mValues[2][1], mValues[2][2] + m.mValues[2][2]);

        return *this;
    }

    inline Matrix3 &operator-=(const Matrix3 &m)
    {
        SetValue(mValues[0][0] - m.mValues[0][0], mValues[0][1] - m.mValues[0][1], mValues[0][2] - m.mValues[0][2],
                 mValues[1][0] - m.mValues[1][0], mValues[1][1] - m.mValues[1][1], mValues[1][2] - m.mValues[1][2],
                 mValues[2][0] - m.mValues[2][0], mValues[2][1] - m.mValues[2][1], mValues[2][2] - m.mValues[2][2]);

        return *this;
    }

    inline bool operator==(const Matrix3 &m) const
    {
        return mValues[0] == m.mValues[0] && mValues[1] == m.mValues[1] && mValues[2] == m.mValues[2];
    }

    bool operator!=(const Matrix3 &m) const
    {
        return !(*this == m);
    }

    inline Vector3< Number > &operator[](size_t axis)
    {
        return mValues[ axis ];
    }

    inline const Vector3< Number > operator[](size_t axis) const
    {
        return mValues[ axis ];
    }

    inline Number *Data()
    {
        return &mValues[0][0];
    }

    inline const Number *Data() const
    {
        return &mValues[0][0];
    }

    inline void SetColumn(const U8 column, const Vector3< Number > &v)
    {
        mValues[0][column] = v[0];
        mValues[1][column] = v[1];
        mValues[2][column] = v[2];
    }

    inline Vector3< Number > GetColumn(const U8 column) const
    {
        return Vector3< Number >(mValues[0][column], mValues[1][column], mValues[2][column]);
    }

    inline void SetRow(const U8 row, const Vector3< Number > &v)
    {
        mValues[row] = v;
    }

    inline Vector3< Number > GetRow(const U8 row) const
    {
        return mValues[row];
    }

    inline void SetRotation(const Quaternion< Number > &q)
    {
        const Number norm2 = q.Length2();

        assert(norm2 != 0.0f);

        const Number s     = 2.0f / norm2;

        const Number xs  = q[0] * s;
        const Number ys  = q[1] * s;
        const Number zs  = q[2] * s;
        const Number wxs = q[3] * xs;
        const Number wys = q[3] * ys;
        const Number wzs = q[3] * zs;
        const Number xxs = q[0] * xs;
        const Number xys = q[0] * ys;
        const Number xzs = q[0] * zs;
        const Number yys = q[1] * ys;
        const Number yzs = q[1] * zs;
        const Number zzs = q[2] * zs;

        SetValue(1.0f - (yys + zzs), xys - wzs, xzs + wys,
                 xys + wzs, 1.0f - (xxs + zzs), yzs - wxs,
                 xzs - wys, yzs + wxs, 1.0f - (xxs + yys));
    }

    inline Quaternion< Number > GetRotation() const
    {
        Number t[4];
        const Number trace = mValues[0][0] + mValues[1][1] + mValues[2][2];


        if (trace > 0.0f)
        {
            const Number s  = Mathf::Sqrt(trace + 1.0f);
            const Number s2 = 0.5f / s;

            t[0] = (mValues[2][1] - mValues[1][2]) * s2;
            t[1] = (mValues[0][2] - mValues[2][0]) * s2;
            t[2] = (mValues[1][0] - mValues[0][1]) * s2;
            t[3] = 0.5f * s;
        }
        else
        {
            const U8 i = mValues[0][0] < mValues[1][1] ?
                         (mValues[1][1] < mValues[2][2] ? 2 : 1) :
                         (mValues[0][0] < mValues[2][2] ? 2 : 0);

            const U8 j = (i + 1) % 3;
            const U8 k = (i + 2) % 3;

            const Number s = Mathf::Sqrt(mValues[i][i] - mValues[j][j] - mValues[k][k] + 1.0f);

            assert(s != 0.0f);

            const Number s2 = 0.5f / s;

            t[i] = 0.5f * s;
            t[j] = (mValues[j][i] - mValues[i][j]) * s2;
            t[k] = (mValues[k][i] - mValues[i][k]) * s2;
            t[3] = (mValues[k][j] - mValues[j][k]) * s2;
        }

        return Quaternion< Number >(t[0], t[1], t[2], t[3]);
    }

    inline void SetEuler(const Number yaw, const Number pitch, const Number roll)
    {
        Number cy(Mathf::Cos(yaw));
        Number cp(Mathf::Cos(pitch));
        Number cr(Mathf::Cos(roll));

        Number sy(Mathf::Sin(yaw));
        Number sp(Mathf::Sin(pitch));
        Number sr(Mathf::Sin(roll));


        Number cc = cr * cy;
        Number cs = cr * sy;
        Number sc = sr * cy;
        Number ss = sr * sy;

        SetValue(cp * cy, sp * sc - cs, sp * cc + ss,
                 cp * sy, sp * ss + cc, sp * cs - sc,
                 -sp, cp * sr, cp * cr);
    }

    inline Vector3< Number > GetEuler() const
    {
        return GetRotation().GetAxis();
    }

    inline Matrix3 Scale(const Vector3< Number > &v) const
    {
        return Matrix3(mValues[0][0] * v[0], mValues[0][1] * v[1], mValues[0][2] * v[2],
                       mValues[1][0] * v[0], mValues[1][1] * v[1], mValues[1][2] * v[2],
                       mValues[2][0] * v[0], mValues[2][1] * v[1], mValues[2][2] * v[2]);
    }

    inline Matrix3 GetTranspose() const
    {
        return Matrix3(mValues[0][0], mValues[1][0], mValues[2][0],
                       mValues[0][1], mValues[1][1], mValues[2][1],
                       mValues[0][2], mValues[1][2], mValues[2][2]);
    }

    inline Matrix3 GetAbsolute() const
    {
        return Matrix3(Mathf::Abs(mValues[0][0]), Mathf::Abs(mValues[0][1]), Mathf::Abs(mValues[0][2]),
                       Mathf::Abs(mValues[1][0]), Mathf::Abs(mValues[1][1]), Mathf::Abs(mValues[1][2]),
                       Mathf::Abs(mValues[2][0]), Mathf::Abs(mValues[2][1]), Mathf::Abs(mValues[2][2]));
    }

    inline Matrix3 GetAdjoint() const
    {
        return Matrix3(GetCofactor(0, 0), GetCofactor(0, 1), GetCofactor(0, 2),
                       GetCofactor(1, 0), GetCofactor(1, 1), GetCofactor(1, 2),
                       GetCofactor(2, 0), GetCofactor(2, 1), GetCofactor(2, 2));
    }

    inline Matrix3 GetInverse() const
    {
        const Number det = GetDeterminant();

        assert(det != 0.0f);

        const Number s = 1.0f / det;
        return GetAdjoint().GetTranspose() * s;
    }

    inline void SetIdentity()
    {
        SetValue(1.0f, 0.0f, 0.0f,
                 0.0f, 1.0f, 0.0f,
                 0.0f, 0.0f, 1.0f);
    }

    inline Number GetCofactor(const U8 row, const U8 column) const
    {
        Number cof = mValues[(row + 1) % 3][(column + 1) % 3] * mValues[(row + 2) % 3][(column + 2) % 3] -
                     mValues[(row + 1) % 3][(column + 2) % 3] * mValues[(row + 2) % 3][(column + 1) % 3];

        if (((column + row) & 1) == 1)
        {
            cof *= -1;
        }

        return cof;
    }

    inline Number GetDeterminant() const
    {
        return  mValues[0][0] * GetCofactor(0, 0) +
                mValues[1][0] * GetCofactor(1, 0) +
                mValues[2][0] * GetCofactor(2, 0);
    }

    inline void SetValue(const Number a11, const Number a12, const Number a13,
                         const Number a21, const Number a22, const Number a23,
                         const Number a31, const Number a32, const Number a33)
    {
        mValues[0].SetValue(a11, a12, a13);
        mValues[1].SetValue(a21, a22, a23);
        mValues[2].SetValue(a31, a32, a33);
    }

    static inline Matrix3 GetZero()
    {
        return Matrix3(Vector3< Number >::GetZero(), Vector3< Number >::GetZero(), Vector3< Number >::GetZero());
    }

    static inline Matrix3 GetIdentity()
    {
        Matrix3 mat;
        mat.SetIdentity();
        return mat;
    }

private:

    Vector3< Number > mValues[3];

    inline Number Dotx(const Vector3< Number > &v) const
    {
        return mValues[0][0] * v[0] + mValues[1][0] * v[1] + mValues[2][0] * v[2];
    }

    inline Number Doty(const Vector3< Number > &v) const
    {
        return mValues[0][1] * v[0] + mValues[1][1] * v[1] + mValues[2][1] * v[2];
    }

    inline Number Dotz(const Vector3< Number > &v) const
    {
        return mValues[0][2] * v[0] + mValues[1][2] * v[1] + mValues[2][2] * v[2];
    }
};

template< class Number >
Matrix3< Number > operator+(const Matrix3< Number > &m1, const Matrix3< Number > &m2)
{
    return Matrix3< Number >(
               m1.mValues[0][0] + m2.mValues[0][0],
               m1.mValues[0][1] + m2.mValues[0][1],
               m1.mValues[0][2] + m2.mValues[0][2],
               m1.mValues[1][0] + m2.mValues[1][0],
               m1.mValues[1][1] + m2.mValues[1][1],
               m1.mValues[1][2] + m2.mValues[1][2],
               m1.mValues[2][0] + m2.mValues[2][0],
               m1.mValues[2][1] + m2.mValues[2][1],
               m1.mValues[2][2] + m2.mValues[2][2]);
}

template< class Number >
Matrix3< Number > operator-(const Matrix3< Number > &m1, const Matrix3< Number > &m2)
{
    return Matrix3< Number >(
               m1.mValues[0][0] - m2.mValues[0][0],
               m1.mValues[0][1] - m2.mValues[0][1],
               m1.mValues[0][2] - m2.mValues[0][2],
               m1.mValues[1][0] - m2.mValues[1][0],
               m1.mValues[1][1] - m2.mValues[1][1],
               m1.mValues[1][2] - m2.mValues[1][2],
               m1.mValues[2][0] - m2.mValues[2][0],
               m1.mValues[2][1] - m2.mValues[2][1],
               m1.mValues[2][2] - m2.mValues[2][2]);
}

template< class Number >
Matrix3< Number > operator*(const Matrix3< Number > &m1, const Matrix3< Number > &m2)
{
    return Matrix3< Number >(m2.Dotx(m1.mValues[0]), m2.Doty(m1.mValues[0]), m2.Dotz(m1.mValues[0]),
                             m2.Dotx(m1.mValues[1]), m2.Doty(m1.mValues[1]), m2.Dotz(m1.mValues[1]),
                             m2.Dotx(m1.mValues[2]), m2.Doty(m1.mValues[2]), m2.Dotz(m1.mValues[2]));
}

template< class Number >
Matrix3< Number > operator*(const Matrix3< Number > &m, const Number s)
{
    return Matrix3< Number >(m.mValues[0][0] * s, m.mValues[0][1] * s, m.mValues[0][2] * s,
                             m.mValues[1][0] * s, m.mValues[1][1] * s, m.mValues[1][2] * s,
                             m.mValues[2][0] * s, m.mValues[2][1] * s, m.mValues[2][2] * s);
}

template< class Number >
Vector3< Number > operator*(const Matrix3< Number > &m, const Vector3< Number > &v)
{
    return Vector3< Number >(m.mValues[0].Dot(v), m.mValues[1].Dot(v), m.mValues[2].Dot(v));
}

#endif
