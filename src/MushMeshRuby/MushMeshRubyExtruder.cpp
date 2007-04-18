//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyExtruder.cpp
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
//%Header } LidtXZbDBjuvFRWeOcoY7w
/*
 * $Id: MushMeshRubyExtruder.cpp,v 1.4 2006/06/22 19:07:33 southa Exp $
 * $Log: MushMeshRubyExtruder.cpp,v $
 * Revision 1.4  2006/06/22 19:07:33  southa
 * Build fixes
 *
 * Revision 1.3  2006/06/16 01:02:33  southa
 * Ruby mesh generation
 *
 * Revision 1.2  2006/06/14 18:45:49  southa
 * Ruby mesh generation
 *
 * Revision 1.1  2006/06/14 11:20:08  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshRubyExtruder.h"

#include "MushMeshRubyDisplacement.h"
// #include "MushMeshRubyRuby.h"
#include "MushMeshRubyVector.h"

using namespace Mushware;
using namespace std;

MUSHRUBYOBJ_INSTANCE(MushMeshLibraryExtruder);

MUSHRUBYOBJ_INITIALIZE(MushMeshLibraryExtruder)(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	MushMeshLibraryExtruder& extruder = WRef(inSelf);
    
	switch (inArgC)
	{
		case 0:
			break;
			
		case 1:
		{
			Mushware::tRubyHash paramHash = MushRubyValue(inpArgV[0]).Hash();
			for (Mushware::tRubyHash::iterator p = paramHash.begin(); p != paramHash.end(); ++p)
			{
				tRubyID symbol = p->first.Symbol();
				if (symbol == MushRubyIntern::sourceface())
				{
					extruder.SourceFaceNumSet(p->second.U32());
				}
				else if (symbol == MushRubyIntern::displacement())
				{
					extruder.DispSet(MushMeshRubyDisplacement::Ref(p->second.Value()));
				}
				else if (symbol == MushRubyIntern::displacement_velocity())
				{
					extruder.DispVelSet(MushMeshRubyDisplacement::Ref(p->second.Value()));
				}
				else if (symbol == MushRubyIntern::num_iterations())
				{
					extruder.NumIterationsSet(p->second.U32());
				}
				else if (symbol == MushRubyIntern::to_point())
				{
					extruder.ToPointSet(p->second.Bool());
				}
				else
				{
					MushRubyUtil::Raise("Unknown name in parameter hash '"+p->first.String()+"'");	
				}
			}
		}
		break;
			
		default:
			MushRubyUtil::Raise("Wrong parameters to MushExtruder.new (must be hash)");
			break;
	}
			
	return inSelf;
}

void
MushMeshRubyExtruder::RubyInstall(void)
{
	ObjInstall("MushExtruder");
}

MUSHRUBY_INSTALL(MushMeshRubyExtruder);
