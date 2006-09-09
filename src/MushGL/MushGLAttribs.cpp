//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLAttribs.cpp
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
//%Header } FFnhuXNalVWlRhcCSD56vg
/*
 * $Id: MushGLAttribs.cpp,v 1.1 2006/09/07 16:38:50 southa Exp $
 * $Log: MushGLAttribs.cpp,v $
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
    ioOut << "colours=" << m_colours;
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
}
//%outOfLineFunctions } VoeCR+oz77E41igfj6cjDA
