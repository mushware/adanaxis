//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameDef.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } FC0XzCJUBCEncI1eI1ibSA
/*
 * $Id: GameDef.cpp,v 1.23 2003/08/21 23:08:42 southa Exp $
 * $Log: GameDef.cpp,v $
 * Revision 1.23  2003/08/21 23:08:42  southa
 * Fixed file headers
 *
 * Revision 1.22  2003/01/20 10:45:25  southa
 * Singleton tidying
 *
 * Revision 1.21  2003/01/13 14:31:57  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.20  2003/01/09 14:57:01  southa
 * Created Mushcore
 *
 * Revision 1.19  2003/01/07 17:13:41  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.18  2002/12/29 20:59:54  southa
 * More build fixes
 *
 * Revision 1.17  2002/12/20 13:17:38  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.16  2002/12/13 01:07:25  southa
 * Mustl work
 *
 * Revision 1.15  2002/12/12 14:00:39  southa
 * Created Mustl
 *
 * Revision 1.14  2002/12/05 13:20:12  southa
 * Client link handling
 *
 * Revision 1.13  2002/11/28 15:33:31  southa
 * Pass GameDef status over link
 *
 * Revision 1.12  2002/11/28 15:14:13  southa
 * Multiplayer setup timing
 *
 * Revision 1.11  2002/11/28 12:05:45  southa
 * Server name work
 *
 * Revision 1.10  2002/11/28 11:10:29  southa
 * Client and server delete messages
 *
 * Revision 1.9  2002/11/27 16:35:09  southa
 * Client and server image handling
 *
 * Revision 1.8  2002/11/27 13:23:26  southa
 * Server and client data exchange
 *
 * Revision 1.7  2002/11/24 23:54:36  southa
 * Initial send of objects over links
 *
 * Revision 1.6  2002/11/24 23:18:16  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.4  2002/11/23 17:23:44  southa
 * Sleep in setup
 *
 * Revision 1.3  2002/11/23 15:23:33  southa
 * Fixed network orders for win32
 *
 * Revision 1.2  2002/11/22 11:42:06  southa
 * Added developer controls
 *
 * Revision 1.1  2002/11/21 18:06:17  southa
 * Non-blocking network connection
 *
 */

#include "GameDef.h"

#include "GameAppHandler.h"
#include "GameProtocol.h"
#include "GameSTL.h"

#include "Mustl.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

GameDef::GameDef(const string& inName) :
    m_name(inName),
    m_status(kStatusInvalid),
    m_isImage(false)
{
    m_creationMsec = dynamic_cast<GLAppHandler &>(MushcoreAppHandler::Sgl()).MillisecondsGet();
}

const string
GameDef::StatusWebStringGet(void) const
{
    switch (m_status)
    {
        case kStatusInvalid:
        default:
            return "<font class=\"bgred\">INVALID</font>";

        case kStatusTesting:
            return "<font class=\"bgyellow\">TESTING</font>";
            
        case kStatusOK:
            return "<font class=\"bggreen\">OK</font>";

        case kStatusNoServer:
            return "<font class=\"bgred\">NO SERVER</font>";
    }
}

void
GameDef::HandleNameEnd(MushcoreXML& inXML)
{
    m_name = inXML.TopData();
}

void
GameDef::HandleStatusEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for status.  Should be <status>3</status>";
    U32 value;
    if (!(data >> value)) inXML.Throw(failMessage);
    m_status = static_cast<tStatus>(value);
}

void
GameDef::NullHandler(MushcoreXML& inXML)
{
}

void
GameDef::Pickle(ostream& inOut, const string& inPrefix) const
{
    inOut << inPrefix << "<name>" << MustlUtils::MakeXMLSafe(m_name) << "</name>" << endl;
    inOut << inPrefix << "<status>" << m_status << "</status>" << endl;
}

void
GameDef::UnpicklePrologue(void)
{
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleData]["name"] = &GameDef::NullHandler;
    m_endTable[kPickleData]["name"] = &GameDef::HandleNameEnd;
    m_startTable[kPickleData]["status"] = &GameDef::NullHandler;
    m_endTable[kPickleData]["status"] = &GameDef::HandleStatusEnd;
    m_pickleState=kPickleData;
}

void
GameDef::UnpickleEpilogue(void)
{
    m_startTable.clear();
    m_endTable.clear();
}

void
GameDef::Unpickle(MushcoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
}

void
GameDef::XMLStartHandler(MushcoreXML& inXML)
{
ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected tag <" << inXML.TopTag() << "> in Def.  Potential matches are";
ElementFunctionMap::iterator p = m_startTable[m_pickleState].begin();
        while (p != m_startTable[m_pickleState].end())
        {
            message << " <" << p->first << ">";
            p++;
        }
        inXML.Throw(message.str());
    }
}

void
GameDef::XMLEndHandler(MushcoreXML& inXML)
{
ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected end of tag </" << inXML.TopTag() << "> in Def.  Potential matches are";
ElementFunctionMap::iterator p = m_endTable[m_pickleState].begin();
        while (p != m_endTable[m_pickleState].end())
        {
            message << " <" << p->first << ">";
            p++;
        }
        inXML.Throw(message.str());
    }
}

void
GameDef::XMLDataHandler(MushcoreXML& inXML)
{
}

