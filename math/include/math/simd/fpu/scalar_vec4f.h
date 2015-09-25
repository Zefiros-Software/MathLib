#pragma once
#ifndef __SCALAR_VEC4f_H__
#define __SCALAR_VEC4f_H__

#include "math/types.h"

#include "math/scalar/mathf.h"

#include "math/simd/simdBaseTraits.h"
#include "math/simd/simdVectorBase.h"

#include "math/simd/fpu/scalar_vec4b.h"

class ScalarVec4f;

template <>
struct FpuSimdTraits<F32> : public BaseSimdTraits<F32>
{
    typedef ScalarVec4f vec_type;
    typedef ScalarVec4b bool_type;
    static const size_t width = 4;
    static const size_t bytesPerValue = 4;
    static const size_t registers = 1;
    static const size_t alignment = 16;
};

class ScalarVec4f : public SimdVectorBase< ScalarVec4f, F32>
{
public:

    union EasyConvert
    {
        F32 f;
        S32 i;
        U32 u;
    };

    ScalarVec4f()
    {}

    inline ScalarVec4f( F32 val )
    {
        for ( U32 i = 0; i < 4; ++i )
        {
            mValue[i] = val;
        }
    }

    /*
    inline ScalarVec4f( F32 x, F32 y, F32 z, F32 w )
    {
        mValue[0] = x;
        mValue[1] = y;
        mValue[2] = z;
        mValue[3] = w;
    }
    */

    inline ScalarVec4f( const F32 *rhs )
    {
        std::copy( rhs, rhs + FpuSimdTraits<F32>::width, mValue );
    }

    inline ScalarVec4f &operator=( const F32 *rhs )
    {
        std::copy( rhs, rhs + FpuSimdTraits<F32>::width, mValue );

        return *this;
    }

    inline operator F32 *()
    {
        return mValue;
    }

    inline operator const F32 *() const
    {
        return mValue;
    }

    void LoadUnaligned( const F32 *src )
    {
        std::copy( src, src + FpuSimdTraits<F32>::width, mValue );
    }

    void LoadAligned( const F32 *src )
    {
        LoadUnaligned( src );
    }

    void StoreUnaligned( F32 *dest ) const
    {
        std::copy( mValue, mValue + FpuSimdTraits<F32>::width, dest );
    }

    void StoreAligned( F32 *dest ) const
    {
        StoreUnaligned( dest );
    }

    void RotateOne( U32 rotation )
    {
        F32 temp = mValue[0];

        mValue[0] = mValue[1];
        mValue[1] = mValue[2];
        mValue[2] = mValue[3];
        mValue[3] = temp;
    }
    
    static inline U32 RotateIndex( U32 rotation, U32 index )
    {
        const U32 registerOffset = 4;
        
        const U32 rotatedIndex = ( ( index + rotation ) & ( registerOffset - 1 ) );
    
        return rotatedIndex;
    }
    
    inline ScalarVec4f RoundToNearest() const
    {
        
        ScalarVec4f newVec;

        for ( U32 i = 0; i < 4; ++i )
        {
            newVec()[i] = (F32) Mathf::Rint( mValue[i] );
        }
    
        return newVec;
    }
    
    inline static ScalarVec4f GetZero()
    {
        ScalarVec4f newVec;

        for ( U32 i = 0; i < 4; ++i )
        {
            newVec()[i] = 0.0;
        }
    
        return newVec;
    }
    
    inline static ScalarVec4f GetFullMask()
    {
        EasyConvert easyc;
        easyc.u = 0xFFFFFFFF;
        
        ScalarVec4f newVec;

        for ( U32 i = 0; i < 4; ++i )
        {
            newVec()[i] = easyc.f;
        }
    
        return newVec;
    }

private:

    F32 mValue[4];
};

//
// Math
//

inline ScalarVec4f operator+( const ScalarVec4f &lhs, const ScalarVec4f &rhs )
{
    ScalarVec4f newVec;

    for ( U32 i = 0; i < 4; ++i )
    {
        newVec()[i] = lhs()[i] + rhs()[i];
    }

    return newVec;
}

inline ScalarVec4f operator-( const ScalarVec4f &lhs, const ScalarVec4f &rhs )
{
    ScalarVec4f newVec;

    for ( U32 i = 0; i < 4; ++i )
    {
        newVec()[i] = lhs()[i] - rhs()[i];
    }

    return newVec;
}

inline ScalarVec4f operator*( const ScalarVec4f &lhs, const ScalarVec4f &rhs )
{
    ScalarVec4f newVec;

    for ( U32 i = 0; i < 4; ++i )
    {
        newVec()[i] = lhs()[i] * rhs()[i];
    }

    return newVec;
}

inline ScalarVec4f operator/( const ScalarVec4f &lhs, const ScalarVec4f &rhs )
{
    ScalarVec4f newVec;

    for ( U32 i = 0; i < 4; ++i )
    {
        newVec()[i] = lhs()[i] / rhs()[i];
    }

    return newVec;
}

//
// Comparison
//

