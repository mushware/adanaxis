#ifndef MEDIANETHANDLER_H
#define MEDIANETHANDLER_H
/*
 * $Id: MediaNetHandler.h,v 1.1 2002/11/25 12:06:18 southa Exp $
 * $Log: MediaNetHandler.h,v $
 * Revision 1.1  2002/11/25 12:06:18  southa
 * Received net message routing
 *
 */

#include "mushCore.h"

class MediaNetData;
class MediaNetLink;

class MediaNetHandler
{
public:
    virtual void MessageHandle(MediaNetData& ioData, const MediaNetLink& inLink, U32 inType) = 0;
};
#endif
