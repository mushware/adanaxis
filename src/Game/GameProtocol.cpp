//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameProtocol.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } V1W+V71AhWS6oE4WO+k6wg
/*
 * $Id: GameProtocol.cpp,v 1.17 2003/09/17 19:40:33 southa Exp $
 * $Log: GameProtocol.cpp,v $
 * Revision 1.17  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.16  2003/08/21 23:08:52  southa
 * Fixed file headers
 *
 * Revision 1.15  2003/01/20 10:45:27  southa
 * Singleton tidying
 *
 * Revision 1.14  2003/01/13 14:31:59  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.13  2003/01/09 14:57:03  southa
 * Created Mushcore
 *
 * Revision 1.12  2002/12/29 20:59:56  southa
 * More build fixes
 *
 * Revision 1.11  2002/12/20 13:17:41  southa
 * Namespace changes, licence changes and source conditioning
 *
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
 * Added type name accessor to MushcorePickle
 *
 */

#include "GameProtocol.h"

#include "GameSTL.h"

#include "mushMedia.h"

using namespace Mushware;
using namespace std;

void
GameProtocol::CreateObjectCreate(MustlData& ioData, MushcorePickle& inObj, const string& inRemoteName)
{
    ostringstream netStream;

    netStream << "<" << inObj.TypeNameGet() << " name=\"" << inRemoteName << "\">";
    inObj.Pickle(netStream);
    netStream << "</" << inObj.TypeNameGet() << ">";
    MustlProtocol::LongAppMessageCreate(ioData, kMessageTypeCreateObject, netStream.str());
    // MustlLog::Sgl().NetLog() << "Sent " << ioData << endl; 
}

void
GameProtocol::DeleteObjectCreate(MustlData& ioData, MushcorePickle& inObj, const string& inRemoteName)
{
    ostringstream netStream;

    netStream << "<" << inObj.TypeNameGet() << " name=\"" << inRemoteName << "\" delete=\"1\">";
    netStream << "</" << inObj.TypeNameGet() << ">";
    MustlProtocol::LongAppMessageCreate(ioData, kMessageTypeDeleteObject, netStream.str());
    // MustlLog::Sgl().NetLog() << "Sent " << ioData << endl;
}

