/*
 * $Id: GameProtocol.cpp,v 1.8 2002/12/06 11:11:16 southa Exp $
 * $Log: GameProtocol.cpp,v $
 * Revision 1.8  2002/12/06 11:11:16  southa
 * Send control information
 *
 * Revision 1.7  2002/12/04 00:37:11  southa
 * ControlFrameDef work
 *
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

