#ifndef MEDIASOUNDSTREAM_H
#define MEDIASOUNDSTREAM_H
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
 * $Id: MediaSoundStream.h,v 1.6 2003/01/09 14:57:05 southa Exp $
 * $Log: MediaSoundStream.h,v $
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

#include "Mushcore.h"

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
#endif
