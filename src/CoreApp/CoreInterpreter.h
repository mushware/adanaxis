/*
 * $Id: CoreInterpreter.h,v 1.3 2002/03/07 22:24:33 southa Exp $
 * $Log: CoreInterpreter.h,v $
 * Revision 1.3  2002/03/07 22:24:33  southa
 * Command interpreter working
 *
 * Revision 1.2  2002/03/05 22:44:46  southa
 * Changes to command handling
 *
 * Revision 1.1  2002/03/02 12:08:23  southa
 * First stage rework of command handler
 * Added core target
 *
 */

#include "CoreStandard.h"
#include "CoreScalar.h"
#include "CoreEnv.h"
#include "CoreCommand.h"
#include "CoreCommandHandler.h"

class CoreInterpreter
{
public:
    virtual ~CoreInterpreter() {}

    static CoreInterpreter& Instance(void) {return *((m_instance==NULL)?m_instance=new CoreInterpreter:m_instance);}
    
    virtual CoreScalar Execute(CoreCommand& ioCommand);
    virtual void AddHandler(const string& inName, CoreCommandHandler inHandler);
    
private:
    CoreEnv m_env;
    map<string, CoreCommandHandler> m_handlers;
    static CoreInterpreter *m_instance;
};
