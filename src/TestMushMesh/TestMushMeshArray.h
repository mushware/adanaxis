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
 * $Id: TestMushMeshArray.h,v 1.3 2003/10/15 12:23:10 southa Exp $
 * $Log: TestMushMeshArray.h,v $
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

class TestMushMeshArray
{
public:
    static MushcoreScalar TestArray(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);

private:
    static Mushware::U32 ValueFunction(Mushware::U32 inX, Mushware::U32 inY);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
