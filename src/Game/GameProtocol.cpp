/*
 * $Id$
 * $Log$
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
    inLink.ReliableSend(netData);
}
