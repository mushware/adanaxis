/*
 * $Id: GameDefServer.cpp,v 1.1 2002/11/24 23:54:36 southa Exp $
 * $Log: GameDefServer.cpp,v $
 * Revision 1.1  2002/11/24 23:54:36  southa
 * Initial send of objects over links
 *
 */

#include "GameDefServer.h"

#include "GameAppHandler.h"
#include "GameDefClient.h"
#include "GameProtocol.h"

#include "mushPlatform.h"

GameDefServer::GameDefServer()
{
}

void
GameDefServer::HostGame(const string& inContract, U32 inPlayerLimit)
{
    m_contractName = inContract;
    m_playerLimit = inPlayerLimit;
}

void
GameDefServer::Ticker(void)
{
}

void
GameDefServer::WebPrint(ostream& ioOut) const
{
    ioOut << "<table width=\"100%\" class=\"bglightred\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\">" << endl;
    ioOut << "<tr>";
    ioOut << "<td class=\"bgred\"><font class=\"bold\">Contract Name</font></td>";
    ioOut << "<td class=\"bgred\"><font class=\"bold\">Player Limit</font></td>";
    ioOut << "<td class=\"bgred\"><font class=\"bold\">Status</font></td>";
    ioOut << "</tr><tr>";
    ioOut << "<td>" << MediaNetUtils::MakeWebSafe(m_contractName) << "</td>";
    ioOut << "<td>" << m_playerLimit << "</td>";
    ioOut << "<td><font class=\"bggreen\">" << "GO" << "</font></td>";
    ioOut << "</tr><tr>";
    ioOut << "<td class=\"bgred\"><font class=\"bold\">Player</font></td>";
    ioOut << "<td class=\"bgred\"><font class=\"bold\">Address</font></td>";
    ioOut << "<td class=\"bgred\"><font class=\"bold\">Status</font></td>";
    ioOut << "</tr>";

    CoreData<GameDef>::tMapIterator endValue = CoreData<GameDef>::Instance().End();

    for (CoreData<GameDef>::tMapIterator p = CoreData<GameDef>::Instance().Begin();  p != endValue; ++p)
    {
        GameDefClient *defClient;
        defClient = dynamic_cast<GameDefClient *>(p->second);
        if (defClient != NULL)
        {
            ioOut << "<tr>";
            ioOut << "<td>" << MediaNetUtils::MakeWebSafe(p->first) << "</td>";
            ioOut << "<td></td>";
            ioOut << "<td><font class=\"bggreen\">" << "GO" << "</font></td>";
            ioOut << "</tr>";
        }
    }
    
    ioOut << "</table>" << endl;
}

void
GameDefServer::NullHandler(CoreXML& inXML)
{
}

void
GameDefServer::HandleDefServerEnd(CoreXML& inXML)
{
    inXML.StopHandler();
}

void
GameDefServer::Pickle(ostream& inOut, const string& inPrefix="") const
{
GameDef::Pickle(inOut, inPrefix);
    inOut << inPrefix << "<!-- Incomplete -->" << endl;
}

void
GameDefServer::Unpickle(CoreXML& inXML)
{
GameDef::UnpicklePrologue();
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_endTable[kPickleData]["defserver"] = &GameDefServer::HandleDefServerEnd;
    m_pickleState=kPickleData;
    inXML.ParseStream(*this);
}

void
GameDefServer::XMLStartHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        if (m_pickleState == kPickleData)
        {
GameDef::XMLStartHandler(inXML);
            m_pickleState=kPickleWithinBase;
            ++m_baseThreaded;
        }
        else
        {
            ostringstream message;
            message << "Unexpected tag <" << inXML.TopTag() << "> in DefServer.  Potential matches are";
ElementFunctionMap::iterator p = m_startTable[m_pickleState].begin();
            while (p != m_startTable[m_pickleState].end())
            {
                message << " <" << p->first << ">";
                p++;
            }
            inXML.Throw(message.str());
        }
    }
}

void
GameDefServer::XMLEndHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        if (m_pickleState == kPickleWithinBase)
        {
GameDef::XMLEndHandler(inXML);
            --m_baseThreaded;
            if (m_baseThreaded == 0)
            {
                m_pickleState=kPickleData;
            }
        }
        else
        {
            ostringstream message;
            message << "Unexpected end of tag </" << inXML.TopTag() << "> in DefServer.  Potential matches are";
ElementFunctionMap::iterator p = m_endTable[m_pickleState].begin();
            while (p != m_endTable[m_pickleState].end())
            {
                message << " <" << p->first << ">";
                p++;
            }
            inXML.Throw(message.str());
        }
    }
}

void
GameDefServer::XMLDataHandler(CoreXML& inXML)
{
}

char *
GameDefServer::TypeNameGet(void) const
{
    return "gamedefserver";
}

