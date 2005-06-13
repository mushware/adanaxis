//%includeGuardStart {
#ifndef TESTMUSHCORECOUNTER_H
#define TESTMUSHCORECOUNTER_H
//%includeGuardStart } Ri6Sd6FAxTULZy0XBqE/Uw
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreCounter.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } c+kkiNz4qO+XRi5oHm5Ztg
/*
 * $Id$
 * $Log$
 */

#include "TestMushcoreStandard.h"

class TestMushcoreCounter
{
public:
    TestMushcoreCounter() : m_pCount(NULL) {}
    TestMushcoreCounter(Mushware::U32& inCount) : m_pCount(&inCount) { ++*m_pCount; }
    ~TestMushcoreCounter() { if (m_pCount != NULL) --*m_pCount; }
    
private:
    Mushware::U32 *m_pCount;
};


//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
