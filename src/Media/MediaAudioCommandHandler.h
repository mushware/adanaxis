#ifndef MEDIAAUDIOCOMMANDHANDLER_H
#define MEDIAAUDIOCOMMANDHANDLER_H
/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: MediaAudioCommandHandler.h,v 1.6 2002/08/27 08:56:28 southa Exp $
 * $Log: MediaAudioCommandHandler.h,v $
 * Revision 1.6  2002/08/27 08:56:28  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/16 19:46:07  southa
 * MediaSound work
 *
 * Revision 1.4  2002/08/13 17:50:21  southa
 * Added playsound command
 *
 * Revision 1.3  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.2  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.1  2002/07/02 15:48:30  southa
 * Floor map designer
 *
 */

#include "mushCore.h"

class MediaAudioCommandHandler
{
public:
    static void Install(void);
    static CoreScalar PlayMusic(CoreCommand& ioCommand, CoreEnv& ioEnv);
};
#endif
