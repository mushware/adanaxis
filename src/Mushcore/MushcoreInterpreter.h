#ifndef MUSHCOREINTERPRETER_H
#define MUSHCOREINTERPRETER_H
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
 * $Id: MushcoreInterpreter.h,v 1.5 2003/01/17 00:41:03 southa Exp $
 * $Log: MushcoreInterpreter.h,v $
 * Revision 1.5  2003/01/17 00:41:03  southa
 * Configuration updates from POST data
 *
 * Revision 1.4  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.3  2003/01/11 17:07:53  southa
 * Mushcore library separation
 *
 * Revision 1.2  2003/01/11 13:03:17  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.10  2002/12/29 20:30:51  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.9  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
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

#include "MushcoreStandard.h"

#include "MushcoreCommandHandler.h"

class MushcoreCommand;
class MushcoreEnv;
class MushcoreScalar;

class MushcoreInterpreter
{
public:
    typedef void (*tLogFunction)(const std::string& inStr);
    
    MushcoreInterpreter();
    virtual ~MushcoreInterpreter() {}

    static MushcoreInterpreter& Sgl(void) {return *((m_instance==NULL)?m_instance=new MushcoreInterpreter:m_instance);}

    virtual void Execute(const std::string& inStr);
    
    virtual MushcoreScalar Despatch(MushcoreCommand& ioCommand);
    virtual void AddHandler(const std::string& inName, MushcoreCommandHandler inHandler);

    void LogFunctionSet(tLogFunction inFunction) { m_logFunction = inFunction; }

    static void NullFunction(void);
    
private:
    typedef std::map<std::string, MushcoreCommandHandler> tHandlerMap;
    
    tHandlerMap m_handlers;
    tLogFunction m_logFunction;
    
    static MushcoreInterpreter *m_instance;
};
#endif
