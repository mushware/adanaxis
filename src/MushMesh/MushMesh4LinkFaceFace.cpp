//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4LinkFaceFace.cpp
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
//%Header } DTHuiPjKCqIb+liUmePGbA
/*
 * $Id: MushMesh4LinkFaceFace.cpp,v 1.2 2006/06/01 15:39:28 southa Exp $
 * $Log: MushMesh4LinkFaceFace.cpp,v $
 * Revision 1.2  2006/06/01 15:39:28  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/13 16:45:05  southa
 * Extrusion work
 *
 */

#include "MushMesh4LinkFaceFace.h"

//%outOfLineFunctions {

const char *MushMesh4LinkFaceFace::AutoName(void) const
{
    return "MushMesh4LinkFaceFace";
}

MushcoreVirtualObject *MushMesh4LinkFaceFace::AutoClone(void) const
{
    return new MushMesh4LinkFaceFace(*this);
}

MushcoreVirtualObject *MushMesh4LinkFaceFace::AutoCreate(void) const
{
    return new MushMesh4LinkFaceFace;
}

MushcoreVirtualObject *MushMesh4LinkFaceFace::AutoVirtualFactory(void)
{
    return new MushMesh4LinkFaceFace;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMesh4LinkFaceFace", MushMesh4LinkFaceFace::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMesh4LinkFaceFace::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "faceNum=" << m_faceNum << ", ";
    ioOut << "localFacetNum=" << m_localFacetNum << ", ";
    ioOut << "remoteFacetNum=" << m_remoteFacetNum;
    ioOut << "]";
}
bool
MushMesh4LinkFaceFace::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "faceNum")
    {
        ioIn >> m_faceNum;
    }
    else if (inTagStr == "localFacetNum")
    {
        ioIn >> m_localFacetNum;
    }
    else if (inTagStr == "remoteFacetNum")
    {
        ioIn >> m_remoteFacetNum;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushMesh4LinkFaceFace::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("faceNum");
    ioOut << m_faceNum;
    ioOut.TagSet("localFacetNum");
    ioOut << m_localFacetNum;
    ioOut.TagSet("remoteFacetNum");
    ioOut << m_remoteFacetNum;
}
//%outOfLineFunctions } isdI6Z0tdgU7swE/2Nkojw
