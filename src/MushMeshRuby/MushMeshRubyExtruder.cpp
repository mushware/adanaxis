//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyExtruder.cpp
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
//%Header } TEYiNQetskSyQ90WH7kvfQ
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
