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
 * $Id: TestMustlApp.h,v 1.2 2003/01/14 20:46:12 southa Exp $
 * $Log: TestMustlApp.h,v $
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

private:
    bool m_doQuit;
};

#endif
