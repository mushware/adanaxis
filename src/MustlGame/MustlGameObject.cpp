//%Header {
/*****************************************************************************
 *
 * File: src/Game/MustlGameObject.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } OeLT2lA5iuGBxjdqvKr/ZQ
/*
 * $Id: MustlGameObject.cpp,v 1.21 2003/09/17 19:40:32 southa Exp $
 * $Log: MustlGameObject.cpp,v $
 * Revision 1.21  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.20  2003/08/21 23:08:50  southa
 * Fixed file headers
 *
 * Revision 1.19  2003/01/20 10:45:26  southa
 * Singleton tidying
 *
 * Revision 1.18  2003/01/13 14:31:59  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.17  2003/01/12 17:32:55  southa
 * Mushcore work
 *
 * Revision 1.16  2003/01/09 14:57:02  southa
 * Created Mushcore
 *
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
 * Pass MustlGameBase status over link
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

#include "MustlGameObject.h"

#include "MustlGameClient.h"
#include "MustlGameServer.h"
#include "GameSTL.h"

#include "mushMedia.h"

using namespace Mushware;
using namespace std;

MustlGameObject::~MustlGameObject()
{
}

void
MustlGameObject::NullHandler(MushcoreXML& inXML)
{
}

void
MustlGameObject::HandleGameDefClientStart(MushcoreXML& inXML)
{
    string elementName=inXML.GetAttribOrThrow("name").StringGet();
    string dataName = elementName+"-image";

    MushcoreScalar netDelete(0);
    inXML.GetAttrib(netDelete, "delete");
    if (netDelete.U32Get())
    {
        try
        {
            MushcoreData<MustlGameClient>::Sgl().Delete(dataName);
        }
        catch (MushcoreReferenceFail& e)
        {
            MustlLog::Sgl().NetLog() << "Delete gamedefclient failed: " << e.what() << endl;
        }
    }
    else
    {
        bool isUpdate = MushcoreData<MustlGameClient>::Sgl().Exists(dataName);
        MustlGameClient *gameDefClient = MushcoreData<MustlGameClient>::Sgl().Give(dataName, new MustlGameClient(elementName));
        gameDefClient->ImageIsSet(true);
        gameDefClient->PlayerNameSet(dataName);
        gameDefClient->AddressSet(m_address);
        gameDefClient->Unpickle(inXML);

        // When a client image is created, we send an update of the server image to that client
        if (!isUpdate)
        {
            MushcoreData<MustlGameServer>::tMapIterator endValue = MushcoreData<MustlGameServer>::Sgl().End();
            for (MushcoreData<MustlGameServer>::tMapIterator p = MushcoreData<MustlGameServer>::Sgl().Begin(); p != endValue; ++p)
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
MustlGameObject::HandleGameDefServerStart(MushcoreXML& inXML)
{
    string elementName=inXML.GetAttribOrThrow("name").StringGet();
    string dataName = elementName+"-image";

    MushcoreScalar netDelete(0);
    inXML.GetAttrib(netDelete, "delete");
    if (netDelete.U32Get())
    {
        try
        {
            MushcoreData<MustlGameServer>::Sgl().Delete(dataName);
        }
        catch (MushcoreReferenceFail& e)
        {
            MustlLog::Sgl().NetLog() << "Delete gamedefserver failed: " << e.what() << endl;
        }
    }
    else
    {
        MustlGameServer *gameDefServer = MushcoreData<MustlGameServer>::Sgl().Give(dataName, new MustlGameServer(elementName));
        gameDefServer->ImageIsSet(true);
        gameDefServer->AddressSet(m_address);
        gameDefServer->Unpickle(inXML);

        // When a server image is created or updated, we can't update the client images
        // on that server without causing a loop, but the update on status change will
        // do the job for us
    }
}

void
MustlGameObject::HandleNetObjectStart(MushcoreXML& inXML)
{
    inXML.Throw("Not expecting a <netobject> element");
}

void
MustlGameObject::HandleNetObjectEnd(MushcoreXML& inXML)
{
    inXML.Throw("Not expecting expect a </netobject> element");
    inXML.StopHandler();
}

void
MustlGameObject::Pickle(ostream& inOut, const string& inPrefix) const
{
    inOut << inPrefix << "<!-- Cannot pickle MustlGameObject -->" << endl;
}

void
MustlGameObject::Unpickle(MushcoreXML& inXML)
{
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleInit]["netobject"] = &MustlGameObject::HandleNetObjectStart;
    m_endTable[kPickleData]["netobject"] = &MustlGameObject::HandleNetObjectEnd;
    m_startTable[kPickleData]["gamedefclient"] = &MustlGameObject::HandleGameDefClientStart;
    m_endTable[kPickleData]["gamedefclient"] = &MustlGameObject::NullHandler;
    m_startTable[kPickleData]["gamedefserver"] = &MustlGameObject::HandleGameDefServerStart;
    m_endTable[kPickleData]["gamedefserver"] = &MustlGameObject::NullHandler;
    m_pickleState=kPickleData;
    inXML.ParseStream(*this);
}

void
MustlGameObject::XMLStartHandler(MushcoreXML& inXML)
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
MustlGameObject::XMLEndHandler(MushcoreXML& inXML)
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
MustlGameObject::XMLDataHandler(MushcoreXML& inXML)
{
}

char *
MustlGameObject::TypeNameGet(void) const
{
    return "gamenetobject";
}
