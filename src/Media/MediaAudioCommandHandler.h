//%includeGuardStart {
#ifndef MEDIAAUDIOCOMMANDHANDLER_H
#define MEDIAAUDIOCOMMANDHANDLER_H
//%includeGuardStart } r97NEZCvbdc6OGWQjgXrlA
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioCommandHandler.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } qjKXp7uUgjCLAhL62k0zMA
/*
 * $Id: MediaAudioCommandHandler.h,v 1.12 2003/09/17 19:40:34 southa Exp $
 * $Log: MediaAudioCommandHandler.h,v $
 * Revision 1.12  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.11  2003/08/21 23:09:00  southa
 * Fixed file headers
 *
 * Revision 1.10  2003/01/11 13:03:15  southa
 * Use Mushcore header
 *
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
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
