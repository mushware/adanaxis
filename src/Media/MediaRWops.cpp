//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaRWops.cpp
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } ZI86PyCnqBLWlcJZZkAnWA
/*
 * $Id: MediaRWops.cpp,v 1.3 2006/11/06 20:37:28 southa Exp $
 * $Log: MediaRWops.cpp,v $
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
    if (m_mushFile.SourceIsFile())
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
    
    if (retVal == NULL)
    {
        throw MushcoreFileFail(m_mushFile.Name(), "MediaRWops cannot open file of this type");
    }
    return retVal;
}
