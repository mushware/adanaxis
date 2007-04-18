//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyBaseSingleFacet.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } aJZ8TBMxKkowOR3hulsWHQ
/*
 *  MushMeshRubyBaseSingleFacet.cpp
 *  project
 *
 *  Created by Andy Southgate on 17/07/2006.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "MushMeshRubyBaseSingleFacet.h"

#include "MushMeshRubyBase.h"

using namespace Mushware;
using namespace std;

MUSHRUBYOBJ_INSTANCE(MushMeshLibrarySingleFacet);

MUSHRUBYOBJ_INITIALIZE(MushMeshLibrarySingleFacet)(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	MushMeshLibrarySingleFacet& baseSingleFacet = WRef(inSelf);
    
	switch (inArgC)
	{
		case 1:
		{
			MushRubyValue param0(inpArgV[0]);				
			if (param0.IsU32())
			{
				baseSingleFacet.OrderSet(param0.U32());
			}
			else if (param0.IsHash())
			{
				Mushware::tRubyHash paramHash = MushRubyValue(inpArgV[0]).Hash();
				for (Mushware::tRubyHash::iterator p = paramHash.begin(); p != paramHash.end(); ++p)
				{
					tRubyID symbol = p->first.Symbol();
					if (symbol == MushRubyIntern::order())
					{
						baseSingleFacet.OrderSet(p->second.U32());
					}
					else
					{
						MushRubyUtil::Raise("Unknown name in parameter hash '"+p->first.String()+"'");	
					}
				}
			}
		}
            break;
			
		default:
			MushRubyUtil::Raise("Wrong parameters to MushBaseSingleFacet.new (must be hash or order value)");
			break;
	}
	
	return inSelf;
}

void
MushMeshRubyBaseSingleFacet::RubyInstall(void)
{
	ObjInstallSubclass("MushBaseSingleFacet", MushMeshRubyBase::Klass());
}

MUSHRUBY_INSTALL(MushMeshRubyBaseSingleFacet);

