//%includeGuardStart {
#ifndef MUSHMESHRUBYDISPLACEMENT_H
#define MUSHMESHRUBYDISPLACEMENT_H
//%includeGuardStart } wA/o7FTWPUZkSPtLetn3sA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyDisplacement.h
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
//%Header } RqIYygnsvbiaEc0+PyskZQ
/*
 * $Id: MushMeshRubyDisplacement.h,v 1.1 2006/06/12 16:01:23 southa Exp $
 * $Log: MushMeshRubyDisplacement.h,v $
 * Revision 1.1  2006/06/12 16:01:23  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshRubyStandard.h"

class MushMeshDisplacement;

class MushMeshRubyDisplacement : public MushRubyObj<MushMeshDisplacement>
{
public:
	static void RubyInstall(void);	
private:
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
