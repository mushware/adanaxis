//%includeGuardStart {
#ifndef MUSHFILERUBY_H
#define MUSHFILERUBY_H
//%includeGuardStart } maVG7GUsiEQQ3pwEUeL/Pg
//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileRuby.h
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
//%Header } +LO8BU2aUuhz83bh3+ENyg
/*
 * $Id: MushFileRuby.h,v 1.1 2006/11/06 12:56:32 southa Exp $
 * $Log: MushFileRuby.h,v $
 * Revision 1.1  2006/11/06 12:56:32  southa
 * MushFile work
 *
 */

#include "MushFileStandard.h"

#include "API/mushMushRuby.h"

class MushFileRuby : public MushRubyEmptyObj<6000>
{
public:
	static void MushFileInstall(void);
	
	static Mushware::tRubyValue LibraryAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);    
	static Mushware::tRubyValue LibraryDump(Mushware::tRubyValue inSelf);    
	static Mushware::tRubyValue File(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);    
private:
};

MUSHRUBYEMPTYOBJ_INSTALL(6000)(void)
{
	EmptyInstall("MushFile");
	MushFileRuby::MushFileInstall();
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
