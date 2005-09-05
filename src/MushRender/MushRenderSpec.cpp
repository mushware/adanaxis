//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderSpec.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } XttDYnY7xVQ0Mej3+yO1wQ
/*
 * $Id: MushRenderSpec.cpp,v 1.7 2005/07/19 10:06:49 southa Exp $
 * $Log: MushRenderSpec.cpp,v $
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
    ioOut << "buffersRef=" << m_buffersRef << ", ";
    ioOut << "texCoordBuffersRef=" << m_texCoordBuffersRef;
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
    else if (inTagStr == "buffersRef")
    {
        ioIn >> m_buffersRef;
    }
    else if (inTagStr == "texCoordBuffersRef")
    {
        ioIn >> m_texCoordBuffersRef;
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
    ioOut.TagSet("buffersRef");
    ioOut << m_buffersRef;
    ioOut.TagSet("texCoordBuffersRef");
    ioOut << m_texCoordBuffersRef;
}
//%outOfLineFunctions } hJfvaIu1NSVJSmMIuZl91g
