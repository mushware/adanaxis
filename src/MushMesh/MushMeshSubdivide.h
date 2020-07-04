//%includeGuardStart {
#ifndef MUSHMESHSUBDIVIDE_H
#define MUSHMESHSUBDIVIDE_H
//%includeGuardStart } FKfqdVfsgtMZujotMytnhA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshSubdivide.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } o+avtbbrowp/dIi6LEKuRQ
/*
 * $Id: MushMeshSubdivide.h,v 1.16 2006/05/01 17:39:00 southa Exp $
 * $Log: MushMeshSubdivide.h,v $
 * Revision 1.16  2006/05/01 17:39:00  southa
 * Texture generation
 *
 * Revision 1.15  2005/05/19 13:02:11  southa
 * Mac release work
 *
 * Revision 1.14  2004/01/05 20:13:15  southa
 * Target and test updates
 *
 * Revision 1.13  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 * Revision 1.12  2003/10/25 15:56:58  southa
 * Test tweaks
 *
 * Revision 1.11  2003/10/25 14:27:30  southa
 * Triangle mesh fixes
 *
 * Revision 1.10  2003/10/25 11:08:17  southa
 * Triangular mesh work
 *
 * Revision 1.9  2003/10/24 20:41:15  southa
 * Triangular subdivision test and fixes
 *
 * Revision 1.8  2003/10/24 12:39:08  southa
 * Triangular mesh work
 *
 * Revision 1.7  2003/10/23 20:03:58  southa
 * End mesh work
 *
 * Revision 1.6  2003/10/18 20:28:38  southa
 * Subdivision speed tests
 *
 * Revision 1.5  2003/10/18 12:58:38  southa
 * Subdivision implementation
 *
 * Revision 1.4  2003/10/17 19:33:10  southa
 * Mesh patches
 *
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
#include "MushMeshUtils.h"

template <class T>
class MushMeshSubdivide
{
public:
    static void RectangularSubdivide(MushMeshArray<T>& outArray, const MushMeshArray<T>& inArray,
                                    Mushware::t2BoxU32 inActiveBox, Mushware::tVal inProp);
    static void TriangularSubdivide(MushMeshArray<T>& outArray, const MushMeshArray<T>& inArray,
                                    Mushware::t2BoxU32 inActiveBox, Mushware::U32 inOrder,
                                    Mushware::tVal inProp);
private:
    static Mushware::U32 M1Wrap(Mushware::U32 inValue, Mushware::U32 inWrap);
    static Mushware::U32 Z0Wrap(Mushware::U32 inValue, Mushware::U32 inWrap);
    static Mushware::U32 P1Wrap(Mushware::U32 inValue, Mushware::U32 inWrap);
};

template <class T>
inline void
MushMeshSubdivide<T>::RectangularSubdivide(MushMeshArray<T>& outArray, const MushMeshArray<T>& inArray,
                                           Mushware::t2BoxU32 inActiveBox, Mushware::tVal inProp)
{
    // class T is usually some flavour of MushMeshVector, not a simple arithmetic type

    /* Check that the active box is regular, and that we have at least 1 row or column
     * outside of the active box on all sides
     */
    MUSHCOREASSERT(inActiveBox.RegularIs());
    MUSHCOREASSERT(inActiveBox.Start().X() > 0);
    MUSHCOREASSERT(inActiveBox.Start().Y() > 0);
    MUSHCOREASSERT(inActiveBox.End().X() < inArray.XSizeGet());
    MUSHCOREASSERT(inActiveBox.End().Y() < inArray.YSizeGet());

    // These are start and end points for the first pass
    Mushware::t2U32 startPoint(inActiveBox.Start());
    Mushware::t2U32 endPoint(inActiveBox.End());

    // Size the output array appropriately for the active box
    outArray.SizeSet(2 * inActiveBox.SizeGet() + 1);

    /* destOffset is used to translate from input array indices to output array.
     * destPoint = 2*srcPoint - destOffset
     * Since we want startPoint to sit at 1,1 in the destination array
     * (to leave room for the border), 1 = 2*startPoint - destOffset
     */
    Mushware::t2U32 destOffset = startPoint * 2 - 1;

    // All of our points have a valence of 6
    Mushware::tVal alpha = MushMeshUtils::SubdivisionAlphaGet(6);
    Mushware::tVal alphaPlusNumVerts = alpha + 6;
    // Precalculate a few things
    Mushware::tVal inverseProp = 1 - inProp;
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

    // First pass
    for (Mushware::U32 x=startPoint.X(); x < endPoint.X(); ++x)
    {
        for (Mushware::U32 y=startPoint.Y(); y < endPoint.Y(); ++y)
        {
            // Calculate output coordinates;
            Mushware::U32 outX = 2*x - destOffset.X();
            Mushware::U32 outY = 2*y - destOffset.Y();

            /* Get references to the nine positions above.  m1m1 implies minus 1, minus 1,
             * i.e. x-1, y-1, and so on
             */

            // Some of these could be reused from the previous loop
            const T& n_m1m1 = inArray.Get(x-1, y-1);
            const T& n_z0m1 = inArray.Get(x,   y-1);
            // n_p1m1 not used
            const T& n_m1z0 = inArray.Get(x-1, y);
            const T& n_z0z0 = inArray.Get(x,   y);
            const T& n_p1z0 = inArray.Get(x+1, y);
            // n_m1p1 not used
            const T& n_z0p1 = inArray.Get(x,   y+1);
            const T& n_p1p1 = inArray.Get(x+1, y+1);
// Interleaving can give around 50% speed increase on G4 but only for simple types
// #define MUSHMESH_INTERLEAVE
#ifdef MUSHMESH_INTERLEAVE
            // Value0 is special as it is the original vertex and follows a different algorithm
            T value0 = n_z0z0;
            T value1 = n_z0z0;
            T value2 = n_z0z0;
            T value3 = n_z0z0;

            value0 *= alpha;
            value1 += n_p1z0;
            value2 += n_z0p1;
            value3 += n_p1p1;

            value0 += n_m1m1;
            value1 *= 3;
            value2 *= 3;
            value3 *= 3;
            
            value0 += n_z0m1;
            value1 += n_z0m1;
            value2 += n_m1z0;
            value3 += n_p1z0;
            
            value0 += n_m1z0;
            value1 += n_p1p1;
            value2 += n_p1p1;
            value3 += n_z0p1;

            value0 += n_p1z0;
            value1 *= propOver4;
            value2 *= propOver4;
            value3 *= propOver4;

            value0 += n_z0p1;
            value1 += (n_z0z0 + n_p1z0) * inverseProp;
            value0 += n_p1p1;
            value2 += (n_z0z0 + n_z0p1) * inverseProp;
            value0 /= alphaPlusNumVerts;
            value3 += (n_z0z0 + n_p1p1) * inverseProp;
            value0 *= inProp;

            value1 /= 2;
            value2 /= 2;
            value3 /= 2;
 
            value0 += n_z0z0 * inverseProp;

            outArray.Set(value1, outX+1, outY);
            outArray.Set(value2, outX, outY+1);
            outArray.Set(value3, outX+1, outY+1);
            outArray.Set(value0, outX, outY);
#else
            // Value0 is special as it is the original vertex and follows a different algorithm
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

            outArray.Set(value0, outX, outY);
             
            T value1 = n_z0z0;
            value1 += n_p1z0;
            value1 *= 3;
            value1 += n_z0m1;
            value1 += n_p1p1;
            value1 *= propOver4;
            value1 += (n_z0z0 + n_p1z0) * inverseProp;
            value1 /= 2;

            outArray.Set(value1, outX+1, outY);

            T value2 = n_z0z0;
            value2 += n_z0p1;
            value2 *= 3;
            value2 += n_m1z0;
            value2 += n_p1p1;
            value2 *= propOver4;
            value2 += (n_z0z0 + n_z0p1) * inverseProp;
            value2 /= 2;

            outArray.Set(value2, outX, outY+1);

            T value3 = n_z0z0;
            value3 += n_p1p1;
            value3 *= 3;
            value3 += n_p1z0;
            value3 += n_z0p1;
            value3 *= propOver4;
            value3 += (n_z0z0 + n_p1p1) * inverseProp;
            value3 /= 2;

            outArray.Set(value3, outX+1, outY+1);
#endif

        }
    }
    /* Second pass - edge points just below startPoint.Y.  This requires
     * points 2 and 3 only
     */
    {
        Mushware::U32 y = startPoint.Y()-1;
        Mushware::U32 outYp1 = 2*y + 1 - destOffset.Y();

        for (Mushware::U32 x=startPoint.X(); x < endPoint.X(); ++x)
        {
            Mushware::U32 outX = 2*x - destOffset.X();

            // Some of these could be reused from the previous loop
            // n_m1m1 not used
            // n_z0m1 not used
            // n_p1m1 not used
            const T& n_m1z0 = inArray.Get(x-1, y);
            const T& n_z0z0 = inArray.Get(x,   y);
            const T& n_p1z0 = inArray.Get(x+1, y);
            // n_m1p1 not used
            const T& n_z0p1 = inArray.Get(x,   y+1);
            const T& n_p1p1 = inArray.Get(x+1, y+1);

            T value2 = n_z0z0;
            value2 += n_z0p1;
            value2 *= 3;
            value2 += n_m1z0;
            value2 += n_p1p1;
            value2 *= propOver4;
            value2 += (n_z0z0 + n_z0p1) * inverseProp;
            value2 /= 2;

            outArray.Set(value2, outX, outYp1);

            T value3 = n_z0z0;
            value3 += n_p1p1;
            value3 *= 3;
            value3 += n_p1z0;
            value3 += n_z0p1;
            value3 *= propOver4;
            value3 += (n_z0z0 + n_p1p1) * inverseProp;
            value3 /= 2;

            outArray.Set(value3, outX+1, outYp1);
        }
    }
    
    /* Third pass - edge points just to the left of startPoint.X.  This requires
     * points 1 and 3 only
     */
    {
        Mushware::U32 x = startPoint.X()-1;
        Mushware::U32 outXp1 = 2*x + 1 - destOffset.X();

        for (Mushware::U32 y=startPoint.Y(); y < endPoint.Y(); ++y)
        {
            Mushware::U32 outY = 2*y - destOffset.Y();
            // Will be reordered

            /* Get references to the nine positions above.  m1m1 implies minus 1, minus 1,
             * i.e. x-1, y-1
             */

            // Some of these could be reused from the previous loop
            // n_m1m1 not used
            const T& n_z0m1 = inArray.Get(x,   y-1);
            // n_p1m1 not used
            // n_m1z0 not used
            const T& n_z0z0 = inArray.Get(x,   y);
            const T& n_p1z0 = inArray.Get(x+1, y);
            // n_m1p1 not used
            const T& n_z0p1 = inArray.Get(x,   y+1);
            const T& n_p1p1 = inArray.Get(x+1, y+1);
             
            T value1 = n_z0z0;
            value1 += n_p1z0;
            value1 *= 3;
            value1 += n_z0m1;
            value1 += n_p1p1;
            value1 *= propOver4;
            value1 += (n_z0z0 + n_p1z0) * inverseProp;
            value1 /= 2;

            outArray.Set(value1, outXp1, outY);

            T value3 = n_z0z0;
            value3 += n_p1p1;
            value3 *= 3;
            value3 += n_p1z0;
            value3 += n_z0p1;
            value3 *= propOver4;
            value3 += (n_z0z0 + n_p1p1) * inverseProp;
            value3 /= 2;

            outArray.Set(value3, outXp1, outY+1);

        }
    }
    /* Fourth pass - the single point just left of and below startPoint.
     * This requires only point 3
     */
    {
        Mushware::U32 x = startPoint.X()-1;
        Mushware::U32 y = startPoint.Y()-1;
        /* No need to calculate outX and outY because we know what they are.
         * Just check that our calculations would have worked instead
         */
        MUSHCOREASSERT(2*x + 1 - destOffset.X() == 0);
        MUSHCOREASSERT(2*y + 1 - destOffset.Y() == 0);
        {
            // n_m1m1 not used
            // n_z0m1 not used
            // n_p1m1 not used
            // n_m1z0 not used
            const T& n_z0z0 = inArray.Get(x,   y);
            const T& n_p1z0 = inArray.Get(x+1, y);
            // n_m1p1 not used
            const T& n_z0p1 = inArray.Get(x,   y+1);
            const T& n_p1p1 = inArray.Get(x+1, y+1);
             
            T value3 = n_z0z0;
            value3 += n_p1p1;
            value3 *= 3;
            value3 += n_p1z0;
            value3 += n_z0p1;
            value3 *= propOver4;
            value3 += (n_z0z0 + n_p1p1) * inverseProp;
            value3 /= 2;

            outArray.Set(value3, 0, 0);
        }
    }
}


