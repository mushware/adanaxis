//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLRubyShader.cpp
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
//%Header } dvX1zNvYXusfJXX+aufacQ
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


