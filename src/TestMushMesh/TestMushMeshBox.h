//%includeGuardStart {
#ifndef TESTMUSHMESHBOX_H
#define TESTMUSHMESHBOX_H
//%includeGuardStart } lj50ZsgWJBEaKPiuIrzn0Q
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshBox.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } y/xKb7oW7RyI23COR8XAQA
/*
 * $Id: TestMushMeshBox.h,v 1.1 2003/10/17 12:27:20 southa Exp $
 * $Log: TestMushMeshBox.h,v $
 * Revision 1.1  2003/10/17 12:27:20  southa
 * Line end fixes and more mesh work
 *
 */

#include "TestMushMeshStandard.h"

class TestMushMeshBox
{
public:
    static MushcoreScalar TestBox(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
