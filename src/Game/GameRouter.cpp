/*
 * $Id: GameRouter.cpp,v 1.2 2002/11/25 12:06:18 southa Exp $
 * $Log: GameRouter.cpp,v $
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
GameRouter::MessageHandle(MediaNetData& ioData, U32 inType)
{
    CreateObjectHandle(ioData);
}

void
GameRouter::CreateObjectHandle(MediaNetData& ioData)
{
    GameNetObject netObject;

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
