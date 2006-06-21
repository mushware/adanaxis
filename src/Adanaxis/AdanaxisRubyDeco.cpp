//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisRubyDeco.cpp
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } r5rNdYDyBUZExmiHMjHIWA
/*
 * $Id$
 * $Log$
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
		khaziRef.TexCoordBuffersNameSet(meshName);
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
