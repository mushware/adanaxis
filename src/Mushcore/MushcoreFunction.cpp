//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreFunction.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } b0jRAjjwmEtJhEBbtl067w
/*
 * $Id: MushcoreFunction.cpp,v 1.8 2003/09/17 19:40:35 southa Exp $
 * $Log: MushcoreFunction.cpp,v $
 * Revision 1.8  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:09:12  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
 * Revision 1.5  2003/01/18 13:33:58  southa
 * Created MushcoreSingleton
 *
 * Revision 1.4  2003/01/13 14:32:02  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.3  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 * Revision 1.2  2003/01/11 17:07:53  southa
 * Mushcore library separation
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.13  2002/12/29 20:59:51  southa
 * More build fixes
 *
 * Revision 1.12  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.11  2002/11/17 13:38:30  southa
 * Game selection
 *
 * Revision 1.10  2002/10/22 20:41:58  southa
 * Source conditioning
 *
 * Revision 1.9  2002/09/07 09:54:01  southa
 * Tweaks to Mandrake RPM
 *
 * Revision 1.8  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.6  2002/07/16 17:48:07  southa
 * Collision and optimisation work
 *
 * Revision 1.4  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/29 08:56:16  southa
 * Tile display
 *
 * Revision 1.1  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 */

#include "MushcoreFunction.h"

#include "MushcoreFail.h"
#include "MushcoreInterpreter.h"
#include "MushcoreScalar.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

void
MushcoreFunction::ThrowErrorExecute(void) const
{
    for (U32 i=0; i<m_commands.size(); ++i)
    {
        MushcoreInterpreter::Sgl().Execute(m_commands[i]);
    }
}

void
MushcoreFunction::CoalesceErrorsExecute(void) const
{
    string failStr;
    for (U32 i=0; i<m_commands.size(); ++i)
    {
        try
        {
            MushcoreInterpreter::Sgl().Execute(m_commands[i]);
        }
        catch (MushcoreNonFatalFail& e)
        {
            failStr += ": ";
            failStr += e.what();
        }
    }
    if (failStr != "")
    {
        throw(MushcoreCommandFail("Command(s) failed"+failStr));
    }
}

void
MushcoreFunction::Print(ostream& inOut) const
{
    for (U32 i=0; i<m_commands.size(); ++i)
    {
        inOut << m_commands[i] << endl;
    }
}
