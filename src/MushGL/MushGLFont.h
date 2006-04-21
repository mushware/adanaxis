//%includeGuardStart {
#ifndef MUSHGLFONT_H
#define MUSHGLFONT_H
//%includeGuardStart } t3ghUhPwnkLwSMZ+RJKnCA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLFont.h
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
//%Header } GszAZNIc4XTjBhyVnPxI7g
/*
 * $Id$
 * $Log$
 */

#include "MushGLStandard.h"

#include "mushMushRuby.h"

class MushGLFont
{
public:
    
    static Mushware::tRubyValue RubyRender(Mushware::tRubyArgC inArgC,
        Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf);
    static void RubyInstall(void);
    static void Install(void);
private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
