//%includeGuardStart {
#ifndef TESTMUSHMESHOPS_H
#define TESTMUSHMESHOPS_H
//%includeGuardStart } 4dGfAMR+uoe7iTaqb4c6XQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshOps.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } B8pdFksUBCzTrPbum/1twA
/*
 * $Id: TestMushMeshOps.h,v 1.1 2004/11/17 23:43:48 southa Exp $
 * $Log: TestMushMeshOps.h,v $
 * Revision 1.1  2004/11/17 23:43:48  southa
 * Added outer product
 *
 */
#include "TestMushMeshStandard.h"

class TestMushMeshOps
{
public:
    static MushcoreScalar TestInnerProduct(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar TestOuterProduct(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar TestNormalise(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar TestSlerp(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    
private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
