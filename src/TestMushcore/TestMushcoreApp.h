#ifndef TESTMUSHCOREAPP_H
#define TESTMUSHCOREAPP_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: TestMushcoreApp.h,v 1.2 2003/01/20 17:03:22 southa Exp $
 * $Log: TestMushcoreApp.h,v $
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
#endif
