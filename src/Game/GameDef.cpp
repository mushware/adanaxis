/*
 * $Id: GameDef.cpp,v 1.6 2002/11/24 23:18:16 southa Exp $
 * $Log: GameDef.cpp,v $
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
#include "GameStationDef.h"

#include "mushPlatform.h"

auto_ptr< CoreData<GameDef> > CoreData<GameDef>::m_instance;

GameDef::GameDef()
{
}

void
GameDef::CreateNewLink(const GameStationDef& inStation)
{
    try
    {
        CoreData<MediaNetLink>::Instance().DataGive(inStation.NameGet()+"client", new MediaNetLink(inStation.NameGet(), inStation.PortGet()));
    }
    catch (NetworkFail& e)
    {
        MediaNetLog::Instance().NetLog() << "Link creation failed: " << e.what() << endl;
    }
}

void
GameDef::HandleDefEnd(CoreXML& inXML)
{
    inXML.StopHandler();
}

void
GameDef::NullHandler(CoreXML& inXML)
{
}

void
GameDef::Pickle(ostream& inOut, const string& inPrefix="") const
{
}

void
GameDef::UnpicklePrologue(void)
{
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_endTable[kPickleData]["def"] = &GameDef::HandleDefEnd;
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

