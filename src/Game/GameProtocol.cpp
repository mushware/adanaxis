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
 * $Id: GameProtocol.cpp,v 1.10 2002/12/12 14:00:40 southa Exp $
 * $Log: GameProtocol.cpp,v $
 * Revision 1.10  2002/12/12 14:00:40  southa
 * Created Mustl
 *
 * Revision 1.9  2002/12/06 17:38:00  southa
 * ControlData message unpacking
 *
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

using namespace Mushware;

void
GameProtocol::CreateObjectCreate(MustlData& ioData, CorePickle& inObj, const string& inRemoteName)
{
    ostringstream netStream;

    netStream << "<" << inObj.TypeNameGet() << " name=\"" << inRemoteName << "\">";
    inObj.Pickle(netStream);
    netStream << "</" << inObj.TypeNameGet() << ">";
    MustlProtocol::LongAppMessageCreate(ioData, kMessageTypeCreateObject, netStream.str());
    // MustlLog::Instance().NetLog() << "Sent " << ioData << endl; 
}

void
GameProtocol::DeleteObjectCreate(MustlData& ioData, CorePickle& inObj, const string& inRemoteName)
{
    ostringstream netStream;

    netStream << "<" << inObj.TypeNameGet() << " name=\"" << inRemoteName << "\" delete=\"1\">";
    netStream << "</" << inObj.TypeNameGet() << ">";
    MustlProtocol::LongAppMessageCreate(ioData, kMessageTypeDeleteObject, netStream.str());
    // MustlLog::Instance().NetLog() << "Sent " << ioData << endl;
}

