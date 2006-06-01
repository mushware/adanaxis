//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshDisplacement.cpp
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
//%Header } wVZg6ptzAxvq0Ysg1vHzCw
/*
 * $Id: MushMeshDisplacement.cpp,v 1.1 2005/07/12 20:39:05 southa Exp $
 * $Log: MushMeshDisplacement.cpp,v $
 * Revision 1.1  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 */

#include "MushMeshDisplacement.h"

//%outOfLineFunctions {

const char *MushMeshDisplacement::AutoName(void) const
{
    return "MushMeshDisplacement";
}

MushcoreVirtualObject *MushMeshDisplacement::AutoClone(void) const
{
    return new MushMeshDisplacement(*this);
}

MushcoreVirtualObject *MushMeshDisplacement::AutoCreate(void) const
{
    return new MushMeshDisplacement;
}

MushcoreVirtualObject *MushMeshDisplacement::AutoVirtualFactory(void)
{
    return new MushMeshDisplacement;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMeshDisplacement", MushMeshDisplacement::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMeshDisplacement::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "offset=" << m_offset << ", ";
    ioOut << "rotation=" << m_rotation << ", ";
    ioOut << "scale=" << m_scale;
    ioOut << "]";
}
bool
MushMeshDisplacement::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "offset")
    {
        ioIn >> m_offset;
    }
    else if (inTagStr == "rotation")
    {
        ioIn >> m_rotation;
    }
    else if (inTagStr == "scale")
    {
        ioIn >> m_scale;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushMeshDisplacement::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("offset");
    ioOut << m_offset;
    ioOut.TagSet("rotation");
    ioOut << m_rotation;
    ioOut.TagSet("scale");
    ioOut << m_scale;
}
//%outOfLineFunctions } QpLfeJFjfVzGw6gNjbRU+Q
