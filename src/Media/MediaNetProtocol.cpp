/*
 * $Id: MediaNetProtocol.cpp,v 1.2 2002/11/03 20:10:00 southa Exp $
 * $Log: MediaNetProtocol.cpp,v $
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

void
MediaNetProtocol::LinkCheckCreate(MediaNetData& outData, U32 inSequenceNumber)
{
    outData.BytePush(kSyncByte1);
    outData.BytePush(kSyncByte2);
    outData.BytePush(kMessageTypeLinkCheck);
    outData.BytePush(static_cast<U8>(inSequenceNumber & 0xff));
}

void
MediaNetProtocol::LinkCheckReplyCreate(MediaNetData& outData, U32 inSequenceNumber)
{
    outData.BytePush(kSyncByte1);
    outData.BytePush(kSyncByte2);
    outData.BytePush(kMessageTypeLinkCheckReply);
    outData.BytePush(static_cast<U8>(inSequenceNumber & 0xff));
}

void
MediaNetProtocol::Unpack(MediaNetData& ioData)
{
    U32 messageLength=0; // Content length after the message type (and length)
    
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
                    cerr << "Skipped '" << byte << "'" << endl;
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
                    cerr << "Skipped '" << byte << "'" << endl;
                }
                break;

            case kUnpackStateMessageType:
                if (byte == kMessageTypeLinkCheck ||
                    byte == kMessageTypeLinkCheckReply)
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
                COREASSERT(false);
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
    return inType == kMessageTypeLinkCheck ||
           inType == kMessageTypeLinkCheckReply;
}
