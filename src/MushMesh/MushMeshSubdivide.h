//%includeGuardStart {
#ifndef MUSHMESHSUBDIVIDE_H
#define MUSHMESHSUBDIVIDE_H
//%includeGuardStart } FKfqdVfsgtMZujotMytnhA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshSubdivide.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 52PDoNY8UY0CW0LzYPWXdA
/*
 * $Id: MushMeshSubdivide.h,v 1.3 2003/10/17 12:27:19 southa Exp $
 * $Log: MushMeshSubdivide.h,v $
 * Revision 1.3  2003/10/17 12:27:19  southa
 * Line end fixes and more mesh work
 *
 * Revision 1.2  2003/10/15 12:26:59  southa
 * MushMeshArray neighbour testing and subdivision work
 *
 * Revision 1.1  2003/10/15 11:54:54  southa
 * MushMeshArray neighbour testing and subdivision
 *
 */

#include "MushMeshStandard.h"
#include "MushMeshArray.h"
#include "MushMeshBox.h"

template <class T>
class MushMeshSubdivide
{
public:
    static void RectangularSubdivide(MushMeshArray<T>& outArray, const MushMeshArray<T>& inArray,
                                    Mushware::t2BoxU32 inActiveBox, Mushware::tVal inProp);
};

template <class T>
inline void
MushMeshSubdivide<T>::RectangularSubdivide(MushMeshArray<T>& outArray, const MushMeshArray<T>& inArray,
                                           Mushware::t2BoxU32 inActiveBox, Mushware::tVal inProp)
{
    // class T is usually some flavour of MushMeshVector, not a simple arithmetic type

    outArray.SizeSet(2 * inArray.SizeGet());

    MUSHCOREASSERT(inActiveBox.RegularIs());
    
    Mushware::t2U32 startPoint(inActiveBox.StartGet() - Mushware::t2U32(1, 1));
    Mushware::t2U32 endPoint(inActiveBox.EndGet() + Mushware::t2U32(1, 1));

    // All of our points have a valence of 6
    Mushware::tVal alpha = MushMeshUtils::SubdivisionAlphaGet(6);
    Mushware::tVal alphaPlusNumVerts = alpha + 6;
    // Precalculate a few things
    Mushware::tVal inverseProp = 1 - inProp;
    Mushware::tVal inversePropOver2 = inverseProp / 2;
    Mushware::tVal propOver4 = inProp/4;


    /* Iterate through points in the source array, writing points in
     * the destination array four at a time
     *
     * m1p1   z0p1   p1p1
     * +------2------3
     * |     /|     /|
     * |    / |    / |
     * |   /  |   /  |
     * |  /   |  /   |
     * | /    | /    |
     * |/     |/     |
     * +------0------1
     * |m1z0 /|z0z0 /| p1z0
     * |    / |    / |
     * |   /  |   /  |
     * |  /   |  /   |
     * | /    | /    |
     * |/     |/     |
     * +------+------+
     * m1m1   z0m1   p1m1
     * Point zero is a point in the original array.  Operations are interelaved
     * to avoid stalling the floating point units, and each operation aims to be
     * a single SIMD instruction.
     *
     * New vertices are generated at the mid points of lines 0->1, 0->2 and 0->3.
     * See Loop's algorithm for which points contribute where
     */
    for (Mushware::U32 x=startPoint.X(); x < endPoint.X(); ++x)
    {
        for (Mushware::U32 y=startPoint.Y(); y < endPoint.Y(); ++y)
        {
            // Will be reordered

            /* Get references to the nine positions above.  m1m1 implies minus 1, minus 1,
             * i.e. x-1, y-1
             */
            const T& n_m1m1 = inArray.Get(x-1, y-1);
            const T& n_z0m1 = inArray.Get(x,   y-1);
            // n_p1m1 not used
            const T& n_m1z0 = inArray.Get(x-1, y);
            const T& n_z0z0 = inArray.Get(x,   y);
            const T& n_p1z0 = inArray.Get(x+1, y);
            // n_m1p1 not used
            const T& n_z0p1 = inArray.Get(x,   y+1);
            const T& n_p1p1 = inArray.Get(x+1, y+1);

            // Value0 is special as it is the original vertex and follows as different algorithm
            T value0 = n_z0z0;

            value0 *= alpha;
            
            value0 += n_m1m1;
            value0 += n_z0m1;
            value0 += n_m1z0;
            value0 += n_p1z0;
            value0 += n_z0p1;
            value0 += n_p1p1;

            value0 /= alphaPlusNumVerts;

            value0 *= inProp;
            value0 += n_z0z0 * inverseProp;

            outArray.Set(value0, 2*x, 2*y);
             
            T value1 = n_z0z0;
            value1 += n_p1z0;
            value1 *= 3;
            value1 += n_z0m1;
            value1 += n_p1p1;
            value1 *= propOver4;
            value1 += (n_z0z0 + n_p1z0) * inversePropOver2;
            value1 /= 2;

            outArray.Set(value1, 2*x+1, 2*y);

            T value2 = n_z0z0;
            value2 += n_z0p1;
            value2 *= 3;
            value2 += n_m1z0;
            value2 += n_p1p1;
            value2 *= propOver4;
            value2 += (n_z0z0 + n_z0p1) * inversePropOver2;
            value2 /= 2;

            outArray.Set(value2, 2*x, 2*y+1);

            T value3 = n_z0z0;
            value3 += n_p1p1;
            value3 *= 3;
            value3 += n_p1z0;
            value3 += n_z0p1;
            value3 *= propOver4;
            value3 += (n_z0z0 + n_p1p1) * inversePropOver2;
            value3 /= 2;

            outArray.Set(value3, 2*x+1, 2*y+1);

        }
    }
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
