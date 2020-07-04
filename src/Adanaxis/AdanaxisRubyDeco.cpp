//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisRubyDeco.cpp
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
//%Header } eYRsped2Zyo3qvUQ4xIC8A
/*
 * $Id: AdanaxisRubyDeco.cpp,v 1.4 2007/04/18 09:22:03 southa Exp $
 * $Log: AdanaxisRubyDeco.cpp,v $
 * Revision 1.4  2007/04/18 09:22:03  southa
 * Header and level fixes
 *
 * Revision 1.3  2006/09/09 11:16:40  southa
 * One-time vertex buffer generation
 *
 * Revision 1.2  2006/08/01 17:21:27  southa
 * River demo
 *
 * Revision 1.1  2006/06/21 16:52:29  southa
 * Deco objects
 *
 */

#include "AdanaxisRubyDeco.h"

#include "AdanaxisRuby.h"
#include "AdanaxisVolatileData.h"

#include "API/mushMushGame.h"
#include "API/mushMushMeshRuby.h"

MUSHRUBYMAPTOROBJ_INSTANCE(AdanaxisPieceDeco);

using namespace Mushware;
using namespace std;

MUSHRUBYMAPTOROBJ_INITIALIZE(AdanaxisPieceDeco)(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	tMaptorObjRef& refRef = MaptorObjRef(inSelf);
	tMaptorObjData& dataRef = AdanaxisRuby::VolatileData().DecoListWRef();
	
	refRef.MaptorSet(dataRef);
	
	refRef.KeySet(dataRef.NextKey());
	AdanaxisPieceDeco& khaziRef = *refRef.GetOrCreate();
	
	std::string meshName = "";
	
	switch (inArgC)
	{
		case 1:
		{			
			MushRubyValue param0(inpArgV[0]);
			if (!param0.IsHash())
			{
				MushRubyUtil::Raise("Parameters to AdanaxisDeco.new must be in hash form");	
			}
			else
			{
				Mushware::tRubyHash paramHash = param0.Hash();
				
				for (Mushware::tRubyHash::iterator p = paramHash.begin(); p != paramHash.end(); ++p)
				{
					tRubyID symbol = p->first.Symbol();
					if (symbol == MushRubyIntern::post())
					{
						khaziRef.PostSet(MushMeshRubyPost::Ref(p->second.Value()));
					}
					else if (symbol == MushRubyIntern::mesh_name())
					{
						meshName = p->second.String();
					}
					else
					{
						MushRubyUtil::Raise("Unknown name in AdanaxisDeco parameter hash '"+p->first.String()+"'");	
					}
				}
			}
		}
		break;
			
		default:
			MushRubyUtil::Raise("AdanaxisRubyDeco constructor requires a parameter hash");
			break;
			
	}
	
	if (meshName != "")
    {
		khaziRef.MeshWRef() = *MushcoreData<MushMesh4Mesh>::Sgl().Get(meshName);
		khaziRef.SharedBuffersNameSet(meshName);
	}
    else
	{
		MushcoreLog::Sgl().WarningLog() << "Creating AdanaxisDeco object without a valid mesh_name parameter" << endl;	
	}
	
	return inSelf;
}

Mushware::tRubyValue
AdanaxisRubyDeco::post(Mushware::tRubyValue inSelf)
{
	Mushware::tRubyValue retVal = MushMeshRubyPost::NewInstance();
	MushMeshRubyPost::WRef(retVal) = Ref(inSelf).Post();
	return retVal;
}

Mushware::tRubyValue
AdanaxisRubyDeco::post_equal(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	WRef(inSelf).PostSet(MushMeshRubyPost::Ref(inArg0));
	return inSelf;
}

void
AdanaxisRubyDeco::RubyInstall(void)
{
	MaptorObjInstall("AdanaxisDeco");
	MushRubyUtil::MethodDefineNoParams(Klass(), "post", post);
	MushRubyUtil::MethodDefineOneParam(Klass(), "post=", post_equal);
}

namespace
{
	void Install(void)
	{
		MushRubyInstall::Sgl().Add(AdanaxisRubyDeco::RubyInstall);
	}
	MushcoreInstaller install(Install);
}
