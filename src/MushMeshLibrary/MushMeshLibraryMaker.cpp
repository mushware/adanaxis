//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryMaker.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } AFvudcE2/OMut3boSNqwAQ
/*
 * $Id: MushMeshLibraryMaker.cpp,v 1.4 2007/04/18 09:22:53 southa Exp $
 * $Log: MushMeshLibraryMaker.cpp,v $
 * Revision 1.4  2007/04/18 09:22:53  southa
 * Header and level fixes
 *
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
