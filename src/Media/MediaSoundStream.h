//%includeGuardStart {
#ifndef MEDIASOUNDSTREAM_H
#define MEDIASOUNDSTREAM_H
//%includeGuardStart } EHnPuJwJVEK7S22kMzkJ0g
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaSoundStream.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } sPuyCP3r99Gc00myo/BA1Q
/*
 * $Id: MediaSoundStream.h,v 1.13 2005/05/19 13:02:08 southa Exp $
 * $Log: MediaSoundStream.h,v $
 * Revision 1.13  2005/05/19 13:02:08  southa
 * Mac release work
 *
 * Revision 1.12  2005/04/19 23:25:41  southa
 * Mode switching and recognition
 *
 * Revision 1.11  2004/01/06 20:46:51  southa
 * Build fixes
 *
 * Revision 1.10  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.9  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:09:02  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
 * Revision 1.6  2003/01/09 14:57:05  southa
 * Created Mushcore
 *
 * Revision 1.5  2002/12/29 20:30:55  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.4  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/27 08:56:29  southa
 * Source conditioning
 *
 * Revision 1.1  2002/08/16 21:13:52  southa
 * Added MediaSoundStream
 *
 */

#include "mushMushcore.h"

#include "MediaSDL.h"

class MediaSoundStream
{
public:
    MediaSoundStream(const std::string& inName);
    const std::string& FilenameGet(void) const { return m_filename; }

    static MushcoreScalar SoundStream(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar PlaySoundStream(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar LoadSoundStream(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);

private:
    std::string m_filename;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
