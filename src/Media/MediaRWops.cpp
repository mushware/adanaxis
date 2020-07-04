//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaRWops.cpp
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
//%Header } M7kgOMR9Zwfez+MpQeZwTg
/*
 * $Id: MediaRWops.cpp,v 1.5 2007/06/25 15:59:43 southa Exp $
 * $Log: MediaRWops.cpp,v $
 * Revision 1.5  2007/06/25 15:59:43  southa
 * X11 compatibility
 *
 * Revision 1.4  2007/04/18 09:22:27  southa
 * Header and level fixes
 *
 * Revision 1.3  2006/11/06 20:37:28  southa
 * Alloc and bounding radius fixes
 *
 * Revision 1.2  2006/11/06 19:27:51  southa
 * Mushfile handling
 *
 * Revision 1.1  2006/11/06 12:56:31  southa
 * MushFile work
 *
 */

#include "MediaRWops.h"

using namespace Mushware;
using namespace std;

MediaRWops::MediaRWops(MushFileFile& ioFile) :
    m_mushFile(ioFile),
    m_pRWops(NULL)
{
}

MediaRWops::~MediaRWops()
{
}

SDL_RWops *
MediaRWops::RWops(void)
{
    SDL_RWops *retVal = NULL;
    if (m_mushFile.SourceIsNull())
    {
        
    }
    else if (m_mushFile.SourceIsFile())
    {
        if (m_pRWops == NULL)
        {
            m_pRWops = SDL_RWFromFile(m_mushFile.PlainFilename().c_str(), "rb");
        }
        
        retVal = m_pRWops;
        if (retVal == NULL)
        {
            throw MushcoreFileFail(m_mushFile.Name(), "Plain file not found");
        }
    }
    else if (m_mushFile.SourceIsMush())
    {
        m_pRWops = SDL_RWFromConstMem(m_mushFile.DataStart(), m_mushFile.DataSize());
        retVal = m_pRWops;
    }
    else
    {
        throw MushcoreFileFail(m_mushFile.Name(), "File not found");
    }

    if (retVal == NULL)
    {
        throw MushcoreFileFail(m_mushFile.Name(), "MediaRWops cannot open file of this type");
    }
    return retVal;
}
