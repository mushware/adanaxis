//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLRubyFont.cpp
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
//%Header } yg6NX73J8HeNsbfghGaUGA
/*
 * $Id: MushGLRubyFont.cpp,v 1.4 2006/11/23 14:40:29 southa Exp $
 * $Log: MushGLRubyFont.cpp,v $
 * Revision 1.4  2006/11/23 14:40:29  southa
 * Intro cutscene
 *
 * Revision 1.3  2006/10/17 20:43:01  southa
 * Dashboard work
 *
 * Revision 1.2  2006/07/08 16:05:58  southa
 * Ruby menus and key handling
 *
 * Revision 1.1  2006/07/02 21:08:54  southa
 * Ruby menu work
 *
 */

#include "MushGLRubyFont.h"

MUSHRUBYDATAOBJ_INSTANCE(MushGLFont);

MUSHRUBY_INSTALL(MushGLRubyFont);

#include "API/mushMushMeshRuby.h"

using namespace Mushware;
using namespace std;

MUSHRUBYDATAOBJ_INITIALIZE(MushGLFont)(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
    if (inArgC != 1)
    {
        MushRubyUtil::Raise("Wrong number of parameters to MushGLFont.new (must be a hash)");	
    }

    Mushware::tRubyHash paramHash = MushRubyValue(inpArgV[0]).Hash();

    std::string nameStr = "";
    std::string textureNameStr = "";

    t2U32 divideVec(1,1);
    t2Val extentVec(1,1);
    t2Val sizeVec(1,1);
    
    bool divideSet = false;
    bool extentSet = false;
    bool sizeSet = false;
    
    for (Mushware::tRubyHash::iterator p = paramHash.begin(); p != paramHash.end(); ++p)
    {
        tRubyID symbol = p->first.Symbol();
        if (symbol == MushRubyIntern::name())
        {
            nameStr = p->second.String();
        }
        else if (symbol == MushRubyIntern::texture_name())
        {
            textureNameStr = p->second.String();
        }
        else if (symbol == MushRubyIntern::divide())
        {
            divideVec = t2U32(p->second.U32Vector());
            divideSet = true;
        }
        else if (symbol == MushRubyIntern::extent())
        {
            extentVec = t2Val(p->second.ValVector());
            extentSet = true;
        }
        else if (symbol == MushRubyIntern::size())
        {
            if (p->second.IsArray())
            {
                sizeVec = t2Val(p->second.ValVector());
            }
            else
            {
                sizeVec = t2Val(p->second.Val(), p->second.Val());
            }
            sizeSet = true;
        }
        else
        {
            MushRubyUtil::Raise("Unknown name in parameter hash '"+p->first.String()+"'");	
        }
    }
    
    if (nameStr == "")
    {
        MushRubyUtil::Raise("MushGLFont.new: Missing :name => '<name>' parameter");	
    }
    
	DataObjRef(inSelf).NameSet(nameStr);
	tDataObjData::Sgl().GetOrCreate(nameStr); // Create if it doesn't exist
    
    MushGLFont& objRef = WRef(inSelf);
    
    if (textureNameStr != "") objRef.TextureNameSet(textureNameStr);
    if (divideSet) objRef.DivideSet(divideVec);
    if (extentSet) objRef.ExtentSet(extentVec);
    if (sizeSet) objRef.SizeSet(sizeVec);
	    
	return inSelf;
}


Mushware::tRubyValue
MushGLRubyFont::Render(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	Ref(inSelf).Render(MushRubyValue(inArg0).String());
	return inSelf;
}

Mushware::tRubyValue
MushGLRubyFont::RenderAt(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0,
                         Mushware::tRubyValue inArg1, Mushware::tRubyValue inArg2)
{
	Ref(inSelf).RenderAt(
                         MushRubyValue(inArg0).String(),
                         t2Val(
                               MushRubyValue(inArg1).Val(),
                               MushRubyValue(inArg2).Val()
                               )
                         );
	return inSelf;
}

Mushware::tRubyValue
MushGLRubyFont::RenderAtSize(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0,
                         Mushware::tRubyValue inArg1, Mushware::tRubyValue inArg2, Mushware::tRubyValue inArg3)
{
    const MushGLFont& fontRef = Ref(inSelf);
	fontRef.RenderAtSize(
                         MushRubyValue(inArg0).String(),
                         t2Val(
                               MushRubyValue(inArg1).Val(),
                               MushRubyValue(inArg2).Val()
                               ),
                         t2Val(
                               MushRubyValue(inArg3).Val(),
                               MushRubyValue(inArg3).Val()
                               )
                         );
	return inSelf;
}

Mushware::tRubyValue
MushGLRubyFont::RenderSymbolAtSize(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0,
    Mushware::tRubyValue inArg1, Mushware::tRubyValue inArg2, Mushware::tRubyValue inArg3)
{
	const MushGLFont& fontRef = Ref(inSelf);
	fontRef.RenderSymbolAtSize(
                             MushRubyValue(inArg0).U32(),
                             t4Val(
                                   MushRubyValue(inArg1).Val(),
                                   MushRubyValue(inArg2).Val(),
                                   0.0,
                                   1.0
                                   ),
                             t2Val(
                                   fontRef.Size().X() * MushRubyValue(inArg3).Val(),
                                   fontRef.Size().Y() * MushRubyValue(inArg3).Val()
                                   )
                             );
	return inSelf;
}



Mushware::tRubyValue
MushGLRubyFont::ColourEquals(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	WRef(inSelf).ColourSet(MushMeshRubyVector::Ref(inArg0));
	return inSelf;
}


