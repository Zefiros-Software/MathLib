#pragma once
#ifndef __SCALAR_VEC4d_H__
#define __SCALAR_VEC4d_H__

#include "math/types.h"

#include "math/simd/simdVectorBase.h"

#include "math/simd/scalarFallback/scalar_vec4b.h"

class ScalarVec4d;

template <>
struct SimdTraits<F64>
{
    typedef F64 value_type;
    typedef ScalarVec4d vec_type;
    typedef ScalarVec4b bool_type;
    static const size_t width = 4;
    static const size_t bytesPerValue = 8;
};

class ScalarVec4d : public SimdVectorBase< ScalarVec4d, F64> 
{
public:

    ScalarVec4d()
    {}

    inline ScalarVec4d( F64 val )
    {
        for ( U32 i=0; i < 4; ++i )
        {
            mValue[i] = val;
        }
    }
    
    inline ScalarVec4d( F64 x, F64 y, F64 z, F64 w ) 
    {
        mValue[0] = x;
        mValue[1] = y;
        mValue[2] = z;
        mValue[3] = w;
    }
    
    inline ScalarVec4d( const F64 *rhs ) 
    {
    	std::copy( rhs,rhs+4, mValue );
    }

    inline ScalarVec4d &operator=( const F64 *rhs )
    {
        std::copy( rhs,rhs+4, mValue );

        return *this;
    }
    
    inline operator F64* ()
    {
        return mValue;
    }
    
    inline operator const F64* () const
    {
        return mValue;
    }
    
    void LoadUnaligned( const F64 *src )
    {
        std::copy( src,src+SimdTraits<F64>::width, mValue );
    }
    
    void LoadAligned( const F64 *src )
    {
        LoadUnaligned( src );
    }
    
    void StoreUnaligned( F64 *dest ) const
    {
        std::copy( mValue,mValue+SimdTraits<F64>::width, dest );
    }
    
    void StoreAligned( F64 *dest ) const
    {
        StoreUnaligned( dest );
    }
    
    void RotateOne( bool permute128  )
    {
        F64 temp = mValue[0];
        
        mValue[0] = mValue[1];
        mValue[1] = mValue[2];
        mValue[2] = mValue[3];
        mValue[3] = temp;
    }
    
    inline ScalarVec4d RoundToNearest() const
    {   
        ScalarVec4d newVec;

        for ( U32 i = 0; i < 4; ++i )
        {
            newVec()[i] = (F64) Mathf::Rint( mValue[i] );
        }
    
        return newVec;
    }

private:

    F64 mValue[4];
};

//
// Math
//

inline ScalarVec4d operator+( const ScalarVec4d &lhs, const ScalarVec4d &rhs )
{
    ScalarVec4d newVec;
    
    for ( U32 i=0; i < 4; ++i ) 
    {
        newVec()[i] = lhs()[i] + rhs()[i];
    }
    
    return newVec;
}

inline ScalarVec4d operator-( const ScalarVec4d &lhs, const ScalarVec4d &rhs )
{
    ScalarVec4d newVec;
    
    for ( U32 i=0; i < 4; ++i ) 
    {
        newVec()[i] = lhs()[i] - rhs()[i];
    }
    
    return newVec;
}

inline ScalarVec4d operator*( const ScalarVec4d &lhs, const ScalarVec4d &rhs )
{
    ScalarVec4d newVec;
    
    for ( U32 i=0; i < 4; ++i ) 
    {
        newVec()[i] = lhs()[i] * rhs()[i];
    }
    
    return newVec;
}

inline ScalarVec4d operator/( const ScalarVec4d &lhs, const ScalarVec4d &rhs )
{
    ScalarVec4d newVec;
    
    for ( U32 i=0; i < 4; ++i ) 
    {
        newVec()[i] = lhs()[i] / rhs()[i];
    }
    
    return newVec;
}

//
// Comparison
//

inline ScalarVec4b operator== ( const ScalarVec4d &lhs, const ScalarVec4d &rhs )
{
    ScalarVec4b newVec;
    
    for ( U32 i=0; i < 4; ++i ) 
    {
        newVec()[i] = lhs()[i] == rhs()[i];
    }
    
    return newVec;
}

inline ScalarVec4b operator!= ( const ScalarVec4d &lhs, const ScalarVec4d &rhs )
{
    ScalarVec4b newVec;
    
    for ( U32 i=0; i < 4; ++i ) 
    {
        newVec()[i] = lhs()[i] != rhs()[i];
    }
    
    return newVec;
}

inline ScalarVec4b operator< ( const ScalarVec4d &lhs, const ScalarVec4d &rhs )
{
    ScalarVec4b newVec;
    
    for ( U32 i=0; i < 4; ++i ) 
    {
        newVec()[i] = lhs()[i] < rhs()[i];
    }
    
    return newVec;
}

inline ScalarVec4b operator<= ( const ScalarVec4d &lhs, const ScalarVec4d &rhs )
{
    ScalarVec4b newVec;
    
    for ( U32 i=0; i < 4; ++i ) 
    {
        newVec()[i] = lhs()[i] <= rhs()[i];
    }
    
    return newVec;
}

inline ScalarVec4b operator> ( const ScalarVec4d &lhs, const ScalarVec4d &rhs )
{
    ScalarVec4b newVec;
    
    for ( U32 i=0; i < 4; ++i ) 
    {
        newVec()[i] = lhs()[i] > rhs()[i];
    }
    
    return newVec;
}

inline ScalarVec4b operator>= ( const ScalarVec4d &lhs, const ScalarVec4d &rhs )
{
    ScalarVec4b newVec;
    
    for ( U32 i=0; i < 4; ++i ) 
    {
        newVec()[i] = lhs()[i] >= rhs()[i];
    }
    
    return newVec;
}


//
// Special
//

inline ScalarVec4d SIMD_Sqrt( const ScalarVec4d &lhs )
{
   ScalarVec4d newVec;
    
    for ( U32 i=0; i < 4; ++i ) 
    {
        newVec()[i] = Mathf::Sqrt( lhs()[i] );
    }
    
    return newVec; 
}

inline ScalarVec4d SIMD_Rcp( const ScalarVec4d &lhs )
{
   ScalarVec4d newVec;
    
    for ( U32 i=0; i < 4; ++i ) 
    {
        newVec()[i] = Mathf::Rcp( lhs()[i] );
    }
    
    return newVec; 
}

inline ScalarVec4d SIMD_RcpSqrt( const ScalarVec4d &lhs )
{
   return SIMD_Sqrt( SIMD_Rcp(lhs) );
}

inline ScalarVec4d SIMD_Select( const ScalarVec4b &sel, const ScalarVec4d &lhs, const ScalarVec4d &rhs )
{
    ScalarVec4d newVec;
    
    for ( U32 i=0; i < 4; ++i ) 
    {
        newVec()[i] = sel()[i] ? lhs()[i] : rhs()[i];
    }
    
    return newVec;
}

inline F64 SIMD_Hadd( const ScalarVec4d &lhs )
{
    F64 val = 0.0f;
    
    for ( U32 i=0; i < 4; ++i ) 
    {
        val += lhs()[i];
    }
    
    return val;
}

inline ScalarVec4d FMA_ADD( const ScalarVec4d &mul1, const ScalarVec4d &mul2, const ScalarVec4d &add )
{
    return mul1 * mul2 + add;
}

inline ScalarVec4d FMA_SUB( const ScalarVec4d &mul1, const ScalarVec4d &mul2, const ScalarVec4d &sub )
{
    return mul1 * mul2 - sub;
}

#endif