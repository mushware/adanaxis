/*
 * $Id: MediaNetProtocol.h,v 1.1 2002/11/03 18:43:09 southa Exp $
 * $Log: MediaNetProtocol.h,v $
 * Revision 1.1  2002/11/03 18:43:09  southa
 * Network fixes
 *
 */

#include "mushCore.h"

class MediaNetData;

class MediaNetProtocol
{
public:
    static void LinkCheckCreate(MediaNetData& outData, U32 inSequenceNumber);

    static void Unpack(MediaNetData& ioData);
    static bool MessageToHandle(const MediaNetData& ioData);
    static void MessageHandledSet(MediaNetData& ioData);
    
private:
    enum
    {
        kSyncByte1='S',
        kSyncByte2='y'
    };
    
    enum tMessageType
    {
        kMessageTypeInvalid,
        kMessageTypeLinkCheck='A',
        kMessageTypeLinkCheckReply
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


