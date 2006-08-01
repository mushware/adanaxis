//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisRubyKhazi.cpp
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.1, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } qwHjHWDAhJ5nzUjaMqYD6A
/*
 * $Id: AdanaxisRubyKhazi.cpp,v 1.2 2006/06/21 16:52:29 southa Exp $
 * $Log: AdanaxisRubyKhazi.cpp,v $
 * Revision 1.2  2006/06/21 16:52:29  southa
 * Deco objects
 *
 * Revision 1.1  2006/06/21 12:17:56  southa
 * Ruby object generation
 *
 */

#include "AdanaxisRubyKhazi.h"

#include "AdanaxisRuby.h"
#include "AdanaxisSaveData.h"

#include "API/mushMushGame.h"
#include "API/mushMushMeshRuby.h"

MUSHRUBYMAPTOROBJ_INSTANCE(AdanaxisPieceKhazi);

using namespace Mushware;
using namespace std;

MUSHRUBYMAPTOROBJ_INITIALIZE(AdanaxisPieceKhazi)(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	tMaptorObjRef& refRef = MaptorObjRef(inSelf);
	tMaptorObjData& dataRef = AdanaxisRuby::SaveData().KhaziListWRef();
	
	/* This object contains a reference (MushcoreMaptorRef) to an object
	 * in SaveData().KhaziList(), which is a MushcoreMaptor<AdanaxisPieceKhazi>.
	 * The next line points the MushcoreMaptorRef at that MushcoreMaptor
	 */
	refRef.MaptorSet(dataRef);
	
	refRef.KeySet(dataRef.NextKey());
	AdanaxisPieceKhazi& khaziRef = *refRef.GetOrCreate();

	std::string meshName = "";
	
	switch (inArgC)
	{
		case 1:
		{			
			MushRubyValue param0(inpArgV[0]);
			if (!param0.IsHash())
			{
				MushRubyUtil::Raise("Parameters to AdanaxisKhazi.new must be in hash form");	
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
						MushRubyUtil::Raise("Unknown name in AdanaxisKhazi parameter hash '"+p->first.String()+"'");	
					}
				}
			}
		}
		break;
			
		default:
			MushRubyUtil::Raise("AdanaxisRubyKhazi constructor requires a parameter hash");
			break;			
	}
	
	if (meshName != "")
    {
		khaziRef.MeshWRef() = *MushcoreData<MushMesh4Mesh>::Sgl().Get(meshName);
		khaziRef.TexCoordBuffersNameSet(meshName);
	}
    else
	{
			MushcoreLog::Sgl().WarningLog() << "Creating AdanaxisKhazi object without a valid mesh_name parameter" << endl;	
	}

	return inSelf;
}

Mushware::tRubyValue
AdanaxisRubyKhazi::post(Mushware::tRubyValue inSelf)
{
	Mushware::tRubyValue retVal = MushMeshRubyPost::NewInstance();
	MushMeshRubyPost::WRef(retVal) = Ref(inSelf).Post();
	return retVal;
}

Mushware::tRubyValue
AdanaxisRubyKhazi::post_equal(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	WRef(inSelf).PostSet(MushMeshRubyPost::Ref(inArg0));
	return inSelf;
}

void
AdanaxisRubyKhazi::RubyInstall(void)
{
	MaptorObjInstall("AdanaxisKhazi");
	MushRubyUtil::MethodDefineNoParams(Klass(), "post", post);
	MushRubyUtil::MethodDefineOneParam(Klass(), "post=", post_equal);
}

namespace
{
	void Install(void)
	{
		MushRubyInstall::Sgl().Add(AdanaxisRubyKhazi::RubyInstall);
	}
	MushcoreInstaller install(Install);
}
