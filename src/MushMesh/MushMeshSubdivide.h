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
 * $Id: MushMeshSubdivide.h,v 1.2 2003/10/15 12:26:59 southa Exp $
 * $Log: MushMeshSubdivide.h,v $
 * Revision 1.2  2003/10/15 12:26:59  southa
 * MushMeshArray neighbour testing and subdivision work
 *
 * Revision 1.1  2003/10/15 11:54:54  southa
 * MushMeshArray neighbour testing and subdivision
 *
 */

#include "MushMeshStandard.h"
#include "MushMeshArray.h"

template <class T>
class MushMeshSubdivide
{
public:
    static void Subdivide(MushMeshArray<T>& outArray, const MushMeshArray<T>& inArray, Mushware::tVal inProp);
    static void Move(MushMeshArray<T>& outArray, const MushMeshArray<T>& inArray, Mushware::tVal inProp);
};

template <class T>
inline void
MushMeshSubdivide<T>::Move(MushMeshArray<T>& outArray, const MushMeshArray<T>& inArray, Mushware::tVal inProp)
{
    MushwareValarray<const T *> verts(MushMeshArray<T>::kMaxVerts);
    Mushware::U32 numVerts;

    outArray.SizeSet(inArray.SizeGet());

    for (Mushware::U32 x=0; x < inArray.XSizeGet(); ++x)
    {
        for (Mushware::U32 y=0; y < inArray.YSizeGet(); ++y)
        {
            inArray.VertexNeighboursGet(verts, numVerts, x, y);

            T value = inArray.Get(x, y);
            
            Mushware::tVal alpha = MushMeshUtils::SubdivisionAlphaGet(numVerts);

            value *= alpha;

            for (Mushware::U32 v=0; v < numVerts; ++v)
            {
                 value += *verts[v];
            }

            value /= alpha + numVerts;

            value *= inProp;
            value += inArray.Get(x, y) * (1 - inProp);

            outArray.Set(value, x, y);
        }
    }
}

template <class T>
inline void
MushMeshSubdivide<T>::Subdivide(MushMeshArray<T>& outArray, const MushMeshArray<T>& inArray, Mushware::tVal inProp)
{
    MushwareValarray<const T *> verts(MushMeshArray<T>::kMaxVerts);
    Mushware::U32 numVerts;

    outArray.SizeSet(2 * inArray.SizeGet());

    for (Mushware::U32 x=0; x < inArray.XSizeGet(); ++x)
    {
        for (Mushware::U32 y=0; y < inArray.YSizeGet(); ++y)
        {
            inArray.VertexNeighboursGet(verts, numVerts, x, y);

            T value = inArray.Get(x, y);
            
            Mushware::tVal alpha = MushMeshUtils::SubdivisionAlphaGet(numVerts);

            value *= alpha;

            for (Mushware::U32 v=0; v < numVerts; ++v)
            {
                 value += *verts[v];
            }

            value /= alpha + numVerts;

            value *= inProp;
            value += inArray.Get(x, y) * (1 - inProp);

            outArray.Set(value, 2*x, 2*y);
        }
    }
}


//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
