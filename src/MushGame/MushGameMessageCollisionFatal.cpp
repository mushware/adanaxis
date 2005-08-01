//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageCollisionFatal.cpp
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
//%Header } CshWGlblieIk6ihSs7/OQQ
/*
 * $Id$
 * $Log$
 */

#include "MushGameMessageCollisionFatal.h"

//%outOfLineFunctions {

const char *MushGameMessageCollisionFatal::AutoName(void) const
{
    return "MushGameMessageCollisionFatal";
}

MushcoreVirtualObject *MushGameMessageCollisionFatal::AutoClone(void) const
{
    return new MushGameMessageCollisionFatal(*this);
}

MushcoreVirtualObject *MushGameMessageCollisionFatal::AutoCreate(void) const
{
    return new MushGameMessageCollisionFatal;
}

MushcoreVirtualObject *MushGameMessageCollisionFatal::AutoVirtualFactory(void)
{
    return new MushGameMessageCollisionFatal;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMessageCollisionFatal", MushGameMessageCollisionFatal::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMessageCollisionFatal::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameMessageCollision::AutoPrint(ioOut);
    ioOut << "post1=" << m_post1 << ", ";
    ioOut << "post2=" << m_post2 << ", ";
    ioOut << "chunkNum1=" << m_chunkNum1 << ", ";
    ioOut << "chunkNum2=" << m_chunkNum2 << ", ";
    ioOut << "chunkNumsValid=" << m_chunkNumsValid;
    ioOut << "]";
}
bool
MushGameMessageCollisionFatal::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "post1")
    {
        ioIn >> m_post1;
    }
    else if (inTagStr == "post2")
    {
        ioIn >> m_post2;
    }
    else if (inTagStr == "chunkNum1")
    {
        ioIn >> m_chunkNum1;
    }
    else if (inTagStr == "chunkNum2")
    {
        ioIn >> m_chunkNum2;
    }
    else if (inTagStr == "chunkNumsValid")
    {
        ioIn >> m_chunkNumsValid;
    }
    else if (MushGameMessageCollision::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameMessageCollisionFatal::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameMessageCollision::AutoXMLPrint(ioOut);
    ioOut.TagSet("post1");
    ioOut << m_post1;
    ioOut.TagSet("post2");
    ioOut << m_post2;
    ioOut.TagSet("chunkNum1");
    ioOut << m_chunkNum1;
    ioOut.TagSet("chunkNum2");
    ioOut << m_chunkNum2;
    ioOut.TagSet("chunkNumsValid");
    ioOut << m_chunkNumsValid;
}
//%outOfLineFunctions } XG0W1PQyMPpwJLRKEO3QXg
