/*
 * $Id: GameRouter.cpp,v 1.5 2002/11/27 16:35:09 southa Exp $
 * $Log: GameRouter.cpp,v $
 * Revision 1.5  2002/11/27 16:35:09  southa
 * Client and server image handling
 *
 * Revision 1.4  2002/11/27 13:23:26  southa
 * Server and client data exchange
 *
 * Revision 1.3  2002/11/25 15:44:03  southa
 * CreateObject message decoding
 *
 * Revision 1.2  2002/11/25 12:06:18  southa
 * Received net message routing
 *
 * Revision 1.1  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 */

#include "GameRouter.h"

#include "GameNetObject.h"

auto_ptr<GameRouter> GameRouter::m_instance;

void
GameRouter::MessageHandle(MediaNetData& ioData, const MediaNetLink& inLink, U32 inType)
{
    NetObjectHandle(ioData, inLink);
}

void
GameRouter::NetObjectHandle(MediaNetData& ioData, const MediaNetLink& inLink)
{
    GameNetObject netObject;

    netObject.AddressSet(inLink.TCPTargetAddressGet());
    
    string dataStr(reinterpret_cast<char *>(ioData.MessagePtrGet()), ioData.MessageSizeGet());
    istringstream data(dataStr);
    CoreXML xml(data, "network");
    try
    {
        netObject.Unpickle(xml);
    }
    catch (XMLFail& e)
    {
        throw(NetworkFail(e.what()));
    }
}
