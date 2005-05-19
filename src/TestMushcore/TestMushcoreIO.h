//%includeGuardStart {
#ifndef TESTMUSHCOREIO_H
#define TESTMUSHCOREIO_H
//%includeGuardStart } 8NR/SClt8A407tgBZheUAQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreIO.h
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
//%Header } SCz03GM+7LLdAUNVC95pVg
/*
 * $Id: TestMushcoreIO.h,v 1.3 2004/01/02 21:13:17 southa Exp $
 * $Log: TestMushcoreIO.h,v $
 * Revision 1.3  2004/01/02 21:13:17  southa
 * Source conditioning
 *
 * Revision 1.2  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.1  2003/09/17 19:10:17  southa
 * Created
 *
 */

#include "TestMushcoreStandard.h"

class TestMushcoreIO
{
public:
    static MushcoreScalar TestIO(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
