/*
 * $Id: GameProtocol.cpp,v 1.2 2002/11/24 23:54:36 southa Exp $
 * $Log: GameProtocol.cpp,v $
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

    netStream << "<object name=\"" << inRemoteName << "\" type=\"" << inObj.TypeNameGet() << "\">";
    inObj.Pickle(netStream);
    netStream << "</object>" << endl;
    MediaNetData netData;
    MediaNetProtocol::LongAppMessageCreate(netData, kMessageTypeCreateObject, netStream.str());
    MediaNetLog::Instance().NetLog() << "Sent " << netData << endl; 
}
