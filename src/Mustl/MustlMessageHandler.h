#ifndef MUSTLMESSAGEHANDLER_H
#define MUSTLMESSAGEHANDLER_H
#ifndef MUSTLHANDLER_H
#define MUSTLHANDLER_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: MustlMessageHandler.h,v 1.2 2003/01/18 13:33:59 southa Exp $
 * $Log: MustlMessageHandler.h,v $
 * Revision 1.2  2003/01/18 13:33:59  southa
 * Created MushcoreSingleton
 *
 * Revision 1.1  2003/01/17 13:30:41  southa
 * Source conditioning and build fixes
 *
 * Revision 1.3  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
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

class MustlMessageHandler
{
public:
    virtual void MessageHandle(MustlData& ioData, MustlLink& inLink, Mustl::U32 inType) = 0;
};
#endif
#endif
