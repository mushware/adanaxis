#ifndef MEDIANETPROTOCOL_H
#define MEDIANETPROTOCOL_H
/*
 * $Id: MediaNetProtocol.h,v 1.4 2002/11/04 13:11:58 southa Exp $
 * $Log: MediaNetProtocol.h,v $
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
        kMessageTypeMinLinkLayer='A',
        kMessageTypeTCPLinkCheck=kMessageTypeMinLinkLayer,
        kMessageTypeTCPLinkCheckReply,
        kMessageTypeUDPLinkCheck,
        kMessageTypeUDPLinkCheckReply,
        kMessageTypeKillLink,
        kMessageTypeMaxLinkLayer
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
        kReasonCodeUDPBadLink=71        
    };
    
    static void TCPLinkCheckCreate(MediaNetData& outData, U32 inSequenceNumber);
    static void TCPLinkCheckReplyCreate(MediaNetData& outData, U32 inSequenceNumber);
    static void UDPLinkCheckCreate(MediaNetData& outData, U32 inSequenceNumber);
    static void UDPLinkCheckReplyCreate(MediaNetData& outData, U32 inSequenceNumber);
    static void KillLinkCreate(MediaNetData& outData, tReasonCode inReason);

    static void Unpack(MediaNetData& ioData);
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
        kUnpackStateMessageDone,
        kUnpackStateMessageReady
    };
};
#endif
