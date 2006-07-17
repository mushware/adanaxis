//%includeGuardStart {
#ifndef MUSHMESHRUBYMESH_H
#define MUSHMESHRUBYMESH_H
//%includeGuardStart } 0fz+h5HaFSFoFE3/de8MLg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyMesh.h
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
//%Header } hSrHx4/wCdfB19VcRmiYhw
/*
 * $Id: MushMeshRubyMesh.h,v 1.7 2006/06/19 15:57:19 southa Exp $
 * $Log: MushMeshRubyMesh.h,v $
 * Revision 1.7  2006/06/19 15:57:19  southa
 * Materials
 *
 * Revision 1.6  2006/06/16 01:02:33  southa
 * Ruby mesh generation
 *
 * Revision 1.5  2006/06/14 18:45:49  southa
 * Ruby mesh generation
 *
 * Revision 1.4  2006/06/14 11:20:08  southa
 * Ruby mesh generation
 *
 * Revision 1.3  2006/06/13 19:30:37  southa
 * Ruby mesh generation
 *
 * Revision 1.2  2006/06/13 10:35:04  southa
 * Ruby data objects
 *
 * Revision 1.1  2006/06/12 16:01:23  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshRubyStandard.h"

class MushMeshMesh;

class MushMeshRubyMesh : public MushRubyDataObj<MushMesh4Mesh>
{
public:
	static void RubyInstall(void);
	
protected:
	static Mushware::tRubyValue BaseAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	static Mushware::tRubyValue BaseDisplacementAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	static Mushware::tRubyValue BillboardSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	static Mushware::tRubyValue ExtruderAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	static Mushware::tRubyValue MaterialAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	static Mushware::tRubyValue Make(Mushware::tRubyValue inSelf);

private:
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
