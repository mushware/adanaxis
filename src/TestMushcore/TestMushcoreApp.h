//%includeGuardStart {
#ifndef TESTMUSHCOREAPP_H
#define TESTMUSHCOREAPP_H
//%includeGuardStart } 3PYZsxPqo6UJme/us+rKDg
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreApp.h
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
//%Header } q6csMjfkW5ucWnDGc0sh8w
/*
 * $Id: TestMushcoreApp.h,v 1.6 2005/05/19 13:02:24 southa Exp $
 * $Log: TestMushcoreApp.h,v $
 * Revision 1.6  2005/05/19 13:02:24  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/02 21:13:17  southa
 * Source conditioning
 *
 * Revision 1.4  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:36  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/20 17:03:22  southa
 * Command line expression evaluator enhancements
 *
 * Revision 1.1  2003/01/20 15:38:28  southa
 * Created MushcoreTest
 *
 */

#include "TestMushcoreStandard.h"

class TestMushcoreApp : public MushcoreSingleton<TestMushcoreApp>
{
public:
    TestMushcoreApp();
    ~TestMushcoreApp();
    
    void EnterInstance(void);
    void RunTest(const std::string& inCommandStr, const std::string& inNameStr);
    static void Enter(void);
    static bool MagicTest(void);
    static void FailureAdd(const std::string& inStr);
    static void PassAdd(const std::string& inStr);
    static void FailuresPrint(void);
    
private:
    enum
    {
        kMagic = 0x65927466
    };

    typedef std::vector<std::string> tFails;

    Mushware::U32 m_dynamicMagic;

    static Mushware::U32 m_staticMagic;
    static Mushware::U32 m_passCount;
    static tFails m_fails;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
