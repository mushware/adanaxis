/*
 * $Id$
 * $Log$
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
