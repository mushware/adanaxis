/*
 * $Id: MediaNetProtocol.cpp,v 1.9 2002/11/25 12:06:18 southa Exp $
 * $Log: MediaNetProtocol.cpp,v $
 * Revision 1.9  2002/11/25 12:06:18  southa
 * Received net message routing
 *
 * Revision 1.8  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.7  2002/11/22 11:42:06  southa
 * Added developer controls
 *
 * Revision 1.6  2002/11/04 19:34:47  southa
 * Network link maintenance
 *
 * Revision 1.5  2002/11/04 15:50:32  southa
 * Network log
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

/************************************
 *
 * Protocol details
 *
 * [0] sync byte 'S'
 * [1] sync byte 'y'
 * [2] message type
 * [3] length MSB (optional)
 * [4] length LSB (optional)
 *
 ************************************/

#include "MediaNetProtocol.h"
#include "MediaNetData.h"
#include "MediaNetLog.h"
#include "MediaNetUtils.h"

void
MediaNetProtocol::TCPLinkCheckCreate(MediaNetData& outData, U32 inSequenceNumber)
{
    outData.BytePush(kSyncByte1);
    outData.BytePush(kSyncByte2);
    outData.BytePush(kMessageTypeTCPLinkCheck);
    outData.BytePush(static_cast<U8>(inSequenceNumber & 0xff));
}

void
MediaNetProtocol::TCPLinkCheckReplyCreate(MediaNetData& outData, U32 inSequenceNumber)
{
    outData.BytePush(kSyncByte1);
    outData.BytePush(kSyncByte2);
    outData.BytePush(kMessageTypeTCPLinkCheckReply);
    outData.BytePush(static_cast<U8>(inSequenceNumber & 0xff));
}

void
MediaNetProtocol::UDPLinkCheckCreate(MediaNetData& outData, U32 inSequenceNumber)
{
    outData.BytePush(kSyncByte1);
    outData.BytePush(kSyncByte2);
    outData.BytePush(kMessageTypeUDPLinkCheck);
    outData.BytePush(static_cast<U8>(inSequenceNumber & 0xff));
}

void
MediaNetProtocol::UDPLinkCheckReplyCreate(MediaNetData& outData, U32 inSequenceNumber)
{
    outData.BytePush(kSyncByte1);
    outData.BytePush(kSyncByte2);
    outData.BytePush(kMessageTypeUDPLinkCheckReply);
    outData.BytePush(static_cast<U8>(inSequenceNumber & 0xff));
}

void
MediaNetProtocol::KillLinkCreate(MediaNetData& outData, tReasonCode inReason)
{
    outData.BytePush(kSyncByte1);
    outData.BytePush(kSyncByte2);
    outData.BytePush(kMessageTypeKillLink);
    outData.BytePush(static_cast<U8>(inReason & 0xff));
}

