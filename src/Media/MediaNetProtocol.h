/*
 * $Id: MediaNetProtocol.h,v 1.2 2002/11/03 20:10:00 southa Exp $
 * $Log: MediaNetProtocol.h,v $
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
        kMessageTypeLinkCheck='A',
        kMessageTypeLinkCheckReply
    };
    
    static void LinkCheckCreate(MediaNetData& outData, U32 inSequenceNumber);
    static void LinkCheckReplyCreate(MediaNetData& outData, U32 inSequenceNumber);

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


