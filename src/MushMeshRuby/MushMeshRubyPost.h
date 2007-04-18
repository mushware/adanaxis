//%includeGuardStart {
#ifndef MUSHMESHRUBYPOST_H
#define MUSHMESHRUBYPOST_H
//%includeGuardStart } LENY2n19YIp+tUhqba3KBg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyPost.h
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
//%Header } pCiwhiEnc/FvJ7yFh1hl0w
/*
 * $Id: MushMeshRubyPost.h,v 1.1 2006/06/20 19:06:53 southa Exp $
 * $Log: MushMeshRubyPost.h,v $
 * Revision 1.1  2006/06/20 19:06:53  southa
 * Object creation
 *
 */

#include "MushMeshRubyStandard.h"

class MushMeshRubyPost : public MushRubyObj<MushMeshPosticity>
{
public:
	static void RubyInstall(void);
	
protected:
	static Mushware::tRubyValue position(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue velocity(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue angular_position(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue angular_velocity(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue position_equal(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);	
	static Mushware::tRubyValue velocity_equal(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);	
	static Mushware::tRubyValue angular_position_equal(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);	
	static Mushware::tRubyValue angular_velocity_equal(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);	
private:
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
