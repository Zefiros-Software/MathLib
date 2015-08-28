#pragma once
#ifndef __SCALAR_VEC_4B_H__
#define __SCALAR_VEC_4B_H__

#include "math/types.h"

#include "math/simd/simdVectorBoolBase.h"

class ScalarVec4b : public SimdVectorBoolBase< ScalarVec4b > 
{
public:

    ScalarVec4b()
    {}

    inline ScalarVec4b( bool val )
    {
        for ( U32 i=0; i < 4; ++i )
        {
            mValue[i] = val;
        }
    }
    
    inline ScalarVec4b( bool x, bool y, bool z, bool w ) 
    {
        mValue[0] = x;
        mValue[1] = y;
        mValue[2] = z;
        mValue[3] = w;
    }
    
    inline ScalarVec4b( const bool *rhs ) 
    {
    	std::copy( rhs,rhs+4, mValue );
    }

    inline ScalarVec4b &operator=( const bool *rhs )
    {
        std::copy( rhs,rhs+4, mValue );

        return *this;
    }
    
    inline operator bool* ()
    {
        return mValue;
    }
    
    inline operator const bool* () const
    {
        return mValue;
    }
    
    void StoreAligned( F32 *dest ) const
    {
        for ( U32 i=0; i < 4; ++i ) 
        {
            dest[i] = (F32) mvalue[i];
        }
    }

    void LoadAligned( const F32 *src ) 
    {
        for ( U32 i=0; i < 4; ++i ) 
        {
            mvalue[i] = (bool) src[i];
        }
    }
    
    template< U32 rotate >
    inline void LoadMask( U64 mask ) 
    {
        mValue[0] = ( mask >> ( 0  + ( 0 + rotate ) % 4 ) ) & 0x1;
        mValue[1] = ( mask >> ( 4  + ( 1 + rotate ) % 4 ) ) & 0x1;
        mValue[2] = ( mask >> ( 8  + ( 2 + rotate ) % 4 ) ) & 0x1;
        mValue[3] = ( mask >> ( 12 + ( 3 + rotate ) % 4 ) ) & 0x1;                    
    }
    
private:

    bool mValue[4];
};

inline ScalarVec4b operator&( const ScalarVec4b &lhs, const ScalarVec4b &rhs )
{
    ScalarVec4b newVec;
    
    for ( U32 i=0; i < 4; ++i ) 
    {
        newVec()[i] = lhs()[i] & rhs()[i];
    }
    
    return newVec;
}

inline ScalarVec4b operator|( const ScalarVec4b &lhs, const ScalarVec4b &rhs )
{
    ScalarVec4b newVec;
    
    for ( U32 i=0; i < 4; ++i ) 
    {
        newVec()[i] = lhs()[i] | rhs()[i];
    }
    
    return newVec;
}

inline ScalarVec4b operator^( const ScalarVec4b &lhs, const ScalarVec4b &rhs )
{
    ScalarVec4b newVec;
    
    for ( U32 i=0; i < 4; ++i ) 
    {
        newVec()[i] = lhs()[i] ^ rhs()[i];
    }
    
    return newVec;
}

inline ScalarVec4b operator==( const ScalarVec4b &lhs, const ScalarVec4b &rhs )
{
    ScalarVec4b newVec;
    
    for ( U32 i=0; i < 4; ++i ) 
    {
        newVec()[i] = lhs()[i] == rhs()[i];
    }
    
    return newVec;
}

inline ScalarVec4b operator!=( const ScalarVec4b &lhs, const ScalarVec4b &rhs )
{
    ScalarVec4b newVec;
    
    for ( U32 i=0; i < 4; ++i ) 
    {
        newVec()[i] = lhs()[i] != rhs()[i];
    }
    
    return newVec;
}

inline bool SIMD_Hadd( const SSE41Vec4b &lhs )
{
    int val = 0;
    
    for ( U32 i=0; i < 4; ++i ) 
    {
        val += lhs()[i];
    }
    
    return (bool)val;
}


#endif