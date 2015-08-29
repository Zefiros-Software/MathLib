#pragma once 
#ifndef __FP_VECTOR_H__
#define __FP_VECTOR_H__

#include "primayVectorBase.h"

template< class TYPE, U32 N >
class FloatingPointVector : public PrimayVectorBase< TYPE, N >
{
public:

    FloatingPointVector()
    {}

    FloatingPointVector(const PrimayVectorBase< TYPE, N > &lhs)
    {
        for (U32 i = 0; i < N; ++i)
        {
            mValues[i] = lhs[i];
        }
    }

    // Internal intrinsics
    inline TYPE Distance( const FloatingPointVector< TYPE, N > &v ) const
    {
        FloatingPointVector< TYPE, N > intermediate = (*this - v);

        return intermediate.Length();
    }
    
    inline TYPE Length() const
    {
        return Mathf::Sqrt( this->Length2() );
    }
    
    inline FloatingPointVector< TYPE, N > SafeNormalise()
    {
        const FloatingPointVector< TYPE, N > absv = this->Absolute();
        U8 max = absv.MaxAxis();
    
        if ( absv.mValues[max] > 0 )
        {
            assert( absv[max] != 0.0f );
            assert( Length() != 0.0f );
    
            FloatingPointVector< TYPE, N >(*this) /= absv.mValues[max];
            return FloatingPointVector< TYPE, N >(*this) /= Length();
        }
    
        this->SetValue( 0, 1.0f );
        this->SetValue( 1, 0.0f );
        this->SetValue( 2, 0.0f );
        
        return FloatingPointVector< TYPE, N >(*this);
    }
    
    inline FloatingPointVector< TYPE, N > Normalise()
    {
        assert( Length() != 0.0f );
    
        return FloatingPointVector< TYPE, N >(*this) /= Length();
    }
    
    inline FloatingPointVector< TYPE, N > Lerp( const FloatingPointVector< TYPE, N > &v, const TYPE t ) const
    {
        FloatingPointVector< TYPE, N > newVec;
        
        for ( U32 i=0; i < N; ++i )
        {
            newVec.SetValue( i,  Mathf::Lerp( this->mValues[i], v.mValues[i], t ) ); 
        }
        
        return newVec;
    }
    
    inline FloatingPointVector< TYPE, N > Slerp( const FloatingPointVector< TYPE, N > &v, const TYPE t ) const
    {
        TYPE dotp = Dot( v );
    
        // Make sure the floating point accuracy doesn't
        // crash our program
        Mathf::Clamp( dotp , -1.0f, 1.0f );
    
        TYPE theta = Mathf::Acos( dotp ) * t;
        FloatingPointVector< TYPE, N > relative = v - FloatingPointVector< TYPE, N >(*this) * dotp;
        relative.Normalise();
    
        return FloatingPointVector< TYPE, N >(*this) * Mathf::Cos( theta ) + relative * Mathf::Sin( theta );
    }
    
    inline FloatingPointVector< TYPE, N > Nlerp( const FloatingPointVector< TYPE, N > &v, const TYPE t ) const
    {
        return Lerp( v, t ).Normalise();
    }
    
    inline TYPE Angle( const FloatingPointVector< TYPE, N > &v ) const
    {
        TYPE s = Mathf::Sqrt( this->Length2() * v.Length2() );
    
        assert( s != 0.0f );
    
        return Mathf::Acos( Mathf::Clamp( Dot( v ) / s, -1.0f, 1.0f ) );
    }
};

#endif