/*
 * $Id: GameProtocol.cpp,v 1.1 2002/11/24 23:18:24 southa Exp $
 * $Log: GameProtocol.cpp,v $
 * Revision 1.1  2002/11/24 23:18:24  southa
 * Added type name accessor to CorePickle
 *
 */

#include "GameProtocol.h"

#include "mushMedia.h"

void
GameProtocol::SendObject(MediaNetLink& inLink, CorePickle& inObj, const string& inRemoteName)
{
    ostringstream netStream;

    netStream << "<object name=\"" << inRemoteName << "\" type=\"" << inObj.TypeNameGet() << "\">";
    inObj.Pickle(netStream);
    netStream << "</object>" << endl;
    MediaNetData netData(netStream.str());
    MediaNetLog::Instance().NetLog() << "Sent " << netData << endl; 
    // inLink.ReliableSend(netData);
}
