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
 * $Id: MushRenderSpec.cpp,v 1.3 2005/07/02 00:42:38 southa Exp $
 * $Log: MushRenderSpec.cpp,v $
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
    ioOut << "buffersRef=" << m_buffersRef;
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
    else if (inTagStr == "buffersRef")
    {
        ioIn >> m_buffersRef;
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
    ioOut.TagSet("buffersRef");
    ioOut << m_buffersRef;
}
//%outOfLineFunctions } JpalBjzD3uCwsNNCGmWIGA
