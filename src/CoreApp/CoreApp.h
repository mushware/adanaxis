/*
 * $Id: CoreApp.h,v 1.1 2002/05/10 16:39:37 southa Exp $
 * $Log: CoreApp.h,v $
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
#include "ChildRecord.h"
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
    list<ChildRecord> m_children;
};

    