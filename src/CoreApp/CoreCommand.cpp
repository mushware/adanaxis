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
 * $Id: CoreCommand.cpp,v 1.16 2002/12/20 13:17:31 southa Exp $
 * $Log: CoreCommand.cpp,v $
 * Revision 1.16  2002/12/20 13:17:31  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.15  2002/11/22 11:42:05  southa
 * Added developer controls
 *
 * Revision 1.14  2002/10/22 20:41:57  southa
 * Source conditioning
 *
 * Revision 1.13  2002/08/27 08:56:16  southa
 * Source conditioning
 *
 * Revision 1.12  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.11  2002/07/06 18:04:15  southa
 * More designer work
 *
 * Revision 1.10  2002/06/27 12:36:03  southa
 * Build process fixes
 *
 * Revision 1.9  2002/05/30 14:41:13  southa
 * GameData and loadtilemap command
 *
 * Revision 1.8  2002/05/28 13:07:03  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.7  2002/05/24 16:23:09  southa
 * Config and typenames
 *
 * Revision 1.6  2002/05/10 16:39:39  southa
 * Changed .hp files to .h
 *
 * Revision 1.5  2002/03/07 22:24:33  southa
 * Command interpreter working
 *
 * Revision 1.4  2002/03/05 22:44:45  southa
 * Changes to command handling
 *
 * Revision 1.3  2002/03/04 22:30:48  southa
 * Interpreter work
 *
 * Revision 1.2  2002/03/02 20:35:07  southa
 * Added flex and bison parser
 *
 * Revision 1.1  2002/03/02 12:08:23  southa
 * First stage rework of command handler
 * Added core target
 *
 */

#include "CoreCommand.h"
#include "CoreEnv.h"
#include "CoreException.h"
#include "CoreFlex.h"
#include "CoreInterpreter.h"

using namespace Mushware;
using namespace std;

void
CoreCommand::Execute(void)
{
    Execute(CoreEnv::Instance());
}

void
CoreCommand::Execute(CoreEnv& ioEnv)
{
    if (m_bison.Parse(*this))
    {
        throw(CommandFail("Syntax error in '" + m_string + "'"));
    }
}

string
CoreCommand::AllParams(void)
{
    string retStr;
    bool first=true;
    while (!m_paramList.Empty())
    {
        if (first)
        {
            first=false;
        }
        else
        {
            retStr.append(" ");
        }
        string str;
        m_paramList.PopParam(str);
        retStr.append(str);
    }
    return retStr;
}

string
CoreCommand::PopString(void)
{
    string retStr;
    m_paramList.PopParam(retStr);
    return retStr;
}

tVal
CoreCommand::PopVal(void)
{
    tVal retVal;
    m_paramList.PopParam(retVal);
    return retVal;
}

CoreScalar
CoreCommand::Despatch(void)
{
    return CoreInterpreter::Instance().Execute(*this);
}
