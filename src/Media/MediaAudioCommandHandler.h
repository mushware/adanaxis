#ifndef MEDIAAUDIOCOMMANDHANDLER_H
#define MEDIAAUDIOCOMMANDHANDLER_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: MediaAudioCommandHandler.h,v 1.1 2002/07/02 15:48:30 southa Exp $
 * $Log: MediaAudioCommandHandler.h,v $
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
