#ifndef MEDIANETPROTOCOL_H
#define MEDIANETPROTOCOL_H
/*
 * $Id: MediaNetProtocol.h,v 1.8 2002/11/27 16:35:10 southa Exp $
 * $Log: MediaNetProtocol.h,v $
 * Revision 1.8  2002/11/27 16:35:10  southa
 * Client and server image handling
 *
 * Revision 1.7  2002/11/25 12:06:18  southa
 * Received net message routing
 *
 * Revision 1.6  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.5  2002/11/04 19:34:47  southa
 * Network link maintenance
 *
 * Revision 1.4  2002/11/04 13:11:58  southa
 * Link setup work
 *
 * Revision 1.3  2002/11/04 01:02:38  southa
 * Link checks
 *
 * Revision 1.2  2002/11/03 20:10:00  southa
 * Initial message unpacking
 *
 * Revision 1.1  2002/11/03 18:43:09  southa
 * Network fixes
 *
 */

#include "mushCore.h"

class MediaNetData;

class MediaNetProtocol
{
public:
    enum tMessageType
    {
        kMessageTypeInvalid,
        kMessageTypeMinLinkLayer='A', // These messages are for the link
        kMessageTypeTCPLinkCheck=kMessageTypeMinLinkLayer,
        kMessageTypeTCPLinkCheckReply,
        kMessageTypeUDPLinkCheck,
        kMessageTypeUDPLinkCheckReply,
        kMessageTypeKillLink,
        kMessageTypeMaxLinkLayer, // Subsequent messages are for the application
        kMessageTypeLongApp,
        kMessageTypeShortApp,
        kMessageTypeNextLayerStart='a'
    };

    enum tReasonCode
    {
        kReasonCodeInvalid,
        kReasonCodeNone=65,
        kReasonCodeDisconnect=66,
        kReasonCodePeerDisconnected=67,
        kReasonCodeTCPLinkCheckFail=68,
        kReasonCodeTCPBadLink=69,
        kReasonCodeUDPLinkCheckFail=70,
        kReasonCodeUDPBadLink=71,
        kReasonCodeIdleTimeout=72,
        kReasonCodeUserDisconnect=73
    };
    
    static void TCPLinkCheckCreate(MediaNetData& outData, U32 inSequenceNumber);
    static void TCPLinkCheckReplyCreate(MediaNetData& outData, U32 inSequenceNumber);
    static void UDPLinkCheckCreate(MediaNetData& outData, U32 inSequenceNumber);
    static void UDPLinkCheckReplyCreate(MediaNetData& outData, U32 inSequenceNumber);
    static void KillLinkCreate(MediaNetData& outData, tReasonCode inReason);

    static void LongAppMessageCreate(MediaNetData& ioData, U32 inType, const string& inStr);
    static void LongAppMessageHeaderCreate(MediaNetData& ioData, U32 inType);
    static void LongAppMessageFinish(MediaNetData& ioData);

    static void Unpack(MediaNetData& ioData);
    static void RemoveLength(MediaNetData& ioData, U32 inType);
    static bool MessageTake(MediaNetData& ioData);
    static bool MessageTypeIsLinkLayer(U32 inType);

    
private:
    enum
    {
        kSyncByte1='S',
        kSyncByte2='y'
    };

    enum tUnpackUnpackState
    {
        kUnpackStateInvalid,
        kUnpackStateSync1,
        kUnpackStateSync2,
        kUnpackStateMessageType,
        kUnpackStateLengthMSB,
        kUnpackStateLengthLSB,
        kUnpackStateMessageDone,
        kUnpackStateMessageReady
    };
};
#endif
