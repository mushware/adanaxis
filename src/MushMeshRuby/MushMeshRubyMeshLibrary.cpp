//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyMeshLibrary.cpp
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
//%Header } VdvEyD/ERRNhz3m3gIZBOw
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
