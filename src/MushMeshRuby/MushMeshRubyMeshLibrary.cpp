//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyMeshLibrary.cpp
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
//%Header } 7po3niQtybBuVvnFyMOO2w
/*
 * $Id: MushMeshRubyMeshLibrary.cpp,v 1.1 2006/06/12 16:01:23 southa Exp $
 * $Log: MushMeshRubyMeshLibrary.cpp,v $
 * Revision 1.1  2006/06/12 16:01:23  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshRubyMeshLibrary.h"

#include "MushMeshRubyMesh.h"
#include "MushMeshRubyRuby.h"
#include "MushMeshRubyVector.h"

#include "API/mushMushMeshLibrary.h"

using namespace Mushware;
using namespace std;

Mushware::tRubyValue MushMeshRubyMeshLibrary::m_meshLibraryKlass = Qnil;

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
	m_meshLibraryKlass = MushRubyUtil::ClassDefine("MushMeshLibrary");
	
	MushRubyUtil::SingletonMethodDefineThreeParams(m_meshLibraryKlass, "sPolygonPrismCreate", PolygonPrismCreate);
}

namespace
{
	void Install(void)
	{
		MushRubyInstall::Sgl().Add(MushMeshRubyMeshLibrary::RubyInstall);
	}
	MushcoreInstaller install(Install);
}