void
MediaNetProtocol::Unpack(MediaNetData& ioData)
{
    U32 messageLength=0; // Content length after the message type (and length)
    string skippedStr; // For error log
    
    U32 unpackState=ioData.UnpackStateGet();
    if (unpackState==0) unpackState=kUnpackStateSync1;

    while (unpackState != kUnpackStateMessageDone && !ioData.IsEmptyForRead())
    {
        U8 byte=ioData.BytePop();
        switch (static_cast<tUnpackUnpackState>(unpackState))
        {
            case kUnpackStateSync1:
                if (byte == kSyncByte1)
                {
                    unpackState=kUnpackStateSync2;
                }
                else
                {
                    skippedStr += byte;
                }
                break;

            case kUnpackStateSync2:
                if (byte == kSyncByte2)
                {
                    unpackState=kUnpackStateMessageType;
                    // Leave messagePos pointing at the message type
                    ioData.MessagePosSet(ioData.ReadPosGet());
                }
                else
                {
                    unpackState = kUnpackStateSync1;
                    skippedStr += kSyncByte1;
                    skippedStr += byte;
                }
                break;

            case kUnpackStateMessageType:
                if (byte >= kMessageTypeMinLinkLayer && byte < kMessageTypeMaxLinkLayer)
                {
                    messageLength=1;
                    unpackState=kUnpackStateMessageDone;
                }
                else
                {
                    unpackState=kUnpackStateLengthMSB;
                }
                break;

            case kUnpackStateLengthMSB:
                messageLength=byte << 8;
                unpackState=kUnpackStateLengthLSB;
                break;

            case kUnpackStateLengthLSB:
                messageLength |= byte;

                // Remove the header size from messageLength, leaving the size of the content
                if (messageLength < 5)
                {
                    MediaNetLog::Instance().NetLog() << "Bad length in application protocol message (" << messageLength << ")" << endl;
                    unpackState = kUnpackStateSync1;
                    
                }
                else
                {
                    messageLength -= 5;
                    unpackState=kUnpackStateMessageDone;
                }
                break;

            case kUnpackStateMessageDone:
                // I think not
                COREASSERT(false);
                break;

            case kUnpackStateMessageReady:
                throw(LogicFail("Caller of Unpack failed to handle returned message"));

            case kUnpackStateInvalid:
            // default:
                COREASSERT(false);
                unpackState=kUnpackStateSync1;
                break;
        }
    }
    if (unpackState == kUnpackStateMessageDone)
    {
        if (ioData.ReadSizeGet() >= messageLength)
        {
            // Set readPos to byte beyond last byte of message
            ioData.ReadPosAdd(messageLength);
            unpackState=kUnpackStateMessageReady;
        }
        // else come round in kUnpackStateMessageDone next time when more data has been added
    }
    ioData.UnpackStateSet(unpackState);

    // Error logging
    if (skippedStr.size() > 0)
    {
        MediaNetLog::Instance().NetLog() << "NetProtocol skipped '" << MediaNetUtils::MakePrintable(skippedStr) << "'" << endl;
    }
}

void
MediaNetProtocol::RemoveLength(MediaNetData& ioData, U32 inType)
{
    if (inType >= kMessageTypeLongAppStart && inType < kMessageTypeLongAppEnd)
    {
        ioData.MessagePosSet(ioData.MessagePosGet() + 2);
    }
    else if (inType >= kMessageTypeShortAppStart && inType < kMessageTypeShortAppEnd)
    {
        ioData.MessagePosSet(ioData.MessagePosGet() + 1);
    }
    else
    {
        MediaNetLog::Instance().NetLog() << "RemoveLength called on message type without length (" << inType << ")" << endl;
    }
}

U32
MediaNetProtocol::LinkToAppType(U32 inType)
{
    U32 retType;
    if (inType >= kMessageTypeLongAppStart && inType < kMessageTypeLongAppEnd)
    {
        retType = inType - kMessageTypeLongAppStart;
    }
    else if (inType >= kMessageTypeShortAppStart && inType < kMessageTypeShortAppEnd)
    {
        retType = inType - kMessageTypeShortAppStart;
    }
    else
    {
        MediaNetLog::Instance().NetLog() << "LinkToAppType called non-app message (" << inType << ")" << endl;
        retType=0;
    }
    return retType;
}

bool
MediaNetProtocol::MessageTake(MediaNetData& ioData)
{
    if (ioData.UnpackStateGet() != kUnpackStateMessageReady)
    {
        return false;
    }
    ioData.UnpackStateSet(kUnpackStateSync1);
    return true;
}

bool
MediaNetProtocol::MessageTypeIsLinkLayer(U32 inType)
{
    return inType < kMessageTypeMaxLinkLayer;
}

void
MediaNetProtocol::LongAppMessageHeaderCreate(MediaNetData& ioData, U32 inType)
{
    U32 messageType=kMessageTypeLongAppStart+inType;
    COREASSERT(messageType < kMessageTypeLongAppEnd);
    ioData.BytePush(kSyncByte1);
    ioData.BytePush(kSyncByte2);
    ioData.BytePush(messageType);
    ioData.LengthPosSet(ioData.WritePosGet());
    ioData.BytePush(0); // Length byte MSB
    ioData.BytePush(0); // Length byte LSB    
}

void
MediaNetProtocol::LongAppMessageFinish(MediaNetData& ioData)
{
    U32 size=ioData.ReadSizeGet();
    ioData.LengthBytePush(size >> 8);
    ioData.LengthBytePush(size);
}

void
MediaNetProtocol::LongAppMessageCreate(MediaNetData& ioData, U32 inType, const string& inStr)
{
    LongAppMessageHeaderCreate(ioData, inType);
    ioData.Write(inStr);
    LongAppMessageFinish(ioData);
}
