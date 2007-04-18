//%includeGuardStart {
#ifndef MEDIAAUDIOCOMMANDHANDLER_H
#define MEDIAAUDIOCOMMANDHANDLER_H
//%includeGuardStart } r97NEZCvbdc6OGWQjgXrlA
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioCommandHandler.h
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } WhbmBftIKQuNrZ55YlNk2A
/*
 * $Id: MediaAudioCommandHandler.h,v 1.16 2006/06/01 15:39:13 southa Exp $
 * $Log: MediaAudioCommandHandler.h,v $
 * Revision 1.16  2006/06/01 15:39:13  southa
 * DrawArray verification and fixes
 *
 * Revision 1.15  2005/05/19 13:02:08  southa
 * Mac release work
 *
 * Revision 1.14  2004/01/06 20:46:51  southa
 * Build fixes
 *
 * Revision 1.13  2004/01/02 21:13:10  southa
 * Source conditioning
 *
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

#include "mushMushcore.h"

class MediaAudioCommandHandler
{
public:
    static void Install(void);
    static MushcoreScalar PlayMusic(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
