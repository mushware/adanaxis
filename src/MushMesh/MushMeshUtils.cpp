//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshUtils.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 32mFSsTNLHJgXJZJxCfxrQ
/*
 * $Id: MushMeshUtils.cpp,v 1.4 2003/10/23 20:03:58 southa Exp $
 * $Log: MushMeshUtils.cpp,v $
 * Revision 1.4  2003/10/23 20:03:58  southa
 * End mesh work
 *
 * Revision 1.3  2003/10/15 12:26:59  southa
 * MushMeshArray neighbour testing and subdivision work
 *
 * Revision 1.2  2003/10/15 07:08:29  southa
 * MushMeshArray creation
 *
 * Revision 1.1  2003/10/14 13:07:25  southa
 * MushMesh vector creation
 *
 */

#include "MushMeshUtils.h"

#include "MushMeshBox.h"
#include "MushMeshSTL.h"

using namespace Mushware;
using namespace std;

const tVal MushMeshUtils::m_alphaTable[kMaxValence] =
{
    0,
    3.26667,
    1.28205,
    2.33333,
    4.25806,
    6.89157,
    10,
    13.3978
};

void
MushMeshUtils::BoundaryThrow(U32 inValue, U32 inLimit)
{
    ostringstream message;
    message << "Access out of bounds (" << inValue << " >= " << inLimit << ')';
    throw MushcoreLogicFail(message.str()) ;
}

void
MushMeshUtils::BoundaryThrow(Mushware::U32 inValue1, Mushware::U32 inLimit1, Mushware::U32 inValue2, Mushware::U32 inLimit2)
{
    ostringstream message;
    message << "Access out of bounds (" << inValue1 << " >= " << inLimit1 << " or " << inValue2 << " >= " << inLimit2 << ')';
    throw MushcoreLogicFail(message.str()) ;
}

#if 0
// Doesn't work
Mushware::U32
MushMeshUtils::TriangleOrderGet(const Mushware::t2U32& inSize)
{
    MUSHCOREASSERT(inSize.X() > 2);
    MUSHCOREASSERT(inSize.Y() > 1);

    U32 order = inSize.Y() / (inSize.X() - 2);
    if (order * (inSize.X() - 2) != inSize.Y())
    {
        ostringstream message;
        message << "Bad triangle size: x=" << inSize.X() << ", y=" << inSize.Y() << ", y != n(x-2)";
        throw MushcoreDataFail(message.str());
    }
    return order;
}
#endif

tVal
MushMeshUtils::SubdivisionAlphaCalculate(Mushware::U32 inN)
{
    MUSHCOREASSERT(inN > 0);

    tVal a;
    a = 3.0 + 2.0 * cos((2*M_PI) / inN);
    a = 0.625 - a*a/64.0;

    return inN * (1.0 - a) / a;
}
