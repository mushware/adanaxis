//%includeGuardStart {
#ifndef MUSHRUBYOBJECT_H
#define MUSHRUBYOBJECT_H
//%includeGuardStart } xHqxdIndLRouJD8Rk8IjdA
//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyObject.h
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
//%Header } 1spFzd+tKmmAcPwCez5bHw
/*
 * $Id: MushRubyObject.h,v 1.1 2006/06/16 12:11:05 southa Exp $
 * $Log: MushRubyObject.h,v $
 * Revision 1.1  2006/06/16 12:11:05  southa
 * Ruby subclasses
 *
 */

#include "MushRubyStandard.h"

#include "MushRubyEmptyObj.h"

class MushRubyObject : public MushRubyEmptyObj<1>
{
public:
private:
};

MUSHRUBYEMPTYOBJ_INSTALL(1)(void)
{
	EmptyInstall("MushObject");
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
