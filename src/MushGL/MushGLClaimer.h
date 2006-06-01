//%includeGuardStart {
#ifndef MUSHGLCLAIMER_H
#define MUSHGLCLAIMER_H
//%includeGuardStart } 4OgFyVD5b4MruLBSe1Mx6A
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLClaimer.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } UQsydd3AgkasB2lW0UWYNg
/*
 * $Id: MushGLClaimer.h,v 1.1 2005/07/04 11:10:43 southa Exp $
 * $Log: MushGLClaimer.h,v $
 * Revision 1.1  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 */

#include "MushGLStandard.h"

#include "MushGLBuffers.h"

template<class T>
class MushGLClaimer
{
public:
    enum
    {
        kOwnerInvalid,
        kOwnerNone,
        kOwnerMushGL,
        kOwnerOther
    };
    explicit MushGLClaimer(T& ioClaimed, Mushware::U32 inOwner = MushGLBuffers::kOwnerOther) :
        m_claimed(ioClaimed),
        m_owner(inOwner)
    {
        m_claimed.Claim(m_owner);
    }

    ~MushGLClaimer() { m_claimed.Release(m_owner); }

private:
    T& m_claimed;
    Mushware::U32 m_owner;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
