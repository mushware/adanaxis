//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyMesh.cpp
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
//%Header } oR7WPhSKmfGQldTVFg6TpQ
/*
 * $Id: MushMeshRubyMesh.cpp,v 1.2 2006/06/13 10:35:04 southa Exp $
 * $Log: MushMeshRubyMesh.cpp,v $
 * Revision 1.2  2006/06/13 10:35:04  southa
 * Ruby data objects
 *
 * Revision 1.1  2006/06/12 16:01:23  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshRubyMesh.h"

#include "MushMeshRubyRuby.h"

MUSHRUBYDATAOBJ_INSTANCE(MushMesh4Mesh);

using namespace Mushware;
using namespace std;

MUSHRUBYDATAOBJ_INITIALIZE(MushMesh4Mesh)(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	if (inArgC != 1)
	{
		MushRubyUtil::Raise("MushMesh constructor requires one parameter <mesh name>");
	}
	MushRubyValue nameValue(inpArgV[0]);
	std::string nameStr = nameValue.String();
	DataObjRef(inSelf).NameSet(nameStr);
	tDataObjData::Sgl().GetOrCreate(nameStr); // Create mesh if it doesn't exist

	return inSelf;
}

void
MushMeshRubyMesh::RubyInstall(void)
{
	DataObjInstall("MushMesh");
}

namespace
{
	void Install(void)
	{
		MushRubyInstall::Sgl().Add(MushMeshRubyMesh::RubyInstall);
	}
	MushcoreInstaller install(Install);
}
