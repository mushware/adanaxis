//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisRubyWorld.cpp
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.4, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } uoFN8PO4Ddik/DdBbZNTuA
/*
 * $Id: AdanaxisRubyWorld.cpp,v 1.4 2007/04/18 09:22:03 southa Exp $
 * $Log: AdanaxisRubyWorld.cpp,v $
 * Revision 1.4  2007/04/18 09:22:03  southa
 * Header and level fixes
 *
 * Revision 1.3  2006/09/09 11:16:40  southa
 * One-time vertex buffer generation
 *
 * Revision 1.2  2006/08/01 17:21:28  southa
 * River demo
 *
 * Revision 1.1  2006/07/19 10:22:15  southa
 * World objects
 *
 */

#include "AdanaxisRubyWorld.h"

#include "AdanaxisRuby.h"
#include "AdanaxisVolatileData.h"

#include "API/mushMushGame.h"
#include "API/mushMushMeshRuby.h"

MUSHRUBYMAPTOROBJ_INSTANCE(AdanaxisPieceWorld);

using namespace Mushware;
using namespace std;

MUSHRUBYMAPTOROBJ_INITIALIZE(AdanaxisPieceWorld)(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	tMaptorObjRef& refRef = MaptorObjRef(inSelf);
	tMaptorObjData& dataRef = AdanaxisRuby::VolatileData().WorldListWRef();
	
	refRef.MaptorSet(dataRef);
	
	refRef.KeySet(dataRef.NextKey());
	AdanaxisPieceWorld& khaziRef = *refRef.GetOrCreate();
	
	std::string meshName = "";
	
	switch (inArgC)
	{
		case 1:
		{			
			MushRubyValue param0(inpArgV[0]);
			if (!param0.IsHash())
			{
				MushRubyUtil::Raise("Parameters to AdanaxisWorld.new must be in hash form");	
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
						MushRubyUtil::Raise("Unknown name in AdanaxisWorld parameter hash '"+p->first.String()+"'");	
					}
				}
			}
		}
            break;
			
		default:
			MushRubyUtil::Raise("AdanaxisRubyWorld constructor requires a parameter hash");
			break;
			
	}
	
	if (meshName != "")
    {
		khaziRef.MeshWRef() = *MushcoreData<MushMesh4Mesh>::Sgl().Get(meshName);
		khaziRef.SharedBuffersNameSet(meshName);
	}
    else
	{
		MushcoreLog::Sgl().WarningLog() << "Creating AdanaxisWorld object without a valid mesh_name parameter" << endl;	
	}
	
	return inSelf;
}

Mushware::tRubyValue
AdanaxisRubyWorld::post(Mushware::tRubyValue inSelf)
{
	Mushware::tRubyValue retVal = MushMeshRubyPost::NewInstance();
	MushMeshRubyPost::WRef(retVal) = Ref(inSelf).Post();
	return retVal;
}

Mushware::tRubyValue
AdanaxisRubyWorld::post_equal(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	WRef(inSelf).PostSet(MushMeshRubyPost::Ref(inArg0));
	return inSelf;
}

void
AdanaxisRubyWorld::RubyInstall(void)
{
	MaptorObjInstall("AdanaxisWorld");
	MushRubyUtil::MethodDefineNoParams(Klass(), "post", post);
	MushRubyUtil::MethodDefineOneParam(Klass(), "post=", post_equal);
}

namespace
{
	void Install(void)
	{
		MushRubyInstall::Sgl().Add(AdanaxisRubyWorld::RubyInstall);
	}
	MushcoreInstaller install(Install);
}
