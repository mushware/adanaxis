#ifndef TESTMUSHCOREAPP_H
#define TESTMUSHCOREAPP_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id$
 * $Log$
 */

#include "TestMushcoreStandard.h"

class TestMushcoreApp : public MushcoreSingleton<TestMushcoreApp>
{
public:
    TestMushcoreApp();
    ~TestMushcoreApp();
    
    void EnterInstance(void);
    void RunTest(const string& inCommandStr, const string& inNameStr);
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
