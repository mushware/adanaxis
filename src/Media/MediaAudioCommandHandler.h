#ifndef MEDIAAUDIOCOMMANDHANDLER_H
#define MEDIAAUDIOCOMMANDHANDLER_H
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
 * $Id: MediaAudioCommandHandler.h,v 1.9 2003/01/09 14:57:04 southa Exp $
 * $Log: MediaAudioCommandHandler.h,v $
 * Revision 1.9  2003/01/09 14:57:04  southa
 * Created Mushcore
 *
 * Revision 1.8  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/10/22 20:42:07  southa
 * Source conditioning
 *
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
 * Floor std::map designer
 *
 */

#include "Mushcore.h"

class MediaAudioCommandHandler
{
public:
    static void Install(void);
    static MushcoreScalar PlayMusic(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};
#endif
