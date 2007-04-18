//%includeGuardStart {
#ifndef TESTMUSTLPOSTHANDLER_H
#define TESTMUSTLPOSTHANDLER_H
//%includeGuardStart } SJgpGuH7CQ341wYrg3Yerw
//%Header {
/*****************************************************************************
 *
 * File: src/TestMustl/TestMustlPostHandler.h
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
//%Header } d+axu6zBkUacsUbiiIOpxQ
/*
 * $Id: TestMustlPostHandler.h,v 1.7 2006/06/01 15:40:06 southa Exp $
 * $Log: TestMustlPostHandler.h,v $
 * Revision 1.7  2006/06/01 15:40:06  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/05/19 13:02:25  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/02 21:13:18  southa
 * Source conditioning
 *
 * Revision 1.4  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:39  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/17 13:30:42  southa
 * Source conditioning and build fixes
 *
 * Revision 1.1  2003/01/14 20:46:12  southa
 * Post data handling
 *
 */

#include "TestMustlStandard.h"

class MushcoreCommand;
class MushcoreEnv;
class MushcoreScalar;

class TestMustlPostHandler
{
public:
    static void Install(void);
    static MushcoreScalar PostHandler(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
