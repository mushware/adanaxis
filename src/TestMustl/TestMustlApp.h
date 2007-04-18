//%includeGuardStart {
#ifndef TESTMUSTLAPP_H
#define TESTMUSTLAPP_H
//%includeGuardStart } HhndmeRttYciWz9uO77Pcg
//%Header {
/*****************************************************************************
 *
 * File: src/TestMustl/TestMustlApp.h
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
//%Header } B7ljUnaD78KIJ4ha1mTJMg
/*
 * $Id: TestMustlApp.h,v 1.11 2006/06/01 15:40:06 southa Exp $
 * $Log: TestMustlApp.h,v $
 * Revision 1.11  2006/06/01 15:40:06  southa
 * DrawArray verification and fixes
 *
 * Revision 1.10  2005/05/19 13:02:25  southa
 * Mac release work
 *
 * Revision 1.9  2004/09/26 20:43:19  southa
 * TestMustl fixes
 *
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
