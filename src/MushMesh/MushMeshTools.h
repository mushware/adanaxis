//%includeGuardStart {
#ifndef MUSHMESHTOOLS_H
#define MUSHMESHTOOLS_H
//%includeGuardStart } 3QmVbluf3UkkQebEInihFQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshTools.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } R8PJKwqR61qEAsXpbOlPGQ
/*
 * $Id: MushMeshTools.h,v 1.1 2004/10/31 23:34:07 southa Exp $
 * $Log: MushMeshTools.h,v $
 * Revision 1.1  2004/10/31 23:34:07  southa
 * Hypercube rendering test
 *
 */

#include "MushMeshStandard.h"
#include "MushMeshVector.h"
#include "MushMeshQuaternion.h"
#include "MushMeshPreMatrix.h"

class MushMeshTools
{
public:
    static Mushware::t3x3Val RotateInXY(Mushware::tVal inAngle);
    static Mushware::t4x4Val MatrixRotateInAxis(Mushware::U32 inAxis, Mushware::tVal inAngle);
    static Mushware::tQValPair QuaternionRotateInAxis(Mushware::U32 inAxis, Mushware::tVal inAngle);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
