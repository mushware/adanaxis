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
 * $Id$
 * $Log$
 */

#include "MushMeshStandard.h"
#include "MushMeshVector.h"
#include "MushMeshPreMatrix.h"

class MushMeshTools
{
public:
    static MushMeshPreMatrix<Mushware::tVal, 3, 3> RotateInXY(Mushware::tVal inAngle);
    static MushMeshPreMatrix<Mushware::tVal, 4, 4> RotateInAxis(Mushware::U32 inAxis, Mushware::tVal inAngle);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
