//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyDisplacement.cpp
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
//%Header } wt1yJZnIr9M7T5DwI0rLOg
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
