#ifndef COREAPP_H
#define COREAPP_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/


/*
 * $Id: CoreApp.h,v 1.4 2002/07/02 14:27:12 southa Exp $
 * $Log: CoreApp.h,v $
 * Revision 1.4  2002/07/02 14:27:12  southa
 * First floor map designer build
 *
 * Revision 1.3  2002/06/27 12:36:02  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/30 14:41:13  southa
 * GameData and loadtilemap command
 *
 * Revision 1.1  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.4  2002/03/07 22:24:32  southa
 * Command interpreter working
 *
 * Revision 1.3  2002/03/05 22:44:45  southa
 * Changes to command handling
 *
 * Revision 1.2  2002/03/02 12:08:23  southa
 * First stage rework of command handler
 * Added core target
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */

#include "CoreStandard.h"
#include "CoreChildRecord.h"
#include "CoreCommandHandler.h"

class CoreApp
{
public:
    
    static CoreApp& Instance(void) {return *((m_instance==NULL)?m_instance=new CoreApp:m_instance);}
    virtual ~CoreApp() {}
    void Process(const string& inStr);
    void AddHandler(const string& inName, CoreCommandHandler inHandler);
    void AddChild(int pid, int inPipe, int outPipe);
    void ServiceChildren(int &outCount);

protected:
    CoreApp() {}
    static CoreApp *m_instance;
    
private:
    list<CoreChildRecord> m_children;
};

    
#endif
