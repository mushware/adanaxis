/*
 * $Id: GameRouter.cpp,v 1.1 2002/11/25 10:43:28 southa Exp $
 * $Log: GameRouter.cpp,v $
 * Revision 1.1  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 */

#include "GameRouter.h"

auto_ptr<GameRouter> GameRouter::m_instance;

void
GameRouter::MessageHandle(MediaNetData& ioData, U32 inType)
{
    cerr << "Handling message type " << inType << ", data=" << ioData << endl;
}
