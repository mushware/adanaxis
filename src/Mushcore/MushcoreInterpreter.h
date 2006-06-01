//%includeGuardStart {
#ifndef MUSHCOREINTERPRETER_H
#define MUSHCOREINTERPRETER_H
//%includeGuardStart } 90pIiLoZqlqvg4bg4lEe2A
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreInterpreter.h
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } aHzDwz9sg5ITyhdoxgz5KQ
/*
 * $Id: MushcoreInterpreter.h,v 1.14 2005/07/29 08:27:47 southa Exp $
 * $Log: MushcoreInterpreter.h,v $
 * Revision 1.14  2005/07/29 08:27:47  southa
 * Collision work
 *
 * Revision 1.13  2005/05/19 13:02:15  southa
 * Mac release work
 *
 * Revision 1.12  2004/01/05 14:27:41  southa
 * MushPie work and build fixes
 *
 * Revision 1.11  2004/01/02 21:13:13  southa
 * Source conditioning
 *
 * Revision 1.10  2003/10/04 12:23:08  southa
 * File renaming
 *
 * Revision 1.9  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:09:14  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.6  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
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
 * InfernalData and loadtilemap command
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
#include "MushcoreSingleton.h"

class MushcoreCommand;
class MushcoreEnv;
class MushcoreScalar;

class MushcoreInterpreter : public MushcoreSingleton<MushcoreInterpreter>
{
public:
    typedef void (*tLogFunction)(const std::string& inStr);
    
    MushcoreInterpreter();
    virtual ~MushcoreInterpreter() {}

    virtual void Execute(const std::string& inStr);
    
    virtual MushcoreScalar Despatch(MushcoreCommand& ioCommand);
    virtual void HandlerAdd(const std::string& inName, MushcoreCommandHandler inHandler);
    
    virtual void CommandsGet(std::vector<std::string>& outVec, const std::string& inStr) const;
    
    void LogFunctionSet(tLogFunction inFunction) { m_logFunction = inFunction; }

    static void NullFunction(void);
    
private:
    typedef std::map<std::string, MushcoreCommandHandler> tHandlerMap;
    
    tHandlerMap m_handlers;
    tLogFunction m_logFunction;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
