/**
 * @cond ___LICENSE___
 *
 * Copyright (c) 2016 Koen Visscher, Paul Visscher and individual contributors.
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

#include "math/scalar/quaternion.h"
#include "math/scalar/mathf.h"
#include "math/scalar/vec4.h"

#include <assert.h>

Quaternion::Quaternion()
{
}

Quaternion::Quaternion( const Real yaw, const Real pitch, const Real roll )
{
    SetEuler( yaw, pitch, roll );
}

Quaternion::Quaternion( const Real x, const Real y, const Real z, const Real w )
{
    SetValue( x, y, z, w );
}

Quaternion::Quaternion( const Vec3 &axis, const Real angle )
{
    SetRotation( axis, angle );
}

Quaternion::Quaternion( const Quaternion &other )
{
    mValues[0] = other.mValues[0];
    mValues[1] = other.mValues[1];
    mValues[2] = other.mValues[2];
    mValues[3] = other.mValues[3];
}

Quaternion::Quaternion( const Matrix3 &m )
{
    *this = m.GetRotation();
}

Quaternion::Quaternion( const Vec4 &axis )
{
    SetValue( axis[0], axis[1], axis[2], axis[3] );
}

Quaternion &Quaternion::operator=( const Quaternion &q )
{
    mValues[0] = q[0];
    mValues[1] = q[1];
    mValues[2] = q[2];
    mValues[3] = q[3];

    return *this;
}

Quaternion &Quaternion::operator+=( const Quaternion &q )
{
    mValues[0] += q[0];
    mValues[1] += q[1];
    mValues[2] += q[2];
    mValues[3] += q[3];

    return *this;
}

Quaternion &Quaternion::operator-=( const Quaternion &q )
{
    mValues[0] -= q[0];
    mValues[1] -= q[1];
    mValues[2] -= q[2];
    mValues[3] -= q[3];

    return *this;
}

Quaternion &Quaternion::operator*=( const Quaternion &q )
{
    SetValue( mValues[3] * q[0] + mValues[0] * q[3] + mValues[1] * q[2] - mValues[2] * q[1],
              mValues[3] * q[1] + mValues[1] * q[3] + mValues[2] * q[0] - mValues[0] * q[2],
              mValues[3] * q[2] + mValues[2] * q[3] + mValues[0] * q[1] - mValues[1] * q[0],
              mValues[3] * q[3] - mValues[0] * q[0] - mValues[1] * q[1] - mValues[2] * q[2] );

    return *this;
}

Quaternion &Quaternion::operator*=( const Real s )
{
    mValues[0] *= s;
    mValues[1] *= s;
    mValues[2] *= s;
    mValues[3] *= s;

    return *this;
}

Quaternion &Quaternion::operator/=( const Real s )
{
    assert( s != 0.0f );
    return *this *= 1.0f / s;
}

Quaternion Quaternion::operator+( const Quaternion &q ) const
{
    return Quaternion( mValues[0] + q[0], mValues[1] + q[1], mValues[2] + q[2], mValues[3] + q[3] );
}

Quaternion Quaternion::operator-( const Quaternion &q ) const
{
    return Quaternion( mValues[0] - q[0], mValues[1] - q[1], mValues[2] - q[2], mValues[3] - q[3] );
}

Quaternion Quaternion::operator*( const Real s ) const
{
    return Quaternion( mValues[0] * s, mValues[1] * s, mValues[2] * s, mValues[3] * s );
}

Quaternion Quaternion::operator/( const Real s ) const
{
    assert( s != 0.0f );
    return *this * ( 1.0f / s );
}

Quaternion Quaternion::operator-() const
{
    return Quaternion( -mValues[0], -mValues[1],  -mValues[2],  -mValues[3] );
}

Real Quaternion::operator[]( const U8 axis ) const
{
    return mValues[ axis ];
}

Real Quaternion::operator[]( const U8 axis )
{
    return mValues[ axis ];
}

void Quaternion::SetEuler( const Real yaw, const Real pitch, const Real roll )
{
    const Real p = yaw * 0.5f;
    const Real y = pitch * 0.5f;
    const Real r = roll * 0.5f;

    const Real siny = Mathf::Sin( y );
    const Real sinp = Mathf::Sin( p );
    const Real sinr = Mathf::Sin( r );
    const Real cosy = Mathf::Cos( y );
    const Real cosp = Mathf::Cos( p );
    const Real cosr = Mathf::Cos( r );

    SetValue( cosr * sinp * cosy + sinr * cosp * siny,
              cosr * cosp * siny - sinr * sinp * cosy,
              sinr * cosp * cosy - cosr * sinp * siny,
              cosr * cosp * cosy + sinr * sinp * siny );
}

void Quaternion::SetRotation( const Vec3 &axis, const Real angle )
{
    assert( axis.Length() != 0.0f );

    Real s = Mathf::Sin( angle * 0.5f ) / axis.Length();
    SetValue( axis[0] * s, axis[1] * s, axis[2] * s, Mathf::Cos( angle * 0.5f ) );
}

void Quaternion::SetValue( Real x, Real y, Real z, Real w )
{
    mValues[0] = x;
    mValues[1] = y;
    mValues[2] = z;
    mValues[3] = w;
}

Quaternion Quaternion::GetInverse() const
{
    return Quaternion( -mValues[0], -mValues[1], -mValues[2], mValues[3] );
}

Quaternion Quaternion::SafeNormalise()
{
    const Vec4 absv = Vec4( mValues[0], mValues[1], mValues[2], mValues[3] ).Absolute();
    const U8 max = absv.MaxAxis();

    if ( absv[max] > 0 )
    {
        *this /= absv[max];

        return *this /= Length();
    }
    else
    {
        SetValue( 1.0f, 0.0f, 0.0f, 0.0f );
    }

    return *this;
}

Quaternion Quaternion::Normalise()
{
    assert( Length() != 0.0f );

    return *this /= Length();
}

Vec3 Quaternion::RotateVector( const Vec3 &vec ) const
{
    //     Quaternion q = vec * ( *this );
    //
    //     q *= ( *this ).GetInverse();
    //
    //     return Vec3( q[0], q[1], q[2] );

    // Faster path ! https://molecularmusings.wordpress.com/2013/05/24/a-faster-quaternion-vector-multiplication/

    Vec3 qXYZ = this->xyz();
    Vec3 t = 2 * qXYZ.Cross( vec );

    return ( vec + mValues[3] * t + qXYZ.Cross( t ) );
}

Quaternion Quaternion::GetViewRotation() const
{
    return GetInverse();
}

Real Quaternion::GetAngleFromQuaternion( const Quaternion &q ) const
{
    const Real s = Mathf::Sqrt( Length2() * q.Length2() );

    assert( s != 0.0f );

    return Mathf::Acos( Mathf::Clamp( Dot( q ) / s, -1.0f, 1.0f ) );
}

Real Quaternion::GetAngle() const
{
    return 2.0f * Mathf::Acos( Mathf::Clamp( mValues[3], -1.0f, 1.0f ) );
}

Vec3 Quaternion::GetAxis() const
{
    const Real s2 = 1.0f - mValues[3] * mValues[3];

    if ( s2 < Mathf::GetEpsilon() )
    {
        return Vec3( 1.0f, 0.0f, 0.0f );
    }

    const Real s = 1.0f / Mathf::Sqrt( s2 );
    return Vec3( mValues[0] * s, mValues[1] * s, mValues[2] * s );
}

Real Quaternion::Dot( const Quaternion &q ) const
{
    return mValues[0] * q.mValues[0] + mValues[1] * q.mValues[1] + mValues[2] * q.mValues[2] + mValues[3] * q.mValues[3];
}

Real Quaternion::Length2() const
{
    return Dot( *this );
}

Real Quaternion::Length() const
{
    return Mathf::Sqrt( Length2() );
}

Quaternion Quaternion::Slerp( const Quaternion &q, const Real t ) const
{
    const Real dotp = Dot( q );

    if ( dotp > ( 1.0f - Mathf::GetEpsilon() ) )
    {
        return Lerp( q, t );
    }

    const Real theta = Mathf::Acos( Mathf::Clamp( dotp, -1.0f, 1.0f ) ) * t;
    Quaternion q2 = q - *this * dotp;
    q2.Normalise();

    return *this * Mathf::Cos( theta ) + q2 * Mathf::Sin( theta );
}

Quaternion Quaternion::Nlerp( const Quaternion &q, const Real t ) const
{
    const Vec4 tv( mValues[0], mValues[1], mValues[2], mValues[3] );
    const Vec4 qv( q.mValues[0], q.mValues[1], q.mValues[2], q.mValues[3] );
    return Quaternion( tv.Lerp( qv, t ).Normalise() );
}


Quaternion Quaternion::Lerp( const Quaternion &q, const Real t ) const
{
    const Vec4 tv( mValues[0], mValues[1], mValues[2], mValues[3] );
    const Vec4 qv( q.mValues[0], q.mValues[1], q.mValues[2], q.mValues[3] );
    return Quaternion( tv.Lerp( qv, t ) );
}

void Quaternion::Clear()
{
    SetValue( 0.0f, 0.0f, 0.0f, 1.0f );
}

Quaternion Quaternion::GetIdentity()
{
    return Quaternion( 0.0f, 0.0f, 0.0f, 1.0f );
}

Vec3 Quaternion::xyz() const
{
    return Vec3( mValues[0], mValues[1], mValues[2] );
}

Quaternion operator*( const Quaternion &q1, const Quaternion &q2 )
{
    return Quaternion( q1[3] * q2[0] + q1[0] * q2[3] + q1[1] * q2[2] - q1[2] * q2[1],
                       q1[3] * q2[1] + q1[1] * q2[3] + q1[2] * q2[0] - q1[0] * q2[2],
                       q1[3] * q2[2] + q1[2] * q2[3] + q1[0] * q2[1] - q1[1] * q2[0],
                       q1[3] * q2[3] - q1[0] * q2[0] - q1[1] * q2[1] - q1[2] * q2[2] );
}

Quaternion operator*( const Quaternion &q, const Vec3 &v )
{
    return Quaternion( +q[3] * v[0] + q[1] * v[2] - q[2] * v[1],
                       +q[3] * v[1] + q[2] * v[0] - q[0] * v[2],
                       +q[3] * v[2] + q[0] * v[1] - q[1] * v[0],
                       -q[0] * v[0] - q[1] * v[1] - q[2] * v[2] );
}

Quaternion operator*( const Vec3 &v, const Quaternion &q )
{
    return Quaternion( +v[0] * q[3] + v[1] * q[2] - v[2] * q[1],
                       +v[1] * q[3] + v[2] * q[0] - v[0] * q[2],
                       +v[2] * q[3] + v[0] * q[1] - v[1] * q[0],
                       -v[0] * q[0] - v[1] * q[1] - v[2] * q[2] );
}