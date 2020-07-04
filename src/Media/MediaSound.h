//%includeGuardStart {
#ifndef MEDIASOUND_H
#define MEDIASOUND_H
//%includeGuardStart } j/z3aSYbVnN574ydLaERaA
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaSound.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } mXEJasZc1dtqtm5r68XatA
/*
 * $Id: MediaSound.h,v 1.17 2007/04/18 09:22:27 southa Exp $
 * $Log: MediaSound.h,v $
 * Revision 1.17  2007/04/18 09:22:27  southa
 * Header and level fixes
 *
 * Revision 1.16  2006/06/01 15:39:14  southa
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
 * Revision 1.11  2003/08/21 23:09:02  southa
 * Fixed file headers
 *
 * Revision 1.10  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
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

#include "mushMushcore.h"

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
    void IsNullSet(bool inIsNull) { m_isNull = inIsNull; }
    bool IsNull(void) const { return m_isNull; }

    static MushcoreScalar TransientSound(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar ResidentSound(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar PlaySound(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    
private:
    std::string m_filename;
    Mix_Chunk *m_chunk;
    bool m_resident;
    bool m_isNull;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
