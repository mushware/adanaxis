#ifndef MEDIASOUND_H
#define MEDIASOUND_H
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
 * $Id: MediaSound.h,v 1.9 2003/01/09 14:57:04 southa Exp $
 * $Log: MediaSound.h,v $
 * Revision 1.9  2003/01/09 14:57:04  southa
 * Created Mushcore
 *
 * Revision 1.8  2002/12/29 20:30:55  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.7  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/27 08:56:28  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/24 13:12:32  southa
 * Null MediaAudio device
 *
 * Revision 1.3  2002/08/16 21:13:52  southa
 * Added MediaSoundStream
 *
 * Revision 1.2  2002/08/16 19:46:07  southa
 * MediaSound work
 *
 * Revision 1.1  2002/08/15 13:39:31  southa
 * MushcoreData and MushcoreDatRef
 *
 */

#include "Mushcore.h"

#include "MediaSDL.h"

class MediaSound
{
public:
    MediaSound(const std::string& inName);
    ~MediaSound();
    void Load(void);
    void Free(void);
    void EndHandler(void);
    const std::string& FilenameGet(void) const { return m_filename; }
    Mix_Chunk *MixChunkGet(void) const { return m_chunk; }
    void MixChunkSet(Mix_Chunk *inChunk) { m_chunk=inChunk; }
    void ResidenceSet(bool inResident) { m_resident=inResident; }

    static MushcoreScalar TransientSound(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar ResidentSound(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar PlaySound(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    
private:
    std::string m_filename;
    Mix_Chunk *m_chunk;
    bool m_resident;
};
#endif
