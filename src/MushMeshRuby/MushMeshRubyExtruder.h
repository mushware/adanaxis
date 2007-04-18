//%includeGuardStart {
#ifndef MUSHMESHRUBYEXTRUDER_H
#define MUSHMESHRUBYEXTRUDER_H
//%includeGuardStart } s31XL8hpWOP9g7HFyI6Pjg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyExtruder.h
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
//%Header } hz/YwH9ElvmpPHRbIQlz7g
/*
 * $Id: MushMeshRubyExtruder.h,v 1.1 2006/06/14 11:20:08 southa Exp $
 * $Log: MushMeshRubyExtruder.h,v $
 * Revision 1.1  2006/06/14 11:20:08  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshRubyStandard.h"

class MushMeshRubyExtruder : public MushRubyObj<MushMeshLibraryExtruder>
{
public:
	static void RubyInstall(void);
	
private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
