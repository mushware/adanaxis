/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class MediaNetData;

class MediaNetProtocol
{
public:
    static void LinkCheckCreate(MediaNetData& outData, U32 inSequenceNumber);

private:
    enum
    {
        kSyncByte1='S',
        kSyncByte2='y',
        kMessageTypeLinkCheck='A',
    };
};


