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
 * $Id: MushcoreCommand.cpp,v 1.4 2003/01/20 10:45:29 southa Exp $
 * $Log: MushcoreCommand.cpp,v $
 * Revision 1.4  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
 * Revision 1.3  2003/01/12 17:32:58  southa
 * Mushcore work
 *
 * Revision 1.2  2003/01/11 17:07:53  southa
 * Mushcore library separation
 *
 * Revision 1.1  2003/01/09 14:57:06  southa
 * Created Mushcore
 *
 * Revision 1.17  2002/12/29 20:59:51  southa
 * More build fixes
 *
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

#include "MushcoreCommand.h"
#include "MushcoreEnv.h"
#include "MushcoreFail.h"
#include "MushcoreFlex.h"
#include "MushcoreInterpreter.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

void
MushcoreCommand::Execute(void)
{
    Execute(MushcoreEnv::Sgl());
}

void
MushcoreCommand::Execute(MushcoreEnv& ioEnv)
{
    if (m_bison.Parse(*this))
    {
        throw(MushcoreCommandFail("Syntax error in '" + m_string + "'"));
    }
}

string
MushcoreCommand::AllParams(void)
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
MushcoreCommand::PopString(void)
{
    string retStr;
    m_paramList.PopParam(retStr);
    return retStr;
}

tVal
MushcoreCommand::PopVal(void)
{
    tVal retVal;
    m_paramList.PopParam(retVal);
    return retVal;
}

MushcoreScalar
MushcoreCommand::Despatch(void)
{
    return MushcoreInterpreter::Sgl().Despatch(*this);
}
