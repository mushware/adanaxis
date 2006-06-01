//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameRouter.cpp
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Hs4BQXuOUjn+PSzRpLSLMg
/*
 * $Id: GameRouter.cpp,v 1.32 2005/05/19 13:02:03 southa Exp $
 * $Log: GameRouter.cpp,v $
 * Revision 1.32  2005/05/19 13:02:03  southa
 * Mac release work
 *
 * Revision 1.31  2005/03/13 00:34:46  southa
 * Build fixes, key support and stereo
 *
 * Revision 1.30  2004/01/02 21:13:07  southa
 * Source conditioning
 *
 * Revision 1.29  2003/10/06 23:06:31  southa
 * Include fixes
 *
 * Revision 1.28  2003/10/06 22:23:44  southa
 * Game to GameMustl move
 *
 * Revision 1.27  2003/10/04 15:32:09  southa
 * Module split
 *
 * Revision 1.26  2003/10/04 12:44:34  southa
 * File renaming
 *
 * Revision 1.25  2003/10/04 12:23:02  southa
 * File renaming
 *
 * Revision 1.24  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.23  2003/08/21 23:08:53  southa
 * Fixed file headers
 *
 * Revision 1.22  2003/01/20 10:45:27  southa
 * Singleton tidying
 *
 * Revision 1.21  2003/01/18 13:33:57  southa
 * Created MushcoreSingleton
 *
 * Revision 1.20  2003/01/17 13:30:39  southa
 * Source conditioning and build fixes
 *
 * Revision 1.19  2003/01/13 14:32:00  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.18  2003/01/12 17:32:56  southa
 * Mushcore work
 *
 * Revision 1.17  2003/01/09 14:57:03  southa
 * Created Mushcore
 *
 * Revision 1.16  2002/12/29 20:59:57  southa
 * More build fixes
 *
 * Revision 1.15  2002/12/20 13:17:42  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.14  2002/12/14 15:04:33  southa
 * Mustl fixes
 *
 * Revision 1.13  2002/12/13 01:07:25  southa
 * Mustl work
 *
 * Revision 1.12  2002/12/12 14:00:40  southa
 * Created Mustl
 *
 * Revision 1.11  2002/12/09 23:59:59  southa
 * Network control
 *
 * Revision 1.10  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 * Revision 1.9  2002/12/05 13:20:12  southa
 * Client link handling
 *
 * Revision 1.8  2002/12/04 15:39:58  southa
 * Multiplayer work
 *
 * Revision 1.7  2002/12/04 00:37:11  southa
 * ControlFrameDef work
 *
 * Revision 1.6  2002/11/28 11:10:29  southa
 * Client and server delete messages
 *
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

#include "GameProtocol.h"
#include "GameSTL.h"

#ifdef MUSHWARE_USE_MUSTL
#include "mushMustlGame.h"
#endif

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(GameRouter);

void
GameRouter::MessageHandle(MustlData& ioData, MustlLink& inLink, U32 inType)
{
#ifdef MUSHWARE_USE_MUSTL
    switch (inType)
    {
        case GameProtocol::kMessageTypeIDTransfer:
            IDTransferHandle(ioData, inLink);
            break;
            
        case GameProtocol::kMessageTypeCreateObject:
        case GameProtocol::kMessageTypeDeleteObject:
            NetObjectHandle(ioData, inLink);
            break;

        default:
            MustlLog::Sgl().NetLog() << "Unrecognised message type (" << inType << ")" << endl;
            break;
    }
#endif
}

void
GameRouter::IDTransferHandle(MustlData& ioData, MustlLink& inLink)
{
#ifdef MUSHWARE_USE_MUSTL

    MustlGameID netID(ioData);

    // We add the -image suffix if the target of this link is a client.  Not rigourous
    if (!inLink.TargetServerIs())
    {
        netID.NameSuffixAdd("-image");
    }
    inLink.NetIDSet(netID);
#endif
}

void
GameRouter::NetObjectHandle(MustlData& ioData, const MustlLink& inLink)
{
#ifdef MUSHWARE_USE_MUSTL
    MustlGameObject netObject;

    netObject.AddressSet(inLink.TCPAddressGet());
    
    string dataStr(reinterpret_cast<char *>(ioData.MessagePtrGet()), ioData.MessageSizeGet());
    istringstream data(dataStr);
    MushcoreXML xml(data, "network");
    try
    {
        netObject.Unpickle(xml);
    }
    catch (MushcoreSyntaxFail& e)
    {
        throw(MustlFail(e.what()));
    }
#endif
}


/************************************************************************************

Network calculations
--------------------

Basic critereon
---------------

Server must support a 4 player game, with one player on the server machine, using a 56k modem and 500ms ping time

uplink 33kbps   3300 bytes/s
downlink 50kbps 5000 bytes/s

UDP header 20 bytes, ignoring PPP headers, etc.

Uplink
------

Limit is the server's ability to receive 3 control streams.  Gives us 1100 bytes/s per station.  Using all bytes for headers, packet rate = 55 Hz.

Desired packet rate = 20Hz

Available payload = 35 bytes

Ample for a control spec.

Format
------

S16 motion frame number where this data ends
U8 number of frames/key bitmaps
S16 mouseDeltaX at end
S16 mouseDeltaY at end
U8[x] x frames of key bitmaps

Downlink
--------

Limit is the server's ability to send three snapshot streams.  Available stream are 1666 bytes/s per station.

Packet rate = 20Hz

Available payload = 63 bytes

We need one MotionSpec per object, plus object create/delete and collision events.

MotionSpec is
Bytes------max--min
position    8    4
angle       2    1
deltapos    4    2
deltaangle  2    1
-------------------
total      16    6

Object creation
Bytes------max--min
ID          2    1
frame       2    2
type        1    1
MotionSpec 16    6
------------------
total      21   10

Collision/destruction
Bytes------max--min
ID          2    1
ID2         2    1
frame       2    2
------------------
total       6    4

Conclusions:

1.  Compressed MotionSpecs will be useful
2.  Packet headers are significant so messages must be aggregated

************************************************************************************/
