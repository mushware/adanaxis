//%includeGuardStart {
#ifndef MEDIASOUNDSTREAM_H
#define MEDIASOUNDSTREAM_H
//%includeGuardStart } EHnPuJwJVEK7S22kMzkJ0g
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaSoundStream.h
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
//%Header } qQgjdY2Z0THes8y9+1PNGw
/*
 * $Id: MediaSoundStream.h,v 1.14 2006/06/01 15:39:14 southa Exp $
 * $Log: MediaSoundStream.h,v $
 * Revision 1.14  2006/06/01 15:39:14  southa
 * DrawArray verification and fixes
 *
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
