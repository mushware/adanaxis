#ifndef TESTMUSTLAPP_H
#define TESTMUSTLAPP_H
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
 * $Id: TestMustlApp.h,v 1.1 2003/01/13 23:05:22 southa Exp $
 * $Log: TestMustlApp.h,v $
 * Revision 1.1  2003/01/13 23:05:22  southa
 * Mustl test application
 *
 */

#include "TestMustlStandard.h"

class TestMustlApp
{
public:
    void Enter(void);
    void DoQuit(void);

    static inline TestMustlApp& Instance(void);

private:
    bool m_doQuit;

    static std::auto_ptr<TestMustlApp> m_instance;
};

inline TestMustlApp&
TestMustlApp::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new TestMustlApp);
    return *m_instance;
}

#endif
