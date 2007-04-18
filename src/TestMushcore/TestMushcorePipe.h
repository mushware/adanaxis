//%includeGuardStart {
#ifndef TESTMUSHCOREPIPE_H
#define TESTMUSHCOREPIPE_H
//%includeGuardStart } hRmlmpYJpUC4oMxpceS2MA
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcorePipe.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } zbMgaAfg5tG7Oa5Ds3VA5A
/*
 * $Id: TestMushcorePipe.h,v 1.2 2006/06/01 15:40:05 southa Exp $
 * $Log: TestMushcorePipe.h,v $
 * Revision 1.2  2006/06/01 15:40:05  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/06/13 14:25:47  southa
 * Pipe and ordered data work
 *
 */

#include "TestMushcoreStandard.h"

class TestMushcorePipe
{
public:
    static MushcoreScalar TestPipe(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
