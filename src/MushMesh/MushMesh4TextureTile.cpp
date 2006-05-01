//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4TextureTile.cpp
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
//%Header } 1kCIwS/JA8VtB31OUyUq8Q
/*
 * $Id$
 * $Log$
 */

#include "MushMesh4TextureTile.h"

using namespace Mushware;
using namespace std;

void
MushMesh4TextureTile::Make(void)
{
    tVal u0 = m_tileP0.X();
    tVal v0 = m_tileP0.Y();
    tVal u1 = m_tileV0.X();
    tVal v1 = m_tileV0.Y();
    tVal u2 = m_tileV1.X();
    tVal v2 = m_tileV1.Y();
    
    if (u2*v1 == u1*v2)
    {
        throw MushcoreDataFail("Colinear vector in texture tile");
    }
    
    m_constant = m_objectP0 +
        m_objectV0 * ((u0*v2 - u2*v0) / (u2*v1 - u1*v2)) +
        m_objectV1 * ((u0*v1 - u1*v0) / (u1*v2 - u2*v1));
    
    m_uFactor = m_objectV0 * (v2 / (u1*v2 - u2*v1)) -
                m_objectV1 * (v1 / (u1*v2 - u2*v1));
                       
    m_vFactor = m_objectV0 * (u2 / (u2*v1 - u1*v2)) -
                m_objectV1 * (u1 / (u2*v1 - u1*v2));
    
    if (std::fabs(u2*v1 - u1*v2) < 1e-6)
    {
        MushcoreLog::Sgl().WarningLog() << "Ill-conditioned texture tile" << std::endl;
    }    
}

//%outOfLineFunctions {

const char *MushMesh4TextureTile::AutoName(void) const
{
    return "MushMesh4TextureTile";
}

MushcoreVirtualObject *MushMesh4TextureTile::AutoClone(void) const
{
    return new MushMesh4TextureTile(*this);
}

MushcoreVirtualObject *MushMesh4TextureTile::AutoCreate(void) const
{
    return new MushMesh4TextureTile;
}

MushcoreVirtualObject *MushMesh4TextureTile::AutoVirtualFactory(void)
{
    return new MushMesh4TextureTile;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMesh4TextureTile", MushMesh4TextureTile::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMesh4TextureTile::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "tileBox=" << m_tileBox << ", ";
    ioOut << "tileP0=" << m_tileP0 << ", ";
    ioOut << "tileV0=" << m_tileV0 << ", ";
    ioOut << "tileV1=" << m_tileV1 << ", ";
    ioOut << "objectP0=" << m_objectP0 << ", ";
    ioOut << "objectV0=" << m_objectV0 << ", ";
    ioOut << "objectV1=" << m_objectV1 << ", ";
    ioOut << "constant=" << m_constant << ", ";
    ioOut << "uFactor=" << m_uFactor << ", ";
    ioOut << "vFactor=" << m_vFactor;
    ioOut << "]";
}
bool
MushMesh4TextureTile::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "tileBox")
    {
        ioIn >> m_tileBox;
    }
    else if (inTagStr == "tileP0")
    {
        ioIn >> m_tileP0;
    }
    else if (inTagStr == "tileV0")
    {
        ioIn >> m_tileV0;
    }
    else if (inTagStr == "tileV1")
    {
        ioIn >> m_tileV1;
    }
    else if (inTagStr == "objectP0")
    {
        ioIn >> m_objectP0;
    }
    else if (inTagStr == "objectV0")
    {
        ioIn >> m_objectV0;
    }
    else if (inTagStr == "objectV1")
    {
        ioIn >> m_objectV1;
    }
    else if (inTagStr == "constant")
    {
        ioIn >> m_constant;
    }
    else if (inTagStr == "uFactor")
    {
        ioIn >> m_uFactor;
    }
    else if (inTagStr == "vFactor")
    {
        ioIn >> m_vFactor;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushMesh4TextureTile::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("tileBox");
    ioOut << m_tileBox;
    ioOut.TagSet("tileP0");
    ioOut << m_tileP0;
    ioOut.TagSet("tileV0");
    ioOut << m_tileV0;
    ioOut.TagSet("tileV1");
    ioOut << m_tileV1;
    ioOut.TagSet("objectP0");
    ioOut << m_objectP0;
    ioOut.TagSet("objectV0");
    ioOut << m_objectV0;
    ioOut.TagSet("objectV1");
    ioOut << m_objectV1;
    ioOut.TagSet("constant");
    ioOut << m_constant;
    ioOut.TagSet("uFactor");
    ioOut << m_uFactor;
    ioOut.TagSet("vFactor");
    ioOut << m_vFactor;
}
//%outOfLineFunctions } h8ugTCmO6zwfvFqYr+TEOA
