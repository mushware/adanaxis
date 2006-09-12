//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyBaseWorldSphere.cpp
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
//%Header } r7AZ2pAa13akh7s4qWkeJg
/*
 * $Id$
 * $Log$
 */

#include "MushMeshRubyBaseWorldSphere.h"

#include "MushMeshRubyBase.h"

using namespace Mushware;
using namespace std;

MUSHRUBYOBJ_INSTANCE(MushMeshLibraryWorldSphere);

MUSHRUBYOBJ_INITIALIZE(MushMeshLibraryWorldSphere)(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	MushMeshLibraryWorldSphere& baseWorldSphere = WRef(inSelf);
    
	switch (inArgC)
	{
		case 1:
		{
			MushRubyValue param0(inpArgV[0]);				
			if (param0.IsHash())
			{
				Mushware::tRubyHash paramHash = MushRubyValue(inpArgV[0]).Hash();
				for (Mushware::tRubyHash::iterator p = paramHash.begin(); p != paramHash.end(); ++p)
				{
					tRubyID symbol = p->first.Symbol();
					if (symbol == MushRubyIntern::SymbolID("num_facets"))
					{
						baseWorldSphere.NumFacetsSet(p->second.U32());
					}
					else if (symbol == MushRubyIntern::SymbolID("tiles_per_texture"))
                    {
                        baseWorldSphere.TilesPerTextureSet(p->second.U32());
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
			MushRubyUtil::Raise("Wrong parameters to MushBaseWorldSphere.new (must be hash or order value)");
			break;
	}
	
	return inSelf;
}

void
MushMeshRubyBaseWorldSphere::RubyInstall(void)
{
	ObjInstallSubclass("MushBaseWorldSphere", MushMeshRubyBase::Klass());
}

MUSHRUBY_INSTALL(MushMeshRubyBaseWorldSphere);

