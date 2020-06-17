//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyBaseSingleFacet.cpp
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
//%Header } YineEBSc29BYcInSkRyI+A
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

