//%includeGuardStart {
#ifndef MUSHMESHMATH_H
#define MUSHMESHMATH_H
//%includeGuardStart } ZghGN7KlqsaRqIda0rIylg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshMath.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } KjVCAaiP9AXyz0sqvTXz+A
/*
 * $Id: MushMeshMath.h,v 1.2 2003/10/15 12:26:58 southa Exp $
 * $Log: MushMeshMath.h,v $
 * Revision 1.2  2003/10/15 12:26:58  southa
 * MushMeshArray neighbour testing and subdivision work
 *
 * Revision 1.1  2003/10/15 11:54:54  southa
 * MushMeshArray neighbour testing and subdivision
 *
 */

#include "MushMeshStandard.h"

#if 0
template <class T>
inline bool
operator==(const MushwareValarray<T>& a, const MushwareValarray<T>& b)
{
    if (a.size() != b.size())
    {
        return false;
    }

    for (i=0; i < a.size(); ++i)
    {
        if (a[i] != b[i])
        {
            return false;
        }
    }
    return true;
}
#endif

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
