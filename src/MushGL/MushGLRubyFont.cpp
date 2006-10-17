//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLRubyFont.cpp
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
//%Header } x7wDRgXhtyz4ur55Gakesw
/*
 * $Id: MushGLRubyFont.cpp,v 1.2 2006/07/08 16:05:58 southa Exp $
 * $Log: MushGLRubyFont.cpp,v $
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
	Ref(inSelf).RenderAtSize(
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
	Ref(inSelf).RenderSymbolAtSize(
                             MushRubyValue(inArg0).U32(),
                             t4Val(
                                   MushRubyValue(inArg1).Val(),
                                   MushRubyValue(inArg2).Val(),
                                   0.0,
                                   1.0
                                   ),
                             t2Val(
                                   MushRubyValue(inArg3).Val(),
                                   MushRubyValue(inArg3).Val()
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


