//%includeGuardStart {
#ifndef TESTMUSHMESHPOSTMATRIX_H
#define TESTMUSHMESHPOSTMATRIX_H
//%includeGuardStart } 7Lxc5UoUlhH7X+YSVRetNg
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshPostMatrix.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 77qNslD+0dAAmIBbxNKncA
/*
 * $Id$
 * $Log$
 */
#include "TestMushMeshStandard.h"

class TestMushMeshPostMatrix
{
public:
    static MushcoreScalar TestPostMatrix(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    
private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
