#ifndef MUSTLHANDLER_H
#define MUSTLHANDLER_H
/*
 * $Id: MustlHandler.h,v 1.3 2002/12/07 18:32:15 southa Exp $
 * $Log: MustlHandler.h,v $
 * Revision 1.3  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 * Revision 1.2  2002/11/27 16:35:09  southa
 * Client and server image handling
 *
 * Revision 1.1  2002/11/25 12:06:18  southa
 * Received net message routing
 *
 */

#include "mushCore.h"

class MustlData;
class MustlLink;

class MustlHandler
{
public:
    virtual void MessageHandle(MustlData& ioData, MustlLink& inLink, U32 inType) = 0;
};
#endif
