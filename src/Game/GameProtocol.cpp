/*
 * $Id: GameProtocol.cpp,v 1.6 2002/11/28 11:10:29 southa Exp $
 * $Log: GameProtocol.cpp,v $
 * Revision 1.6  2002/11/28 11:10:29  southa
 * Client and server delete messages
 *
 * Revision 1.5  2002/11/25 15:44:03  southa
 * CreateObject message decoding
 *
 * Revision 1.4  2002/11/25 12:06:18  southa
 * Received net message routing
 *
 * Revision 1.3  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.2  2002/11/24 23:54:36  southa
 * Initial send of objects over links
 *
 * Revision 1.1  2002/11/24 23:18:24  southa
 * Added type name accessor to CorePickle
 *
 */

#include "GameProtocol.h"

#include "mushMedia.h"

void
GameProtocol::CreateObjectCreate(MediaNetData& ioData, CorePickle& inObj, const string& inRemoteName)
{
    ostringstream netStream;

    netStream << "<" << inObj.TypeNameGet() << " name=\"" << inRemoteName << "\">";
    inObj.Pickle(netStream);
    netStream << "</" << inObj.TypeNameGet() << ">";
    MediaNetProtocol::LongAppMessageCreate(ioData, kMessageTypeCreateObject, netStream.str());
    // MediaNetLog::Instance().NetLog() << "Sent " << ioData << endl; 
}

void
GameProtocol::DeleteObjectCreate(MediaNetData& ioData, CorePickle& inObj, const string& inRemoteName)
{
    ostringstream netStream;

    netStream << "<" << inObj.TypeNameGet() << " name=\"" << inRemoteName << "\" delete=\"1\">";
    netStream << "</" << inObj.TypeNameGet() << ">";
    MediaNetProtocol::LongAppMessageCreate(ioData, kMessageTypeDeleteObject, netStream.str());
    // MediaNetLog::Instance().NetLog() << "Sent " << ioData << endl;
}

void
GameProtocol::ControlDataCreate(MediaNetData& ioData, const GameControlDataMessage& inSpec)
{
    MediaNetProtocol::LongAppMessageHeaderCreate(ioData, kMessageTypeControlData);
    ioData.PrepareForWrite();
    ioData.BytePush(inSpec.endFrame >> 8);
    ioData.BytePush(inSpec.endFrame);
    U32 size = inSpec.frameDefs.size();
    COREASSERT(size <= 32);
    if (size > 32) size = 32;
    ioData.BytePush(size);
    for (U32 i=0; i<size; ++i)
    {
        ioData.BytePush(inSpec.frameDefs[i].mouseDeltaX);
        ioData.BytePush(inSpec.frameDefs[i].mouseDeltaY);
        ioData.BytePush(inSpec.frameDefs[i].keyState);
    }
    MediaNetProtocol::LongAppMessageFinish(ioData);
}