inline ScalarVec4b operator== ( const ScalarVec4f &lhs, const ScalarVec4f &rhs )
{
    ScalarVec4b newVec;

    for ( U32 i = 0; i < 4; ++i )
    {
        newVec()[i] = lhs()[i] == rhs()[i];
    }

    return newVec;
}

inline ScalarVec4b operator!= ( const ScalarVec4f &lhs, const ScalarVec4f &rhs )
{
    ScalarVec4b newVec;

    for ( U32 i = 0; i < 4; ++i )
    {
        newVec()[i] = lhs()[i] != rhs()[i];
    }

    return newVec;
}

inline ScalarVec4b operator< ( const ScalarVec4f &lhs, const ScalarVec4f &rhs )
{
    ScalarVec4b newVec;

    for ( U32 i = 0; i < 4; ++i )
    {
        newVec()[i] = lhs()[i] < rhs()[i];
    }

    return newVec;
}

inline ScalarVec4b operator<= ( const ScalarVec4f &lhs, const ScalarVec4f &rhs )
{
    ScalarVec4b newVec;

    for ( U32 i = 0; i < 4; ++i )
    {
        newVec()[i] = lhs()[i] <= rhs()[i];
    }

    return newVec;
}

inline ScalarVec4b operator> ( const ScalarVec4f &lhs, const ScalarVec4f &rhs )
{
    ScalarVec4b newVec;

    for ( U32 i = 0; i < 4; ++i )
    {
        newVec()[i] = lhs()[i] > rhs()[i];
    }

    return newVec;
}

inline ScalarVec4b operator>= ( const ScalarVec4f &lhs, const ScalarVec4f &rhs )
{
    ScalarVec4b newVec;

    for ( U32 i = 0; i < 4; ++i )
    {
        newVec()[i] = lhs()[i] >= rhs()[i];
    }

    return newVec;
}

inline ScalarVec4f operator&( const ScalarVec4f &lhs, const ScalarVec4f &rhs ) 
{
    ScalarVec4f newVec;

    union EasyConvert
    {
        F32 f;
        S32 i;
        U32 u;
    } conv1, conv2, conv3;
    
    for ( U32 i = 0; i < 4; ++i )
    {
        conv1.f = lhs()[i];
        conv2.f = rhs()[i];
        conv3.u = conv1.u & conv2.u;
        
        newVec()[i] = conv3.f;
    }

    return newVec;
}

inline ScalarVec4f operator&( const ScalarVec4f &lhs, const ScalarVec4b &rhs ) 
{
    ScalarVec4f newVec;

    union EasyConvert
    {
        F32 f;
        S32 i;
        U32 u;
    } conv1, conv2, conv3;

    for ( U32 i = 0; i < 4; ++i )
    {
        conv1.f = lhs()[i];
        conv2.f = rhs()[i];
        conv3.u = conv1.u & conv2.u;
        
        newVec()[i] = conv3.f;
    }

    return newVec;
}

inline ScalarVec4f operator&( const ScalarVec4b &lhs, const ScalarVec4f &rhs ) 
{
    ScalarVec4f newVec;

    union EasyConvert
    {
        F32 f;
        S32 i;
        U32 u;
    } conv1, conv2, conv3;

    for ( U32 i = 0; i < 4; ++i )
    {
        conv1.f = lhs()[i];
        conv2.f = rhs()[i];
        conv3.u = conv1.u & conv2.u;
        
        newVec()[i] = conv3.f;
    }

    return newVec;
}

//
// Special
//

inline ScalarVec4f SIMD_Sqrt( const ScalarVec4f &lhs )
{
    ScalarVec4f newVec;

    for ( U32 i = 0; i < 4; ++i )
    {
        newVec()[i] = Mathf::Sqrt( lhs()[i] );
    }

    return newVec;
}

inline ScalarVec4f SIMD_Rcp( const ScalarVec4f &lhs )
{
    ScalarVec4f newVec;

    for ( U32 i = 0; i < 4; ++i )
    {
        newVec()[i] = Mathf::Rcp( lhs()[i] );
    }

    return newVec;
}

inline ScalarVec4f SIMD_RcpSqrt( const ScalarVec4f &lhs )
{
    return SIMD_Sqrt( SIMD_Rcp( lhs ) );
}

inline ScalarVec4f SIMD_Select( const ScalarVec4b &sel, const ScalarVec4f &lhs, const ScalarVec4f &rhs )
{
    ScalarVec4f newVec;

    for ( U32 i = 0; i < 4; ++i )
    {
        newVec()[i] = sel()[i] ? lhs()[i] : rhs()[i];
    }

    return newVec;
}

inline F32 SIMD_Hadd( const ScalarVec4f &lhs )
{
    F32 val = 0.0f;

    for ( U32 i = 0; i < 4; ++i )
    {
        val += lhs()[i];
    }

    return val;
}

inline ScalarVec4f FMA_ADD( const ScalarVec4f &mul1, const ScalarVec4f &mul2, const ScalarVec4f &add )
{
    return mul1 * mul2 + add;
}

inline ScalarVec4f FMA_SUB( const ScalarVec4f &mul1, const ScalarVec4f &mul2, const ScalarVec4f &sub )
{
    return mul1 * mul2 - sub;
}

#endif