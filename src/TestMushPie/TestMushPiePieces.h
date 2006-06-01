//%includeGuardStart {
#ifndef TESTMUSHPIEPIECES_H
#define TESTMUSHPIEPIECES_H
//%includeGuardStart } m33WbJWvRZbCH8H/4tVjHg
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushPie/TestMushPiePieces.h
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
//%Header } zON+zSQMckxxWqqN801QLQ
/*
 * $Id: TestMushPiePieces.h,v 1.2 2005/05/19 13:02:24 southa Exp $
 * $Log: TestMushPiePieces.h,v $
 * Revision 1.2  2005/05/19 13:02:24  southa
 * Mac release work
 *
 * Revision 1.1  2004/01/06 00:34:57  southa
 * MushPie testing
 *
 */

#include "TestMushPieStandard.h"

class TestMushPiePieces
{
public:
    static MushPiePosicity TestPosMake(Mushware::tVal inKey);
    static MushcoreScalar TestPieces(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
