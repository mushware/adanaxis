/*
 * $Id: MediaNetProtocol.cpp,v 1.5 2002/11/04 15:50:32 southa Exp $
 * $Log: MediaNetProtocol.cpp,v $
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
                MediaNetLog::Instance().Log() << "Protocol error";
                skippedStr += byte;
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
        // else come round in  kUnpackStateMessageDone next time when more data has been added
    }
    ioData.UnpackStateSet(unpackState);

    // Error logging
    if (skippedStr.size() > 0)
    {
        MediaNetLog::Instance().Log() << "NetProtocol skipped '" << MediaNetUtils::MakePrintable(skippedStr) << "'" << endl;
    }
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
