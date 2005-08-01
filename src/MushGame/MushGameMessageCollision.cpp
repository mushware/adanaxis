//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageCollision.cpp
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
//%Header } K4+nipImYcVKzuloQY9QIA
/*
 * $Id$
 * $Log$
 */

#include "MushGameMessageCollision.h"

//%outOfLineFunctions {

const char *MushGameMessageCollision::AutoName(void) const
{
    return "MushGameMessageCollision";
}

MushcoreVirtualObject *MushGameMessageCollision::AutoClone(void) const
{
    return new MushGameMessageCollision(*this);
}

MushcoreVirtualObject *MushGameMessageCollision::AutoCreate(void) const
{
    return new MushGameMessageCollision;
}

MushcoreVirtualObject *MushGameMessageCollision::AutoVirtualFactory(void)
{
    return new MushGameMessageCollision;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMessageCollision", MushGameMessageCollision::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMessageCollision::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameMessage::AutoPrint(ioOut);
    ioOut << "objectName1=" << m_objectName1 << ", ";
    ioOut << "objectName2=" << m_objectName2;
    ioOut << "]";
}
bool
MushGameMessageCollision::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "objectName1")
    {
        ioIn >> m_objectName1;
    }
    else if (inTagStr == "objectName2")
    {
        ioIn >> m_objectName2;
    }
    else if (MushGameMessage::AutoXMLDataProcess(ioIn, inTagStr))
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
MushGameMessageCollision::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameMessage::AutoXMLPrint(ioOut);
    ioOut.TagSet("objectName1");
    ioOut << m_objectName1;
    ioOut.TagSet("objectName2");
    ioOut << m_objectName2;
}
//%outOfLineFunctions } l77vGaz2kQ8/zCVV6/Agwg
