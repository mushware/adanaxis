/*
 * $Id: GameDef.cpp,v 1.11 2002/11/28 12:05:45 southa Exp $
 * $Log: GameDef.cpp,v $
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
 * Added type name accessor to CorePickle
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

#include "mushPlatform.h"

GameDef::GameDef(const string& inName) :
    m_name(inName),
    m_status(kStatusTesting),
    m_isImage(false)
{
    m_creationMsec = dynamic_cast<GLAppHandler &>(CoreAppHandler::Instance()).MillisecondsGet();
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
GameDef::CreateNewLink(const MediaNetAddress& inAddress) const
{
    try
    {
        CoreData<MediaNetLink>::Instance().DataGive(MediaNetLink::NextLinkNameTake(), new MediaNetLink(inAddress));
    }
    catch (NetworkFail& e)
    {
        MediaNetLog::Instance().NetLog() << "Link creation failed: " << e.what() << endl;
    }
}

void
GameDef::HandleNameEnd(CoreXML& inXML)
{
    m_name = inXML.TopData();
}

void
GameDef::NullHandler(CoreXML& inXML)
{
}

void
GameDef::Pickle(ostream& inOut, const string& inPrefix="") const
{
    inOut << inPrefix << "<name>" << MediaNetUtils::MakeXMLSafe(m_name) << "</name>" << endl;
}

void
GameDef::UnpicklePrologue(void)
{
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleData]["name"] = &GameDef::NullHandler;
    m_endTable[kPickleData]["name"] = &GameDef::HandleNameEnd;
    m_pickleState=kPickleData;
}

void
GameDef::UnpickleEpilogue(void)
{
    m_startTable.clear();
    m_endTable.clear();
}

void
GameDef::Unpickle(CoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
}

void
GameDef::XMLStartHandler(CoreXML& inXML)
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
GameDef::XMLEndHandler(CoreXML& inXML)
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
GameDef::XMLDataHandler(CoreXML& inXML)
{
}

