#ifndef COREINTERPRETER_H
#define COREINTERPRETER_H
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
 * $Id: CoreInterpreter.h,v 1.5 2002/08/07 13:36:45 southa Exp $
 * $Log: CoreInterpreter.h,v $
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
    map<string, CoreCommandHandler> m_handlers;
    static CoreInterpreter *m_instance;
};
#endif
