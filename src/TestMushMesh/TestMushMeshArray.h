//%includeGuardStart {
#ifndef TESTMUSHMESHARRAY_H
#define TESTMUSHMESHARRAY_H
//%includeGuardStart } nvK6t6OW0Lv8bF+/agTL8Q
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshArray.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } fToIyQQx8JGxur8jZBbZlg
/*
 * $Id: TestMushMeshArray.h,v 1.1 2003/10/15 07:08:29 southa Exp $
 * $Log: TestMushMeshArray.h,v $
 * Revision 1.1  2003/10/15 07:08:29  southa
 * MushMeshArray creation
 *
 */

#include "TestMushMeshStandard.h"

class TestMushMeshArray
{
public:
    static MushcoreScalar TestArray(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);

private:
    struct tNeighbourPoint
    {
        Mushware::U32 nx;
        Mushware::U32 ny;
    };

    struct tNeighbourSpec
    {
        Mushware::U32 x;
        Mushware::U32 y;
        Mushware::U32 numNeighbours;
        tNeighbourPoint neighbours[6];
    };

    static Mushware::U32 ValueFunction(Mushware::U32 inX, Mushware::U32 inY);
    static void CheckNeighbours(const tNeighbourSpec& inSpec, const MushwareValarray<const Mushware::U32 *>& inVerts,
                                Mushware::U32 inNumVerts, Mushware::U32 inNumTest);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
