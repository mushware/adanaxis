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
 * $Id: MushMeshUtils.cpp,v 1.2 2003/10/15 07:08:29 southa Exp $
 * $Log: MushMeshUtils.cpp,v $
 * Revision 1.2  2003/10/15 07:08:29  southa
 * MushMeshArray creation
 *
 * Revision 1.1  2003/10/14 13:07:25  southa
 * MushMesh vector creation
 *
 */

#include "MushMeshUtils.h"

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

tVal
MushMeshUtils::SubdivisionAlphaCalculate(Mushware::U32 inN)
{
    MUSHCOREASSERT(inN > 0);

    tVal a;
    a = 3.0 + 2.0 * cos((2*M_PI) / inN);
    a = 0.625 - a*a/64.0;

    return inN * (1.0 - a) / a;
}
