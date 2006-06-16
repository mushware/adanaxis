//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyBasePrism.cpp
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
//%Header } ceyqk6w3RyXgPXeMYSSUcQ
/*
 * $Id: MushMeshRubyBasePrism.cpp,v 1.1 2006/06/16 01:02:33 southa Exp $
 * $Log: MushMeshRubyBasePrism.cpp,v $
 * Revision 1.1  2006/06/16 01:02:33  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshRubyBasePrism.h"

#include "MushMeshRubyBase.h"

using namespace Mushware;
using namespace std;

MUSHRUBYOBJ_INSTANCE(MushMeshLibraryPrism);

MUSHRUBYOBJ_INITIALIZE(MushMeshLibraryPrism)(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	MushMeshLibraryPrism& basePrism = WRef(inSelf);
    
	switch (inArgC)
	{
		case 1:
		{
			MushRubyValue param0(inpArgV[0]);				
			if (param0.IsU32())
			{
				basePrism.OrderSet(param0.U32());
			}
			else if (param0.IsHash())
			{
				Mushware::tRubyHash paramHash = MushRubyValue(inpArgV[0]).Hash();
				for (Mushware::tRubyHash::iterator p = paramHash.begin(); p != paramHash.end(); ++p)
				{
					tRubyID symbol = p->first.Symbol();
					if (symbol == MushRubyIntern::order())
					{
						basePrism.OrderSet(p->second.U32());
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
			MushRubyUtil::Raise("Wrong parameters to MushBasePrism.new (must be hash or order value)");
			break;
	}
	
	return inSelf;
}

void
MushMeshRubyBasePrism::RubyInstall(void)
{
	ObjInstallSubclass("MushBasePrism", MushMeshRubyBase::Klass());
}

MUSHRUBY_INSTALL(MushMeshRubyBasePrism);

