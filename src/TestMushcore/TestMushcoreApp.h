//%includeGuardStart {
#ifndef TESTMUSHCOREAPP_H
#define TESTMUSHCOREAPP_H
//%includeGuardStart } 3PYZsxPqo6UJme/us+rKDg
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreApp.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 5PNcIwJpEHtqpnkRMXTn9w
/*
 * $Id: TestMushcoreApp.h,v 1.3 2003/08/21 23:09:36 southa Exp $
 * $Log: TestMushcoreApp.h,v $
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
