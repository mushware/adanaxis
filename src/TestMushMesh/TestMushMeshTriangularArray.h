//%includeGuardStart {
#ifndef TESTMUSHMESHTRIANGULARARRAY_H
#define TESTMUSHMESHTRIANGULARARRAY_H
//%includeGuardStart } lyinEX4LVI++dsjzRARngQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshTriangularArray.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Y8q23lhLrvwRtbKidXno/A
/*
 * $Id: TestMushMeshArray.h,v 1.5 2003/10/20 13:02:55 southa Exp $
 * $Log: TestMushMeshArray.h,v $
 * Revision 1.5  2003/10/20 13:02:55  southa
 * Patch fixes and testing
 *
 * Revision 1.4  2003/10/17 19:33:11  southa
 * Mesh patches
 *
 * Revision 1.3  2003/10/15 12:23:10  southa
 * MushMeshArray neighbour testing and subdivision work
 *
 * Revision 1.2  2003/10/15 11:54:54  southa
 * MushMeshArray neighbour testing and subdivision
 *
 * Revision 1.1  2003/10/15 07:08:29  southa
 * MushMeshArray creation
 *
 */

#include "TestMushMeshStandard.h"

class TestMushMeshTriangularArray
{
public:
    static MushcoreScalar TestTriangularArray(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);

private:
    enum
    {
        kXMax = 5,
        kOrder = 3
    };

    static void ArrayVerify(const MushMeshTriangularArray<Mushware::U32>& inArray, const std::string& inName);
    static Mushware::U32 ValueFunction(Mushware::U32 inX, Mushware::U32 inY);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
