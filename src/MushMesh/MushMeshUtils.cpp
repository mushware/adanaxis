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
 * $Id$
 * $Log$
 */

#include "MushMeshUtils.h"

#include "MushMeshSTL.h"

using namespace Mushware;
using namespace std;

void
MushMeshUtils::BoundaryThrow(U32 inValue, U32 inLimit)
{
    ostringstream message;
    message << "Access out of bounds (" << inValue << " >= " << inLimit << ')';
    throw MushcoreLogicFail(message.str()) ;
}
