//%Header {
/*****************************************************************************
 *
 * File: src/MushModel/MushModelFacet.cpp
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
//%Header } QlzNTBK7+p5K+Ow89oenmA
/*
 * $Id: MushModelFacet.cpp,v 1.8 2006/06/01 15:39:35 southa Exp $
 * $Log: MushModelFacet.cpp,v $
 * Revision 1.8  2006/06/01 15:39:35  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.6  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.5  2005/06/16 17:25:39  southa
 * Client/server work
 *
 * Revision 1.4  2005/05/19 13:02:12  southa
 * Mac release work
 *
 * Revision 1.3  2005/02/10 12:34:08  southa
 * Template fixes
 *
 * Revision 1.2  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
 * Revision 1.1  2004/01/07 18:01:18  southa
 * MushModel and Infernal work
 *
 */

#include "MushModelFacet.h"

#include "MushModelIO.h"

//%outOfLineFunctions {

const char *MushModelFacet::AutoName(void) const
{
    return "MushModelFacet";
}

MushcoreVirtualObject *MushModelFacet::AutoClone(void) const
{
    return new MushModelFacet(*this);
}

MushcoreVirtualObject *MushModelFacet::AutoCreate(void) const
{
    return new MushModelFacet;
}

MushcoreVirtualObject *MushModelFacet::AutoVirtualFactory(void)
{
    return new MushModelFacet;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushModelFacet", MushModelFacet::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushModelFacet::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "renderType=" << m_renderType << ", ";
    ioOut << "materialRef=" << m_materialRef << ", ";
    ioOut << "vertices=" << m_vertices << ", ";
    ioOut << "texCoords=" << m_texCoords << ", ";
    ioOut << "normals=" << m_normals;
    ioOut << "]";
}
bool
MushModelFacet::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "renderType")
    {
        ioIn >> m_renderType;
    }
    else if (inTagStr == "materialRef")
    {
        ioIn >> m_materialRef;
    }
    else if (inTagStr == "vertices")
    {
        ioIn >> m_vertices;
    }
    else if (inTagStr == "texCoords")
    {
        ioIn >> m_texCoords;
    }
    else if (inTagStr == "normals")
    {
        ioIn >> m_normals;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushModelFacet::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("renderType");
    ioOut << m_renderType;
    ioOut.TagSet("materialRef");
    ioOut << m_materialRef;
    ioOut.TagSet("vertices");
    ioOut << m_vertices;
    ioOut.TagSet("texCoords");
    ioOut << m_texCoords;
    ioOut.TagSet("normals");
    ioOut << m_normals;
}
//%outOfLineFunctions } yKowFzH8cvRWU3a++x6pOQ
