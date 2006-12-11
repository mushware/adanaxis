//%includeGuardStart {
#ifndef MUSHGLRUBY_H
#define MUSHGLRUBY_H
//%includeGuardStart } f8JH71NND8fMo45CMrGt2Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLRuby.h
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
//%Header } 8Q0XWSnnfxmEBtFinmGeBw
/*
 * $Id$
 * $Log$
 */

#include "MushGLStandard.h"

#include "API/mushMushRuby.h"

class MushGLRuby : public MushRubyEmptyObj<7000>
{
public:
	static void MushGLInstall(void);
    static Mushware::tRubyValue ViewExtent(Mushware::tRubyValue inSelf);
private:
};

MUSHRUBYEMPTYOBJ_INSTALL(7000)(void)
{
	EmptyInstall("MushGL");
	MushGLRuby::MushGLInstall();
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
