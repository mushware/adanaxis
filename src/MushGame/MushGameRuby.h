//%includeGuardStart {
#ifndef MUSHGAMERUBY_H
#define MUSHGAMERUBY_H
//%includeGuardStart } umLUrnBd0VXdkb0HFndGjw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameRuby.h
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
//%Header } abz8WfQdtsWpPxv12NZxhA
/*
 * $Id: MushGameRuby.h,v 1.2 2006/07/07 18:13:59 southa Exp $
 * $Log: MushGameRuby.h,v $
 * Revision 1.2  2006/07/07 18:13:59  southa
 * Menu start and stop
 *
 * Revision 1.1  2006/07/07 07:57:29  southa
 * Key translation
 *
 */

#include "MushGameStandard.h"

#include "API/mushMushRuby.h"

class MushGameRuby : public MushRubyEmptyObj<4000>
{
public:
    static Mushware::tRubyValue KeySymbolToName(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue GameModeEnter(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue Quit(Mushware::tRubyValue inSelf);
    static void MethodsInstall(void);
    
private:
};

MUSHRUBYEMPTYOBJ_INSTALL(4000)(void)
{
	EmptyInstallSubclass("MushGame", MushRubyObject::Klass());
    MushGameRuby::MethodsInstall();
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
