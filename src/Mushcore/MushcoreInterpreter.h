//%includeGuardStart {
#ifndef MUSHCOREINTERPRETER_H
#define MUSHCOREINTERPRETER_H
//%includeGuardStart } 90pIiLoZqlqvg4bg4lEe2A
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreInterpreter.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } qSY8E6inHvmVUDQoYRaMmg
/*
 * $Id: MushcoreInterpreter.h,v 1.15 2006/06/01 15:39:45 southa Exp $
 * $Log: MushcoreInterpreter.h,v $
 * Revision 1.15  2006/06/01 15:39:45  southa
 * DrawArray verification and fixes
 *
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
