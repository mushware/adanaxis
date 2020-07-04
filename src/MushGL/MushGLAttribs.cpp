//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLAttribs.cpp
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
//%Header } sjj3qzVNVWk6cwjEifNVYA
/*
 * $Id: MushGLAttribs.cpp,v 1.3 2006/09/10 10:30:52 southa Exp $
 * $Log: MushGLAttribs.cpp,v $
 * Revision 1.3  2006/09/10 10:30:52  southa
 * Shader billboarding
 *
 * Revision 1.2  2006/09/09 15:59:27  southa
 * Shader colour calculations
 *
 * Revision 1.1  2006/09/07 16:38:50  southa
 * Vertex shader
 *
 */

#include "MushGLAttribs.h"

//%outOfLineFunctions {

const char *MushGLAttribs::AutoName(void) const
{
    return "MushGLAttribs";
}

MushcoreVirtualObject *MushGLAttribs::AutoClone(void) const
{
    return new MushGLAttribs(*this);
}

MushcoreVirtualObject *MushGLAttribs::AutoCreate(void) const
{
    return new MushGLAttribs;
}

MushcoreVirtualObject *MushGLAttribs::AutoVirtualFactory(void)
{
    return new MushGLAttribs;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLAttribs", MushGLAttribs::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLAttribs::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "projection=" << m_projection << ", ";
    ioOut << "view=" << m_view << ", ";
    ioOut << "model=" << m_model << ", ";
    ioOut << "colours=" << m_colours << ", ";
    ioOut << "transformType=" << m_transformType;
    ioOut << "]";
}
bool
MushGLAttribs::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "projection")
    {
        ioIn >> m_projection;
    }
    else if (inTagStr == "view")
    {
        ioIn >> m_view;
    }
    else if (inTagStr == "model")
    {
        ioIn >> m_model;
    }
    else if (inTagStr == "colours")
    {
        ioIn >> m_colours;
    }
    else if (inTagStr == "transformType")
    {
        ioIn >> m_transformType;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLAttribs::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("projection");
    ioOut << m_projection;
    ioOut.TagSet("view");
    ioOut << m_view;
    ioOut.TagSet("model");
    ioOut << m_model;
    ioOut.TagSet("colours");
    ioOut << m_colours;
    ioOut.TagSet("transformType");
    ioOut << m_transformType;
}
//%outOfLineFunctions } CnfxFvPT66gzWgev1T4YHA
