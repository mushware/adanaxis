//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryMaker.cpp
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.3, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } hSqJt96BvmTOL3t77e000g
/*
 * $Id: MushMeshLibraryMaker.cpp,v 1.3 2006/08/01 17:21:34 southa Exp $
 * $Log: MushMeshLibraryMaker.cpp,v $
 * Revision 1.3  2006/08/01 17:21:34  southa
 * River demo
 *
 * Revision 1.2  2006/06/16 01:02:32  southa
 * Ruby mesh generation
 *
 * Revision 1.1  2006/06/14 18:45:49  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshLibraryMaker.h"

#include "MushMeshLibraryBase.h"
#include "MushMeshLibraryExtruder.h"
#include "MushMeshLibraryFGenExtrude.h"
#include "MushMeshLibraryVGenExtrude.h"

using namespace Mushware;
using namespace std;

void
MushMeshLibraryMaker::Make(MushMesh4Mesh& ioMesh)
{
	const MushMesh4Base *pBase = ioMesh.BaseGet();

	if (pBase == NULL)
	{
		MushcoreLog::Sgl().WarningLog() << "No base object defined for mesh - cannot create" << endl;
	}
	
	pBase->Make(ioMesh);
	
	ioMesh.Apply(ioMesh.BaseDisplacement());

	U32 numExtruders = ioMesh.NumExtruders();
	
	for (U32 i=0; i<numExtruders; ++i)
	{
		const MushMeshLibraryExtruder *pExtruder = dynamic_cast<const MushMeshLibraryExtruder *>(ioMesh.ExtruderGet(i));
		if (pExtruder == NULL)
		{
			MushcoreLog::Sgl().WarningLog() << "Ignoring extruder (wrong type)" << endl;
		}
		else
		{
			MushMeshLibraryExtrusionContext faceContext(pExtruder->Disp(), pExtruder->SourceFaceNum());
			MushMeshLibraryFGenExtrude faceExtrude;
			faceExtrude.FaceExtrude(ioMesh, faceContext ,pExtruder->NumIterations());
			
			MushMeshLibraryExtrusionContext vertexContext(pExtruder->Disp(), pExtruder->SourceFaceNum());
			MushMeshLibraryVGenExtrude vertexExtrude;
			vertexExtrude.FaceExtrude(ioMesh, vertexContext ,pExtruder->NumIterations());
        }
	}
}

//%outOfLineFunctions {

const char *MushMeshLibraryMaker::AutoName(void) const
{
    return "MushMeshLibraryMaker";
}

MushcoreVirtualObject *MushMeshLibraryMaker::AutoClone(void) const
{
    return new MushMeshLibraryMaker(*this);
}

MushcoreVirtualObject *MushMeshLibraryMaker::AutoCreate(void) const
{
    return new MushMeshLibraryMaker;
}

MushcoreVirtualObject *MushMeshLibraryMaker::AutoVirtualFactory(void)
{
    return new MushMeshLibraryMaker;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMeshLibraryMaker", MushMeshLibraryMaker::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMeshLibraryMaker::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushMesh4Maker::AutoPrint(ioOut);
    ioOut << "]";
}
bool
MushMeshLibraryMaker::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MushMesh4Maker::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushMeshLibraryMaker::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushMesh4Maker::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } uwucyOGWYSJTgsbnT9mYFw
