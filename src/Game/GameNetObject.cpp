/*
 * $Id: GameNetObject.cpp,v 1.11 2002/12/09 23:59:58 southa Exp $
 * $Log: GameNetObject.cpp,v $
 * Revision 1.11  2002/12/09 23:59:58  southa
 * Network control
 *
 * Revision 1.10  2002/12/05 23:52:51  southa
 * Network management and status
 *
 * Revision 1.9  2002/12/05 13:20:12  southa
 * Client link handling
 *
 * Revision 1.8  2002/12/04 12:54:41  southa
 * Network control work
 *
 * Revision 1.7  2002/11/28 15:33:31  southa
 * Pass GameDef status over link
 *
 * Revision 1.5  2002/11/28 11:10:29  southa
 * Client and server delete messages
 *
 * Revision 1.4  2002/11/27 16:35:09  southa
 * Client and server image handling
 *
 * Revision 1.3  2002/11/27 13:23:26  southa
 * Server and client data exchange
 *
 * Revision 1.2  2002/11/25 18:02:57  southa
 * Mushware ID work
 *
 * Revision 1.1  2002/11/25 15:44:02  southa
 * CreateObject message decoding
 *
 */

#include "GameNetObject.h"

#include "GameDefClient.h"
#include "GameDefServer.h"

#include "mushMedia.h"

GameNetObject::~GameNetObject()
{
}

void
GameNetObject::NullHandler(CoreXML& inXML)
{
}

void
GameNetObject::HandleGameDefClientStart(CoreXML& inXML)
{
    string elementName=inXML.GetAttribOrThrow("name").StringGet();
    string dataName = elementName+"-image";

    CoreScalar netDelete(0);
    inXML.GetAttrib(netDelete, "delete");
    if (netDelete.U32Get())
    {
        try
        {
            CoreData<GameDefClient>::Instance().Delete(dataName);
        }
        catch (ReferenceFail& e)
        {
            MustlLog::Instance().NetLog() << "Delete gamedefclient failed: " << e.what() << endl;
        }
    }
    else
    {
        bool isUpdate = CoreData<GameDefClient>::Instance().Exists(dataName);
        GameDefClient *gameDefClient = CoreData<GameDefClient>::Instance().Give(dataName, new GameDefClient(elementName));
        gameDefClient->ImageIsSet(true);
        gameDefClient->PlayerNameSet(dataName);
        gameDefClient->AddressSet(m_address);
        gameDefClient->Unpickle(inXML);

        // When a client image is created, we send an update of the server image to that client
        if (!isUpdate)
        {
            CoreData<GameDefServer>::tMapIterator endValue = CoreData<GameDefServer>::Instance().End();
            for (CoreData<GameDefServer>::tMapIterator p = CoreData<GameDefServer>::Instance().Begin(); p != endValue; ++p)
            {
                if (!p->second->ImageIs())
                {
                    p->second->UpdateClient(*gameDefClient);
                }
            }
        }
    }
}

void
GameNetObject::HandleGameDefServerStart(CoreXML& inXML)
{
    string elementName=inXML.GetAttribOrThrow("name").StringGet();
    string dataName = elementName+"-image";

    CoreScalar netDelete(0);
    inXML.GetAttrib(netDelete, "delete");
    if (netDelete.U32Get())
    {
        try
        {
            CoreData<GameDefServer>::Instance().Delete(dataName);
        }
        catch (ReferenceFail& e)
        {
            MustlLog::Instance().NetLog() << "Delete gamedefserver failed: " << e.what() << endl;
        }
    }
    else
    {
        GameDefServer *gameDefServer = CoreData<GameDefServer>::Instance().Give(dataName, new GameDefServer(elementName));
        gameDefServer->ImageIsSet(true);
        gameDefServer->AddressSet(m_address);
        gameDefServer->Unpickle(inXML);

        // When a server image is created or updated, we can't update the client images
        // on that server without causing a loop, but the update on status change will
        // do the job for us
    }
}

void
GameNetObject::HandleNetObjectStart(CoreXML& inXML)
{
    inXML.Throw("Not expecting a <netobject> element");
}

void
GameNetObject::HandleNetObjectEnd(CoreXML& inXML)
{
    inXML.Throw("Not expecting expect a </netobject> element");
    inXML.StopHandler();
}

void
GameNetObject::Pickle(ostream& inOut, const string& inPrefix="") const
{
    inOut << inPrefix << "<!-- Cannot pickle GameNetObject -->" << endl;
}

void
GameNetObject::Unpickle(CoreXML& inXML)
{
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleInit]["netobject"] = &GameNetObject::HandleNetObjectStart;
    m_endTable[kPickleData]["netobject"] = &GameNetObject::HandleNetObjectEnd;
    m_startTable[kPickleData]["gamedefclient"] = &GameNetObject::HandleGameDefClientStart;
    m_endTable[kPickleData]["gamedefclient"] = &GameNetObject::NullHandler;
    m_startTable[kPickleData]["gamedefserver"] = &GameNetObject::HandleGameDefServerStart;
    m_endTable[kPickleData]["gamedefserver"] = &GameNetObject::NullHandler;
    m_pickleState=kPickleData;
    inXML.ParseStream(*this);
}

void
GameNetObject::XMLStartHandler(CoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected tag <" << inXML.TopTag() << ">.  Potential matches are";
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
GameNetObject::XMLEndHandler(CoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected end of tag </" << inXML.TopTag() << ">.  Potential matches are";
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
GameNetObject::XMLDataHandler(CoreXML& inXML)
{
}

char *
GameNetObject::TypeNameGet(void) const
{
    return "gamenetobject";
}
