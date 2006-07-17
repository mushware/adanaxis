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
 * $Id: MushMeshRubyMesh.cpp,v 1.10 2006/07/16 09:19:47 southa Exp $
 * $Log: MushMeshRubyMesh.cpp,v $
 * Revision 1.10  2006/07/16 09:19:47  southa
 * Delete mesh before creating
 *
 * Revision 1.9  2006/06/22 19:07:33  southa
 * Build fixes
 *
 * Revision 1.8  2006/06/21 12:17:58  southa
 * Ruby object generation
 *
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

#include "MushMeshRubyMesh.h"

#include "MushMeshRubyBase.h"
#include "MushMeshRubyBasePrism.h"
#include "MushMeshRubyBaseSingleFacet.h"
#include "MushMeshRubyDisplacement.h"
#include "MushMeshRubyExtruder.h"
// #include "MushMeshRubyRuby.h"

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

    tDataObjData::Sgl().IfExistsDelete(nameStr); // Create mesh if it doesn't exist
	tDataObjData::Sgl().GetOrCreate(nameStr); // Create mesh if it doesn't exist

	WRef(inSelf).TexCoordDelegateSet(MushMesh4Mesh::tDataRef(nameStr));

	return inSelf;
}

Mushware::tRubyValue
MushMeshRubyMesh::BaseAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	try
	{
        if (MushMeshRubyBasePrism::IsInstanceOf(inArg0))
        {
		    WRef(inSelf).BaseGive(new MushMeshLibraryPrism(MushMeshRubyBasePrism::Ref(inArg0)));
        }
        else if (MushMeshRubyBaseSingleFacet::IsInstanceOf(inArg0))
        {
		    WRef(inSelf).BaseGive(new MushMeshLibrarySingleFacet(MushMeshRubyBaseSingleFacet::Ref(inArg0)));
        }
        else
        {
            MushRubyUtil::Raise("Wrong type for BaseAdd"); 
        }
	}
	catch (std::exception& e)
	{
		MushRubyUtil::Raise(e.what());
	}
	return inSelf;
}

Mushware::tRubyValue
MushMeshRubyMesh::BaseDisplacementAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	if (!MushMeshRubyDisplacement::IsInstanceOf(inArg0))
	{
		MushRubyUtil::Raise("Wrong type for BaseDisplacementAdd - must be MushDisplacement");
	}
	try
	{
		WRef(inSelf).BaseDisplacementSet(MushMeshRubyDisplacement::Ref(inArg0));
	}
	catch (std::exception& e)
	{
		MushRubyUtil::Raise(e.what());
	}
	return inSelf;
}

Mushware::tRubyValue
MushMeshRubyMesh::BillboardSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	try
    {
        MushRubyValue param0(inArg0);
        if (param0.Bool())
        {
            WRef(inSelf).TransformTypeSet(MushMesh4Mesh::kTransformTypeBillboard);
        }
        else
        {
            WRef(inSelf).TransformTypeSet(MushMesh4Mesh::kTransformTypeNormal);
        }
    }
    catch (std::exception& e)
    {
        MushRubyUtil::Raise(e.what());
    }
    return inSelf;
}

Mushware::tRubyValue
MushMeshRubyMesh::ExtruderAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	if (!MushMeshRubyExtruder::IsInstanceOf(inArg0))
	{
		MushRubyUtil::Raise("Wrong type for ExtruderAdd - must be MushExtruder");
	}
	try
    {
        WRef(inSelf).ExtruderGive(new MushMeshLibraryExtruder(MushMeshRubyExtruder::Ref(inArg0)));
    }
    catch (std::exception& e)
    {
        MushRubyUtil::Raise(e.what());
    }
    return inSelf;
}

Mushware::tRubyValue
MushMeshRubyMesh::MaterialAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	try
	{
		MushRubyValue param0(inArg0);
		std::string materialName = param0.String();
		WRef(inSelf).MaterialNameSet(materialName, 0);
	}
	catch (std::exception& e)
	{
		MushRubyUtil::Raise(e.what());
	}
	return inSelf;
}

Mushware::tRubyValue
MushMeshRubyMesh::Make(Mushware::tRubyValue inSelf)
{
	try
	{
		WRef(inSelf).Make();
	}
	catch (std::exception& e)
	{
		MushRubyUtil::Raise(e.what());
	}
	return inSelf;
}

void
MushMeshRubyMesh::RubyInstall(void)
{
	DataObjInstall("MushMesh");
	MushRubyUtil::MethodDefineOneParam(DataObjKlass(), "mBaseAdd", BaseAdd);
	MushRubyUtil::MethodDefineOneParam(DataObjKlass(), "mBaseDisplacementAdd", BaseDisplacementAdd);
	MushRubyUtil::MethodDefineOneParam(DataObjKlass(), "mBillboardSet", BillboardSet);
	MushRubyUtil::MethodDefineOneParam(DataObjKlass(), "mExtruderAdd", ExtruderAdd);
	MushRubyUtil::MethodDefineOneParam(DataObjKlass(), "mMaterialAdd", MaterialAdd);
	MushRubyUtil::MethodDefineNoParams(DataObjKlass(), "mMake", Make);
}

namespace
{
	void Install(void)
	{
		MushRubyInstall::Sgl().Add(MushMeshRubyMesh::RubyInstall);
	}
	MushcoreInstaller install(Install);
}
