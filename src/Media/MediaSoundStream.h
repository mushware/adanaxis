/*
 * $Id$
 * $Log$
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
