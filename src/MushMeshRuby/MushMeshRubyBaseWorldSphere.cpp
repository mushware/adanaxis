//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyBaseWorldSphere.cpp
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
//%Header } 1789lqzsB1dsn0Xxyv5u+g
/*
 * $Id: MushMeshRubyBaseWorldSphere.cpp,v 1.1 2006/09/12 15:28:50 southa Exp $
 * $Log: MushMeshRubyBaseWorldSphere.cpp,v $
 * Revision 1.1  2006/09/12 15:28:50  southa
 * World sphere
 *
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

