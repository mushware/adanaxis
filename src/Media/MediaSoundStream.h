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
 * $Id: MediaSoundStream.h,v 1.4 2002/12/20 13:17:45 southa Exp $
 * $Log: MediaSoundStream.h,v $
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

#include "mushCore.h"

#include "MediaSDL.h"

class MediaSoundStream
{
public:
    MediaSoundStream(const std::string& inName);
    const std::string& FilenameGet(void) const { return m_filename; }

    static CoreScalar SoundStream(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static CoreScalar PlaySoundStream(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static void Install(void);

private:
    std::string m_filename;
};
#endif
