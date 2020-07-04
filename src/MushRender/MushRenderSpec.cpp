//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderSpec.cpp
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
//%Header } HdBw5cTeD6TAfd1wYwPhNg
/*
 * $Id: MushRenderSpec.cpp,v 1.12 2006/10/06 14:48:19 southa Exp $
 * $Log: MushRenderSpec.cpp,v $
 * Revision 1.12  2006/10/06 14:48:19  southa
 * Material animation
 *
 * Revision 1.11  2006/10/06 11:54:58  southa
 * Scaled rendering
 *
 * Revision 1.10  2006/09/09 11:16:42  southa
 * One-time vertex buffer generation
 *
 * Revision 1.9  2006/06/01 15:39:38  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/09/05 12:54:30  southa
 * Solid rendering work
 *
 * Revision 1.7  2005/07/19 10:06:49  southa
 * Adanaxis work
 *
 * Revision 1.6  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 * Revision 1.5  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 * Revision 1.3  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.2  2005/07/01 16:42:54  southa
 * Render work
 *
 * Revision 1.1  2005/07/01 10:36:46  southa
 * MushRender work
 *
 */

#include "MushRenderSpec.h"

//%outOfLineFunctions {

const char *MushRenderSpec::AutoName(void) const
{
    return "MushRenderSpec";
}

MushcoreVirtualObject *MushRenderSpec::AutoClone(void) const
{
    return new MushRenderSpec(*this);
}

MushcoreVirtualObject *MushRenderSpec::AutoCreate(void) const
{
    return new MushRenderSpec;
}

MushcoreVirtualObject *MushRenderSpec::AutoVirtualFactory(void)
{
    return new MushRenderSpec;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushRenderSpec", MushRenderSpec::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushRenderSpec::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "projection=" << m_projection << ", ";
    ioOut << "view=" << m_view << ", ";
    ioOut << "model=" << m_model << ", ";
    ioOut << "scale=" << m_scale << ", ";
    ioOut << "buffersRef=" << m_buffersRef << ", ";
    ioOut << "sharedBuffersRef=" << m_sharedBuffersRef << ", ";
    ioOut << "useSharedVertices=" << m_useSharedVertices << ", ";
    ioOut << "materialAnimator=" << m_materialAnimator;
    ioOut << "]";
}
bool
MushRenderSpec::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
    else if (inTagStr == "scale")
    {
        ioIn >> m_scale;
    }
    else if (inTagStr == "buffersRef")
    {
        ioIn >> m_buffersRef;
    }
    else if (inTagStr == "sharedBuffersRef")
    {
        ioIn >> m_sharedBuffersRef;
    }
    else if (inTagStr == "useSharedVertices")
    {
        ioIn >> m_useSharedVertices;
    }
    else if (inTagStr == "materialAnimator")
    {
        ioIn >> m_materialAnimator;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushRenderSpec::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("projection");
    ioOut << m_projection;
    ioOut.TagSet("view");
    ioOut << m_view;
    ioOut.TagSet("model");
    ioOut << m_model;
    ioOut.TagSet("scale");
    ioOut << m_scale;
    ioOut.TagSet("buffersRef");
    ioOut << m_buffersRef;
    ioOut.TagSet("sharedBuffersRef");
    ioOut << m_sharedBuffersRef;
    ioOut.TagSet("useSharedVertices");
    ioOut << m_useSharedVertices;
    ioOut.TagSet("materialAnimator");
    ioOut << m_materialAnimator;
}
//%outOfLineFunctions } fRVDNHJ600Qfmor9DNF1jg
