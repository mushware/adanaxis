/*
 * $Id: GameRouter.cpp,v 1.6 2002/11/28 11:10:29 southa Exp $
 * $Log: GameRouter.cpp,v $
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

#include "GameNetObject.h"
#include "GameProtocol.h"

auto_ptr<GameRouter> GameRouter::m_instance;

void
GameRouter::MessageHandle(MediaNetData& ioData, const MediaNetLink& inLink, U32 inType)
{
    switch (inType)
    {
        case GameProtocol::kMessageTypeCreateObject:
        case GameProtocol::kMessageTypeDeleteObject:
            NetObjectHandle(ioData, inLink);
            break;

        case GameProtocol::kMessageTypeControlData:
            ControlDataHandle(ioData, inLink);
            break;

        default:
            MediaNetLog::Instance().NetLog() << "Unrecognised message type (" << inType << ")" << endl;
            break;
    }
}

void
GameRouter::NetObjectHandle(MediaNetData& ioData, const MediaNetLink& inLink)
{
    GameNetObject netObject;

    netObject.AddressSet(inLink.TCPTargetAddressGet());
    
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

void
GameRouter::ControlDataHandle(MediaNetData& ioData, const MediaNetLink& inLink)
{
    // Find object that relates to this control data

    // Apply or store the data

    // Resend object's MotionSpec to the clients as necessary
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
