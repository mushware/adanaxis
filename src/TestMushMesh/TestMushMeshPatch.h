//%includeGuardStart {
#ifndef TESTMUSHMESHPATCH_H
#define TESTMUSHMESHPATCH_H
//%includeGuardStart } BFG5WurStwvR3cwySRKGUQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshPatch.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } BpjMJ+EMJ1RMIN6aiXGruQ
/*
 * $Id$
 * $Log$
 */


#include "TestMushMeshStandard.h"

class TestMushMeshPatch
{
public:
    static MushcoreScalar TestPatch(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);

private:
    enum
    {
        kXMax = 5,
        kYMax = 6
    };

    static void GeometryPrint(const Mushware::tGeometryArray& inArray);

    static bool ChangeVerify(const Mushware::tGeometryArray& inArray1,
                             const Mushware::tGeometryArray& inArray2,
                             Mushware::U32 inChanges);
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
