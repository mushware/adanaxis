#ifndef MEDIASOUNDSTREAM_H
#define MEDIASOUNDSTREAM_H
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
 * $Id: MediaSoundStream.h,v 1.1 2002/08/16 21:13:52 southa Exp $
 * $Log: MediaSoundStream.h,v $
 * Revision 1.1  2002/08/16 21:13:52  southa
 * Added MediaSoundStream
 *
 */

#include "mushCore.h"

#include "MediaSDL.h"

class MediaSoundStream
{
public:
    MediaSoundStream(const string& inName);
    const string& FilenameGet(void) const { return m_filename; }

    static CoreScalar SoundStream(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static CoreScalar PlaySoundStream(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static void Install(void);

private:
    string m_filename;
};
#endif
