//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlProtocol.cpp
 *
 * Copyright Andy Southgate 2002-2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } /MTXazxpDUyvgMmelFOO8g
/*
 * $Id: MustlProtocol.cpp,v 1.7 2003/08/21 23:09:29 southa Exp $
 * $Log: MustlProtocol.cpp,v $
 * Revision 1.7  2003/08/21 23:09:29  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/01/20 10:45:30  southa
 * Singleton tidying
 *
 * Revision 1.5  2002/12/29 20:59:59  southa
 * More build fixes
 *
 * Revision 1.4  2002/12/20 13:17:46  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/12/17 12:53:34  southa
 * Mustl library
 *
 * Revision 1.2  2002/12/12 18:38:25  southa
 * Mustl separation
 *
 * Revision 1.1  2002/12/12 14:00:26  southa
 * Created Mustl
 *
 * Revision 1.12  2002/12/09 16:18:01  southa
 * Link ID transfer
 *
 * Revision 1.11  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 * Revision 1.10  2002/12/05 13:20:13  southa
 * Client link handling
 *
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

#include "MustlProtocol.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

using namespace Mustl;
using namespace std;

void
MustlProtocol::TCPLinkCheckCreate(MustlData& outData, U32 inSequenceNumber)
{
    outData.BytePush(kSyncByte1);
    outData.BytePush(kSyncByte2);
    outData.BytePush(kMessageTypeTCPLinkCheck);
    outData.BytePush(static_cast<U8>(inSequenceNumber & 0xff));
}

void
MustlProtocol::TCPLinkCheckReplyCreate(MustlData& outData, U32 inSequenceNumber)
{
    outData.BytePush(kSyncByte1);
    outData.BytePush(kSyncByte2);
    outData.BytePush(kMessageTypeTCPLinkCheckReply);
    outData.BytePush(static_cast<U8>(inSequenceNumber & 0xff));
}

void
MustlProtocol::UDPLinkCheckCreate(MustlData& outData, U32 inSequenceNumber)
{
    outData.BytePush(kSyncByte1);
    outData.BytePush(kSyncByte2);
    outData.BytePush(kMessageTypeUDPLinkCheck);
    outData.BytePush(static_cast<U8>(inSequenceNumber & 0xff));
}

void
MustlProtocol::UDPLinkCheckReplyCreate(MustlData& outData, U32 inSequenceNumber)
{
    outData.BytePush(kSyncByte1);
    outData.BytePush(kSyncByte2);
    outData.BytePush(kMessageTypeUDPLinkCheckReply);
    outData.BytePush(static_cast<U8>(inSequenceNumber & 0xff));
}

void
MustlProtocol::KillLinkCreate(MustlData& outData, tReasonCode inReason)
{
    outData.BytePush(kSyncByte1);
    outData.BytePush(kSyncByte2);
    outData.BytePush(kMessageTypeKillLink);
    outData.BytePush(static_cast<U8>(inReason & 0xff));
}

void
MustlProtocol::IDRequestCreate(MustlData& outData)
{
    outData.BytePush(kSyncByte1);
    outData.BytePush(kSyncByte2);
    outData.BytePush(kMessageTypeIDRequest);
    outData.BytePush(0); // Pad to 4 bytes
}

void
MustlProtocol::IDTransferCreate(MustlData& ioData, const MustlID& inID)
{
    LongAppMessageHeaderCreate(ioData, kMessageTypeIDTransfer - kMessageTypeLongAppStart);
    inID.Pack(ioData);
    LongAppMessageFinish(ioData);
}

void
MustlProtocol::Unpack(MustlData& ioData)
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
                if (byte >= kMessageTypeMinLinkLayer && byte < kMessageTypeMaxFixedLength)
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
                    MustlLog::Sgl().NetLog() << "Bad length in application protocol message (" << messageLength << ")" << endl;
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
                MUSTLASSERT(false);
                break;

            case kUnpackStateMessageReady:
                throw(MustlFail("Caller of Unpack failed to handle returned message"));

            case kUnpackStateInvalid:
            // default:
                MUSTLASSERT(false);
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
        MustlLog::Sgl().NetLog() << "NetProtocol skipped '" << MustlUtils::MakePrintable(skippedStr) << "'" << endl;
    }
}

void
MustlProtocol::RemoveLength(MustlData& ioData, U32 inType)
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
        MustlLog::Sgl().NetLog() << "RemoveLength called on message type without length (" << inType << ")" << endl;
    }
}

U32
MustlProtocol::LinkToAppType(U32 inType)
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
        MustlLog::Sgl().NetLog() << "LinkToAppType called non-app message (" << inType << ")" << endl;
        retType=0;
    }
    return retType;
}

bool
MustlProtocol::MessageTake(MustlData& ioData)
{
    if (ioData.UnpackStateGet() != kUnpackStateMessageReady)
    {
        return false;
    }
    ioData.UnpackStateSet(kUnpackStateSync1);
    return true;
}

bool
MustlProtocol::MessageTypeIsLinkLayer(U32 inType)
{
    return inType < kMessageTypeMaxLinkLayer;
}

void
MustlProtocol::LongAppMessageHeaderCreate(MustlData& ioData, U32 inType)
{
    U32 messageType=kMessageTypeLongAppStart + inType;
    MUSTLASSERT(messageType < kMessageTypeLongAppEnd);
    ioData.BytePush(kSyncByte1);
    ioData.BytePush(kSyncByte2);
    ioData.BytePush(messageType);
    ioData.LengthPosSet(ioData.WritePosGet());
    ioData.BytePush(0); // Length byte MSB
    ioData.BytePush(0); // Length byte LSB    
}

void
MustlProtocol::LongAppMessageFinish(MustlData& ioData)
{
    U32 size=ioData.ReadSizeGet();
    ioData.LengthBytePush(size >> 8);
    ioData.LengthBytePush(size);
}

void
MustlProtocol::LongAppMessageCreate(MustlData& ioData, U32 inType, const string& inStr)
{
    LongAppMessageHeaderCreate(ioData, inType);
    ioData.Write(inStr);
    LongAppMessageFinish(ioData);
}
