//%includeGuardStart {
#ifndef MEDIASOUNDSTREAM_H
#define MEDIASOUNDSTREAM_H
//%includeGuardStart } EHnPuJwJVEK7S22kMzkJ0g
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaSoundStream.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } vNBjNbUCI0jb1hp2/2iIZA
/*
 * $Id: MediaSoundStream.h,v 1.10 2004/01/02 21:13:10 southa Exp $
 * $Log: MediaSoundStream.h,v $
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
    static void Install(void);

private:
    std::string m_filename;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
