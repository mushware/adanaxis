/*
 * $Id: MediaSound.h,v 1.3 2002/08/16 21:13:52 southa Exp $
 * $Log: MediaSound.h,v $
 * Revision 1.3  2002/08/16 21:13:52  southa
 * Added MediaSoundStream
 *
 * Revision 1.2  2002/08/16 19:46:07  southa
 * MediaSound work
 *
 * Revision 1.1  2002/08/15 13:39:31  southa
 * CoreData and CoreDatRef
 *
 */

#include "mushCore.h"

#include "MediaSDL.h"

class MediaSound
{
public:
    MediaSound(const string& inName);
    ~MediaSound();
    void Load(void);
    void Free(void);
    void EndHandler(void);
    const string& FilenameGet(void) const { return m_filename; }
    Mix_Chunk *MixChunkGet(void) const { return m_chunk; }
    void MixChunkSet(Mix_Chunk *inChunk) { m_chunk=inChunk; }
    void ResidenceSet(bool inResident) { m_resident=inResident; }

    static CoreScalar TransientSound(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static CoreScalar ResidentSound(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static CoreScalar PlaySound(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static void Install(void);
    
private:
    string m_filename;
    Mix_Chunk *m_chunk;
    bool m_resident;
};
