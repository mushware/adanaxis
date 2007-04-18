//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyMeshLibrary.cpp
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
//%Header } JB/lGUI/utOVDc4rgxGtPg
/*
 * $Id: MushMeshRubyMeshLibrary.cpp,v 1.5 2006/06/22 19:07:33 southa Exp $
 * $Log: MushMeshRubyMeshLibrary.cpp,v $
 * Revision 1.5  2006/06/22 19:07:33  southa
 * Build fixes
 *
 * Revision 1.4  2006/06/20 19:06:53  southa
 * Object creation
 *
 * Revision 1.3  2006/06/13 19:30:38  southa
 * Ruby mesh generation
 *
 * Revision 1.2  2006/06/13 10:35:04  southa
 * Ruby data objects
 *
 * Revision 1.1  2006/06/12 16:01:23  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshRubyMeshLibrary.h"

#include "MushMeshRubyMesh.h"
// #include "MushMeshRubyRuby.h"
#include "MushMeshRubyVector.h"

#include "API/mushMushMeshLibrary.h"

using namespace Mushware;
using namespace std;

MUSHRUBYOBJ_INSTANCE(MushMeshLibraryBase);

Mushware::tRubyValue
MushMeshRubyMeshLibrary::PolygonPrismCreate(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1,
											Mushware::tRubyValue inArg2, Mushware::tRubyValue inArg3)
{
	MushMesh4Mesh& meshRef = MushMeshRubyMesh::WRef(inArg1);
	Mushware::t4Val scaleRef = MushMeshRubyVector::WRef(inArg2);
	MushRubyValue orderValue(inArg3);
	
	MushMeshLibraryBase::Sgl().PolygonPrismCreate(meshRef, scaleRef, orderValue.U32());
	
	return inSelf;
}											
											
void
MushMeshRubyMeshLibrary::RubyInstall(void)
{
	ObjInstall("MushMeshLibrary");
	
	MushRubyUtil::SingletonMethodDefineThreeParams(ObjKlass(), "cPolygonPrismCreate", PolygonPrismCreate);
}

MUSHRUBY_INSTALL(MushMeshRubyMeshLibrary);
