//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyBasePrism.cpp
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
//%Header } 2785xynkrUkq+TkP8aYNHg
/*
 * $Id: MushMeshRubyBasePrism.cpp,v 1.2 2006/06/16 12:11:04 southa Exp $
 * $Log: MushMeshRubyBasePrism.cpp,v $
 * Revision 1.2  2006/06/16 12:11:04  southa
 * Ruby subclasses
 *
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

