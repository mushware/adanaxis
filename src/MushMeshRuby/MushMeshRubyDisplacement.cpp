//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyDisplacement.cpp
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
//%Header } YJG1Jj52PSAutdFyezJmKw
/*
 * $Id: MushMeshRubyDisplacement.cpp,v 1.5 2006/06/22 19:07:33 southa Exp $
 * $Log: MushMeshRubyDisplacement.cpp,v $
 * Revision 1.5  2006/06/22 19:07:33  southa
 * Build fixes
 *
 * Revision 1.4  2006/06/14 18:45:49  southa
 * Ruby mesh generation
 *
 * Revision 1.3  2006/06/14 11:20:08  southa
 * Ruby mesh generation
 *
 * Revision 1.2  2006/06/13 19:30:37  southa
 * Ruby mesh generation
 *
 * Revision 1.1  2006/06/12 16:01:23  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshRubyDisplacement.h"

#include "MushMeshRubyRotation.h"
#include "MushMeshRubyVector.h"

// #include "MushMeshRubyRuby.h"

using namespace Mushware;
using namespace std;

MUSHRUBYOBJ_INSTANCE(MushMeshDisplacement);

MUSHRUBYOBJ_INITIALIZE(MushMeshDisplacement)(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	MushMeshDisplacement& disp = WRef(inSelf);

	switch (inArgC)
	{
	    case 0:
			disp = MushMeshDisplacement::Identity();
			break;
			
		case 1:
		{		
			disp = MushMeshDisplacement::Identity();
			Mushware::tRubyHash paramHash = MushRubyValue(inpArgV[0]).Hash();
			for (Mushware::tRubyHash::iterator p = paramHash.begin(); p != paramHash.end(); ++p)
			{
				tRubyID symbol = p->first.Symbol();
				if (symbol == MushRubyIntern::offset())
				{
					disp.OffsetSet(MushMeshRubyVector::Ref(p->second.Value()));
				}
				else if (symbol == MushRubyIntern::rotation())
				{
					disp.RotationSet(MushMeshRubyRotation::Ref(p->second.Value()));
				}
				else if (symbol == MushRubyIntern::scale())
				{
					if (MushMeshRubyVector::IsInstanceOf(p->second))
					{
					    disp.ScaleSet(t4Val(MushMeshRubyVector::Ref(p->second.Value())));
					}
					else
					{
					    disp.ScaleSet(p->second.Val());
					}
						
				}
				else
				{
					MushRubyUtil::Raise("Unknown name in parameter hash '"+p->first.String()+"'");	
				}
			}
		}	
		break;
			
		case 3:
		{
			if (!MushMeshRubyVector::IsInstanceOf(inpArgV[0]))
			{
				MushRubyUtil::Raise("First parameter to MushDisplacement.new must be MushVector");
			}
			if (!MushMeshRubyRotation::IsInstanceOf(inpArgV[1]))
			{
				MushRubyUtil::Raise("Second parameter to MushDisplacement.new must be MushRotation");
			}
			MushRubyValue param2(inpArgV[2]);
			
			disp.OffsetSet(MushMeshRubyVector::Ref(inpArgV[0]));
			disp.RotationSet(MushMeshRubyRotation::Ref(inpArgV[1]));
			disp.ScaleSet(param2.Val());
		}		
		break;
			
		default:
			MushRubyUtil::Raise("Wrong number of parameters to MushDisplacement.new(offset, rotation, scale)");
			break;			
	}
	return inSelf;
}

void
MushMeshRubyDisplacement::RubyInstall(void)
{
	ObjInstall("MushDisplacement");
}

MUSHRUBY_INSTALL(MushMeshRubyDisplacement);
