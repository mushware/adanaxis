#ifndef COREINTERPRETER_H
#define COREINTERPRETER_H
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
 * $Id: CoreInterpreter.h,v 1.8 2002/11/22 11:42:06 southa Exp $
 * $Log: CoreInterpreter.h,v $
 * Revision 1.8  2002/11/22 11:42:06  southa
 * Added developer controls
 *
 * Revision 1.7  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/30 14:41:15  southa
 * GameData and loadtilemap command
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
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

#include "CoreCommand.h"
#include "CoreCommandHandler.h"
#include "CoreEnv.h"
#include "CoreScalar.h"
#include "CoreStandard.h"

class CoreInterpreter
{
public:
    CoreInterpreter();
    virtual ~CoreInterpreter() {}

    static CoreInterpreter& Instance(void) {return *((m_instance==NULL)?m_instance=new CoreInterpreter:m_instance);}
    
    virtual CoreScalar Execute(CoreCommand& ioCommand);
    virtual void AddHandler(const string& inName, CoreCommandHandler inHandler);

    void LogCommandsSet(bool inLog) { m_logCommands = inLog; }
    
private:
    std::map<string, CoreCommandHandler> m_handlers;
    bool m_logCommands;
    
    static CoreInterpreter *m_instance;
};
#endif
