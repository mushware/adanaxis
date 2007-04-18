//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLRubyShader.cpp
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
//%Header } gPsA7OuITFxju7R5mTgNmA
/*
 * $Id: MushGLRubyShader.cpp,v 1.1 2006/09/07 10:02:37 southa Exp $
 * $Log: MushGLRubyShader.cpp,v $
 * Revision 1.1  2006/09/07 10:02:37  southa
 * Shader interface
 *
 */

#include "MushGLRubyShader.h"

MUSHRUBYDATAOBJ_INSTANCE(MushGLShader);

MUSHRUBY_INSTALL(MushGLRubyShader);

using namespace Mushware;
using namespace std;

MUSHRUBYDATAOBJ_INITIALIZE(MushGLShader)(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
    if (inArgC != 1)
    {
        MushRubyUtil::Raise("Wrong number of parameters to MushGLShader.new (must be a hash)");	
    }
    
    Mushware::tRubyHash paramHash = MushRubyValue(inpArgV[0]).Hash();
    
    std::string nameStr = "";
    std::string fragmentShader = "";
    std::string vertexShader = "";
    
    for (Mushware::tRubyHash::iterator p = paramHash.begin(); p != paramHash.end(); ++p)
    {
        tRubyID symbol = p->first.Symbol();
        if (symbol == MushRubyIntern::name())
        {
            nameStr = p->second.String();
        }
        else if (symbol == MushRubyIntern::fragment_shader())
        {
            fragmentShader = p->second.String();
        }
        else if (symbol == MushRubyIntern::vertex_shader())
        {
            vertexShader = p->second.String();
        }
        else
        {
            MushRubyUtil::Raise("Unknown name in parameter hash '"+p->first.String()+"'");	
        }
    }
    
    if (nameStr == "")
    {
        MushRubyUtil::Raise("MushGLShader.new: Missing :name => '<name>' parameter");	
    }
    
	DataObjRef(inSelf).NameSet(nameStr);
	tDataObjData::Sgl().GetOrCreate(nameStr); // Create if it doesn't exist
    
    MushGLShader& objRef = WRef(inSelf);
    
    if (fragmentShader != "")
    {
        objRef.FragmentShaderSet(fragmentShader);
    }
    
    if (vertexShader != "")
    {
        objRef.VertexShaderSet(vertexShader);
    }
    
	return inSelf;
}

Mushware::tRubyValue
MushGLRubyShader::Dump(Mushware::tRubyValue inSelf)
{
	ostringstream message;
    Ref(inSelf).Dump(message);
	return MushRubyValue(message.str()).Value();
}


