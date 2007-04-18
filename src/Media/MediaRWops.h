//%includeGuardStart {
#ifndef MEDIARWOPS_H
#define MEDIARWOPS_H
//%includeGuardStart } jjoZRQCf7yc7yVeQWx4GbQ
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaRWops.h
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
//%Header } LAizokfdyQ59fagIj3w14g
/*
 * $Id: MediaRWops.h,v 1.1 2006/11/06 12:56:31 southa Exp $
 * $Log: MediaRWops.h,v $
 * Revision 1.1  2006/11/06 12:56:31  southa
 * MushFile work
 *
 */

#include "MediaStandard.h"

#include "MediaSDL.h"

class MediaRWops
{
public:
    explicit MediaRWops(MushFileFile& ioFile);
    ~MediaRWops();
    SDL_RWops *RWops(void);
    
private:
    MushFileFile& m_mushFile; //:read
    SDL_RWops *m_pRWops;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
