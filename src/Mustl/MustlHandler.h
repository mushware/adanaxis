#ifndef MUSTLHANDLER_H
#define MUSTLHANDLER_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MustlHandler.h,v 1.2 2002/12/17 12:53:33 southa Exp $
 * $Log: MustlHandler.h,v $
 * Revision 1.2  2002/12/17 12:53:33  southa
 * Mustl library
 *
 * Revision 1.1  2002/12/12 14:00:25  southa
 * Created Mustl
 *
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

#include "MustlStandard.h"

class MustlData;
class MustlLink;

class MustlHandler
{
public:
    virtual void MessageHandle(MustlData& ioData, MustlLink& inLink, Mustl::U32 inType) = 0;
};
#endif