template <class T>
inline Mushware::U32
MushMeshSubdivide<T>::M1Wrap(Mushware::U32 inValue, Mushware::U32 inWrap)
{
    return (inValue+inWrap-1) % inWrap;
}

template <class T>
inline Mushware::U32
MushMeshSubdivide<T>::Z0Wrap(Mushware::U32 inValue, Mushware::U32 inWrap)
{
    return inValue % inWrap;
}

template <class T>
inline Mushware::U32
MushMeshSubdivide<T>::P1Wrap(Mushware::U32 inValue, Mushware::U32 inWrap)
{
    return (inValue+1) % inWrap;
}


template <class T>
inline void
MushMeshSubdivide<T>::TriangularSubdivide(MushMeshArray<T>& outArray, const MushMeshArray<T>& inArray,
                                           Mushware::t2BoxU32 inActiveBox, Mushware::U32 inOrder,
                                           Mushware::tVal inProp)
{
    // class T is usually some flavour of MushMeshVector, not a simple arithmetic type

    /* Check that the active box is regular, that the active box is withing the array,
     * and that we have at least 1 extra row on the right hand side
     */
    MUSHCOREASSERT(inActiveBox.RegularIs());
    MUSHCOREASSERT(inActiveBox.End().X() < inArray.XSizeGet());
    MUSHCOREASSERT(inActiveBox.End().Y() <= inArray.YSizeGet());

    // These are start and end points for passes through the source array
    Mushware::t2U32 startPoint(inActiveBox.Start());
    // unused Mushware::t2U32 endPoint(inActiveBox.EndGet()); // + (1,0)?
    Mushware::t2U32 sizeVec = inActiveBox.SizeGet();

    // Size the output array appropriately for the active box
    outArray.SizeSet(2 * sizeVec);

    /* destOffset is used to translate from input array indices to output array.
     * destPoint = 2*srcPoint - destOffset
     * Since we want startPoint to sit at 0,0 in the destination array
     * (to leave room for the border), 0 = 2*startPoint - destOffset
     */
    Mushware::t2U32 destOffset = startPoint * 2;

    // Most of our points have a valence of 6, some have 5, the apex can have any number > 2

    Mushware::tVal alpha6 = MushMeshUtils::SubdivisionAlphaGet(6);
    Mushware::tVal alpha6PlusNumVerts = alpha6 + 6;
    // Precalculate a few things
    Mushware::tVal inverseProp = 1 - inProp;
    Mushware::tVal propOver4 = inProp/4;

    MUSHCOREASSERT(inOrder > 0);
    Mushware::U32 xDefect = startPoint.X() + (sizeVec.Y() / inOrder); // Column which holds the defects

    // Calculate the apex
    {
        const T& n_z0z0 = inArray.Get(0, 0);

        Mushware::U32 xeq1Wrap = inOrder;

        Mushware::tVal alpha = MushMeshUtils::SubdivisionAlphaGet(inOrder);

        T value0 = n_z0z0;
        value0 *= alpha;

        for (Mushware::U32 y=0; y<xeq1Wrap; ++y)
        {
            /* The apex point connects to each of the second row vertices, so
             * valency=order.  It generates order+1 vertices
             */
            const T& n_p1z0 = inArray.Get(1, startPoint.Y()+y);
            
            value0 += n_p1z0;

            T value1 = n_z0z0;
            value1 += n_p1z0;
            value1 *= 3;
            value1 += inArray.Get(1, M1Wrap(y, xeq1Wrap));
            value1 += inArray.Get(1, P1Wrap(y, xeq1Wrap));
            value1 *= propOver4;
            value1 += (n_z0z0 + n_p1z0) * inverseProp;
            value1 /= 2;

            outArray.Set(value1, 1, y);
        }

        value0 /= alpha + xeq1Wrap;            
        value0 *= inProp;
        value0 += n_z0z0 * inverseProp;
        outArray.Set(value0, 0, 0);
    }

    for (Mushware::U32 x=1; x < sizeVec.X(); ++x)
    {
        Mushware::U32 xz0Wrap = inOrder*x;
        Mushware::U32 xp1Wrap = xz0Wrap + inOrder;

        if (xz0Wrap > sizeVec.Y())
        {
            // Special case for right hand edge
            xz0Wrap = sizeVec.Y();
        }

        if (xp1Wrap > sizeVec.Y())
        {
            // Special case for right hand edge
            xp1Wrap = sizeVec.Y();
        }

        Mushware::U32 xm1Wrap;

        if (x <= 1)
        {
            // Special case for apex
            xm1Wrap = 1;
        }
        else
        {
            xm1Wrap = (x-1)*inOrder;
            if (xm1Wrap > sizeVec.Y())
            {
                xm1Wrap = sizeVec.Y();
            }
        }


        for (Mushware::U32 y=0; y < xz0Wrap; ++y)
        {
            /* Calculate the skew value.  This relies on unsigned integer division always
             * rounding downwards
             */
            MUSHCOREASSERT(x>0);
            Mushware::U32 skew = y/x;

            // Calculate output coordinates;
            Mushware::U32 outX = 2*x - destOffset.X();
            Mushware::U32 outY = 2*y - destOffset.Y();

            /* Get references to the nine positions above.  m1m1 implies minus 1, minus 1,
             * i.e. x-1, y-1, and so on
             */

            if (x < xDefect)
            {
                MUSHCOREASSERT(y < xz0Wrap); // needn't wrap x,y
                MUSHCOREASSERT(y+skew < xp1Wrap); // needn't wrap x+1, y+skew
                MUSHCOREASSERT(y+skew+1 < xp1Wrap); // needn't wrap x+1, y+skew+1

                const T& n_m1m1 = inArray.Get(x-1, M1Wrap(y-skew, xm1Wrap));
                const T& n_z0m1 = inArray.Get(x,   M1Wrap(y, xz0Wrap));
                const T& n_p1m1 = inArray.Get(x+1, M1Wrap(y+skew, xp1Wrap));
                
                const T& n_m1z0 = inArray.Get(x-1, Z0Wrap(y-skew, xm1Wrap));
                const T& n_z0z0 = inArray.Get(x,   y);
                const T& n_p1z0 = inArray.Get(x+1, y+skew);
                
                // n_m1p1 not used
                const T& n_z0p1 = inArray.Get(x,   P1Wrap(y, xz0Wrap));
                const T& n_p1p1 = inArray.Get(x+1, y+skew+1);

                // Value0 is special as it is the original vertex and follows a different algorithm
                T value0 = n_z0z0;
                T value1 = n_z0z0;
                value1 += n_p1z0;
                value1 *= 3;

                if (y % x == 0)
                {
                    /* Points in line with defects but not on the defect line.
                     * These are hexavalent but have three neighbours to the right
                     * of x.  They generate FIVE points
                     */

                    value0 *= alpha6;

                    value0 += n_m1z0;
                    value0 += n_z0m1;
                    value0 += n_z0p1;
                    value0 += n_p1m1;
                    value0 += n_p1z0;
                    value0 += n_p1p1;
                    
                    value0 /= alpha6PlusNumVerts;
                    
                    value0 *= inProp;
                    value0 += n_z0z0 * inverseProp;

                    // Calculate the fifth point
                    T value4 = n_z0z0;
                    value4 += n_p1m1;
                    value4 *= 3;
                    value4 += n_p1z0;
                    value4 += n_z0m1;
                    value4 *= propOver4;
                    value4 += (n_z0z0 + n_p1m1) * inverseProp;
                    value4 /= 2;
                    
                    // Wrapping point in the output array
                    Mushware::U32 outXp1Wrap = (x*2+1)*inOrder;

                    outArray.Set(value4, outX+1, M1Wrap(outY+skew, outXp1Wrap));

                    value1 += n_p1m1; // not n_z0m1
                }
                else
                {
                    /* Ordinary points between apex and defect line.
                     * These are hexavalent and generate 4 points.
                     * The edge points follow skewed rectangular form
                     */
                    value0 *= alpha6;
            
                    value0 += n_m1m1;
                    value0 += n_m1z0;
                    value0 += n_z0m1;
                    value0 += n_z0p1;
                    value0 += n_p1z0;
                    value0 += n_p1p1;
                    
                    value0 /= alpha6PlusNumVerts;
                    
                    value0 *= inProp;
                    value0 += n_z0z0 * inverseProp;

                    value1 += n_z0m1;
                }
                
                outArray.Set(value0, outX, outY);
                
                value1 += n_p1p1;
                value1 *= propOver4;
                value1 += (n_z0z0 + n_p1z0) * inverseProp;
                value1 /= 2;
                
                outArray.Set(value1, outX+1, outY+skew);
                
                T value2 = n_z0z0;
                value2 += n_z0p1;
                value2 *= 3;
                value2 += n_m1z0;
                value2 += n_p1p1;
                value2 *= propOver4;
                value2 += (n_z0z0 + n_z0p1) * inverseProp;
                value2 /= 2;
                
                outArray.Set(value2, outX, outY+1);
                
                T value3 = n_z0z0;
                value3 += n_p1p1;
                value3 *= 3;
                value3 += n_p1z0;
                value3 += n_z0p1;
                value3 *= propOver4;
                value3 += (n_z0z0 + n_p1p1) * inverseProp;
                value3 /= 2;
                
                outArray.Set(value3, outX+1, outY+skew+1);
            }
            else if (x > xDefect)
            {
                // The rectangular area, so unskewed
                MUSHCOREASSERT(y < xm1Wrap); // needn't wrap any plain y
                MUSHCOREASSERT(y < xz0Wrap); 
                MUSHCOREASSERT(y < xp1Wrap);

                

                const T& n_m1m1 = inArray.Get(x-1, M1Wrap(y, xm1Wrap));
                const T& n_z0m1 = inArray.Get(x,   M1Wrap(y, xz0Wrap));
                // n_p1m1 not used
                
                const T& n_m1z0 = inArray.Get(x-1, y);
                const T& n_z0z0 = inArray.Get(x,   y);
                const T& n_p1z0 = inArray.Get(x+1, y);
                
                // n_m1p1 not used
                const T& n_z0p1 = inArray.Get(x,   P1Wrap(y, xz0Wrap));
                const T& n_p1p1 = inArray.Get(x+1, P1Wrap(y, xp1Wrap));

                T value0 = n_z0z0;

                value0 *= alpha6;
                
                value0 += n_m1m1;
                value0 += n_m1z0;
                value0 += n_z0m1;
                value0 += n_z0p1;
                value0 += n_p1z0;
                value0 += n_p1p1;
                
                value0 /= alpha6PlusNumVerts;
                
                value0 *= inProp;
                value0 += n_z0z0 * inverseProp;
                
                outArray.Set(value0, outX, outY);
                
                T value1 = n_z0z0;
                value1 += n_p1z0;
                value1 *= 3;
                value1 += n_z0m1;
                value1 += n_p1p1;
                value1 *= propOver4;
                value1 += (n_z0z0 + n_p1z0) * inverseProp;
                value1 /= 2;
                
                outArray.Set(value1, outX+1, outY);
                
                T value2 = n_z0z0;
                value2 += n_z0p1;
                value2 *= 3;
                value2 += n_m1z0;
                value2 += n_p1p1;
                value2 *= propOver4;
                value2 += (n_z0z0 + n_z0p1) * inverseProp;
                value2 /= 2;
                
                outArray.Set(value2, outX, outY+1);
                
                T value3 = n_z0z0;
                value3 += n_p1p1;
                value3 *= 3;
                value3 += n_p1z0;
                value3 += n_z0p1;
                value3 *= propOver4;
                value3 += (n_z0z0 + n_p1p1) * inverseProp;
                value3 /= 2;
                
                outArray.Set(value3, outX+1, outY+1);
            }
            else // x == xDefect
            {
                MUSHCOREASSERT(y < xz0Wrap); // needn't wrap x,y
                MUSHCOREASSERT(y < xp1Wrap); // needn't wrap x+1, y
                

                // Values to the left of x are skewed
                const T& n_m1m1 = inArray.Get(x-1, M1Wrap(y-skew, xm1Wrap));
                const T& n_z0m1 = inArray.Get(x,   M1Wrap(y, xz0Wrap));
                // n_p1m1 not used
                
                const T& n_m1z0 = inArray.Get(x-1, Z0Wrap(y-skew, xm1Wrap));
                const T& n_z0z0 = inArray.Get(x,   y);
                const T& n_p1z0 = inArray.Get(x+1, y);
                
                // Values to the right of x are not skewed
                // n_m1p1 not used
                const T& n_z0p1 = inArray.Get(x,   P1Wrap(y, xz0Wrap));
                const T& n_p1p1 = inArray.Get(x+1, P1Wrap(y, xp1Wrap));

                T value0 = n_z0z0;

                if (y % x == 0)
                {
                    /* Defects in the defect line.  These are pentavalent and generate 4 points.
                     * The edge points follow the basic rectangular form
                     */

                    Mushware::tVal alpha5 = MushMeshUtils::SubdivisionAlphaGet(5);
                    value0 *= alpha5;
            
                    value0 += n_m1z0;
                    value0 += n_z0m1;
                    value0 += n_z0p1;
                    value0 += n_p1z0;
                    value0 += n_p1p1;
                    
                    value0 /= alpha5 + 5;
                    
                    value0 *= inProp;
                    value0 += n_z0z0 * inverseProp;    
                }
                else
                {
                    /* Non-defects in the defect line.  These are hexavalent and generate 4 points.
                     * The edge points follow the basic rectangular form
                     */
                    value0 *= alpha6;
            
                    value0 += n_m1m1;
                    value0 += n_m1z0;
                    value0 += n_z0m1;
                    value0 += n_z0p1;
                    value0 += n_p1z0;
                    value0 += n_p1p1;
                    
                    value0 /= alpha6PlusNumVerts;
                    
                    value0 *= inProp;
                    value0 += n_z0z0 * inverseProp;
                }
                
                outArray.Set(value0, outX, outY);
                
                T value1 = n_z0z0;
                value1 += n_p1z0;
                value1 *= 3;
                value1 += n_z0m1;
                value1 += n_p1p1;
                value1 *= propOver4;
                value1 += (n_z0z0 + n_p1z0) * inverseProp;
                value1 /= 2;
                
                outArray.Set(value1, outX+1, outY);
                
                T value2 = n_z0z0;
                value2 += n_z0p1;
                value2 *= 3;
                value2 += n_m1z0;
                value2 += n_p1p1;
                value2 *= propOver4;
                value2 += (n_z0z0 + n_z0p1) * inverseProp;
                value2 /= 2;
                
                outArray.Set(value2, outX, outY+1);
                
                T value3 = n_z0z0;
                value3 += n_p1p1;
                value3 *= 3;
                value3 += n_p1z0;
                value3 += n_z0p1;
                value3 *= propOver4;
                value3 += (n_z0z0 + n_p1p1) * inverseProp;
                value3 /= 2;
                
                outArray.Set(value3, outX+1, outY+1);
            }
        }
    }
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
