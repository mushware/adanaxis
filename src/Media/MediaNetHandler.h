#ifndef MEDIANETHANDLER_H
#define MEDIANETHANDLER_H
/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class MediaNetData;

class MediaNetHandler
{
public:
    virtual void MessageHandle(MediaNetData& ioData, U32 inType) = 0;
};
#endif
