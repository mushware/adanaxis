//%includeGuardStart {
#ifndef TESTMUSTLAPP_H
#define TESTMUSTLAPP_H
//%includeGuardStart } HhndmeRttYciWz9uO77Pcg
//%Header {
/*****************************************************************************
 *
 * File: src/TestMustl/TestMustlApp.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } cFdhIyJ/clkqVXQ7WA7saQ
/*
 * $Id: TestMustlApp.h,v 1.8 2004/01/02 21:13:18 southa Exp $
 * $Log: TestMustlApp.h,v $
 * Revision 1.8  2004/01/02 21:13:18  southa
 * Source conditioning
 *
 * Revision 1.7  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:09:38  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/01/20 10:45:32  southa
 * Singleton tidying
 *
 * Revision 1.4  2003/01/18 17:05:47  southa
 * Singleton work
 *
 * Revision 1.3  2003/01/18 13:34:00  southa
 * Created MushcoreSingleton
 *
 * Revision 1.2  2003/01/14 20:46:12  southa
 * Post data handling
 *
 * Revision 1.1  2003/01/13 23:05:22  southa
 * Mustl test application
 *
 */

#include "TestMustlStandard.h"

class TestMustlApp : public MushcoreSingleton<TestMustlApp>
{
public:
    void Enter(void);
    void DoQuit(void);
    
    static MushcoreScalar TestMustl(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    
private:
    bool m_doQuit;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
