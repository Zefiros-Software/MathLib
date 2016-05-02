/**
 * @cond ___LICENSE___
 *
 * Copyright (c) 2014 Koen Visscher, Paul Visscher and individual contributors.
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
#ifndef __VEC4_H__
#define __VEC4_H__

#include "math/config.h"
#include "math/scalar/vec2.h"
#include "math/scalar/vec3.h"
#include "math/generic/floatingPointVector.h"

BEGIN_MATH_NAMESPACE

class Vec4 : public FloatingPointVector< Real, 4 >
{
public:

    Vec4()
    {
        
    }
    
    Vec4( Real p1 )
    {
        SetValues( p1, p1, p1, p1 );
    }
    
    Vec4( Real p1, Real p2, Real p3, Real p4 )
    {
        SetValues( p1, p2, p3, p4 );
    }
    
    Vec4( const Vec2 &v1, const Vec2 &v2 )
    {
        SetValues( v1[0], v1[1], v2[0], v2[1] );
    }
    
    Vec4( Real p1, const Vec3 &v1 )
    {
        SetValues( p1, v1[0], v1[1], v1[2] );
    }
    
    Vec4( const Vec3 &v1, Real p1 )
    {
        SetValues( v1[0], v1[1], v1[2], p1 );
    }
    
    template< class TYPE2 >
    inline Vec4( const PrimaryVectorBase< TYPE2, 4 > &v1 )
    {
        SetValues( (Real) v1[0], (Real) v1[1], (Real) v1[2], (Real) v1[3] );
    }
    
    Vec4(const FloatingPointVector< Real, 4 > &v1)
    {
        SetValues(v1[0], v1[1], v1[2], v1[3]);
    }
        
};

#endif