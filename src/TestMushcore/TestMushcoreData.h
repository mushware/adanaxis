//%includeGuardStart {
#ifndef TESTMUSHCOREDATA_H
#define TESTMUSHCOREDATA_H
//%includeGuardStart } 2PEny8VIu3csw/GGzPaTZQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreData.h
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
//%Header } GOZri6BjwzrB53IdiQZ3Lg
/*
 * $Id: TestMushcoreData.h,v 1.2 2006/06/01 15:40:04 southa Exp $
 * $Log: TestMushcoreData.h,v $
 * Revision 1.2  2006/06/01 15:40:04  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/06/13 14:25:46  southa
 * Pipe and ordered data work
 *
 */

#include "TestMushcoreStandard.h"

class TestMushcoreData
{
public:
    static MushcoreScalar TestData(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
