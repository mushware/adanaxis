//%includeGuardStart {
#ifndef TESTMUSHMESHBOX_H
#define TESTMUSHMESHBOX_H
//%includeGuardStart } lj50ZsgWJBEaKPiuIrzn0Q
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshBox.h
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 30sotOXGdb32F7C5g1AgRg
/*
 * $Id: TestMushMeshBox.h,v 1.3 2005/05/19 13:02:23 southa Exp $
 * $Log: TestMushMeshBox.h,v $
 * Revision 1.3  2005/05/19 13:02:23  southa
 * Mac release work
 *
 * Revision 1.2  2004/01/02 21:13:17  southa
 * Source conditioning
 *
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
