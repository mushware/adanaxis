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
 * $Id: GameNetObject.cpp,v 1.15 2003/01/07 17:13:43 southa Exp $
 * $Log: GameNetObject.cpp,v $
 * Revision 1.15  2003/01/07 17:13:43  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.14  2002/12/29 20:59:56  southa
 * More build fixes
 *
 * Revision 1.13  2002/12/20 13:17:41  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.12  2002/12/12 14:00:39  southa
 * Created Mustl
 *
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

using namespace Mushware;
using namespace std;

GameNetObject::~GameNetObject()
{
}

void
GameNetObject::NullHandler(MushcoreXML& inXML)
{
}

void
GameNetObject::HandleGameDefClientStart(MushcoreXML& inXML)
{
    string elementName=inXML.GetAttribOrThrow("name").StringGet();
    string dataName = elementName+"-image";

    MushcoreScalar netDelete(0);
    inXML.GetAttrib(netDelete, "delete");
    if (netDelete.U32Get())
    {
        try
        {
            MushcoreData<GameDefClient>::Instance().Delete(dataName);
        }
        catch (ReferenceFail& e)
        {
            MustlLog::Instance().NetLog() << "Delete gamedefclient failed: " << e.what() << endl;
        }
    }
    else
    {
        bool isUpdate = MushcoreData<GameDefClient>::Instance().Exists(dataName);
        GameDefClient *gameDefClient = MushcoreData<GameDefClient>::Instance().Give(dataName, new GameDefClient(elementName));
        gameDefClient->ImageIsSet(true);
        gameDefClient->PlayerNameSet(dataName);
        gameDefClient->AddressSet(m_address);
        gameDefClient->Unpickle(inXML);

        // When a client image is created, we send an update of the server image to that client
        if (!isUpdate)
        {
            MushcoreData<GameDefServer>::tMapIterator endValue = MushcoreData<GameDefServer>::Instance().End();
            for (MushcoreData<GameDefServer>::tMapIterator p = MushcoreData<GameDefServer>::Instance().Begin(); p != endValue; ++p)
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
GameNetObject::HandleGameDefServerStart(MushcoreXML& inXML)
{
    string elementName=inXML.GetAttribOrThrow("name").StringGet();
    string dataName = elementName+"-image";

    MushcoreScalar netDelete(0);
    inXML.GetAttrib(netDelete, "delete");
    if (netDelete.U32Get())
    {
        try
        {
            MushcoreData<GameDefServer>::Instance().Delete(dataName);
        }
        catch (ReferenceFail& e)
        {
            MustlLog::Instance().NetLog() << "Delete gamedefserver failed: " << e.what() << endl;
        }
    }
    else
    {
        GameDefServer *gameDefServer = MushcoreData<GameDefServer>::Instance().Give(dataName, new GameDefServer(elementName));
        gameDefServer->ImageIsSet(true);
        gameDefServer->AddressSet(m_address);
        gameDefServer->Unpickle(inXML);

        // When a server image is created or updated, we can't update the client images
        // on that server without causing a loop, but the update on status change will
        // do the job for us
    }
}

void
GameNetObject::HandleNetObjectStart(MushcoreXML& inXML)
{
    inXML.Throw("Not expecting a <netobject> element");
}

void
GameNetObject::HandleNetObjectEnd(MushcoreXML& inXML)
{
    inXML.Throw("Not expecting expect a </netobject> element");
    inXML.StopHandler();
}

void
GameNetObject::Pickle(ostream& inOut, const string& inPrefix) const
{
    inOut << inPrefix << "<!-- Cannot pickle GameNetObject -->" << endl;
}

void
GameNetObject::Unpickle(MushcoreXML& inXML)
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
GameNetObject::XMLStartHandler(MushcoreXML& inXML)
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
GameNetObject::XMLEndHandler(MushcoreXML& inXML)
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
GameNetObject::XMLDataHandler(MushcoreXML& inXML)
{
}

char *
GameNetObject::TypeNameGet(void) const
{
    return "gamenetobject";
}
