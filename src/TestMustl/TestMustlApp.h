#ifndef TESTMUSTLAPP_H
#define TESTMUSTLAPP_H
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
 * $Id: TestMustlApp.h,v 1.5 2003/01/20 10:45:32 southa Exp $
 * $Log: TestMustlApp.h,v $
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

private:
    bool m_doQuit;
};

#endif
