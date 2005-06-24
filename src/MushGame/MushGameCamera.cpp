//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameCamera.cpp
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
//%Header } n4I3T2aUdqYB2n1/b+c3Kg
/*
 * $Id$
 * $Log$
 */

#include "MushGameCamera.h"

MushGameCamera::MushGameCamera()
{
}

//%outOfLineFunctions {

const char *MushGameCamera::AutoName(void) const
{
    return "MushGameCamera";
}

MushcoreVirtualObject *MushGameCamera::AutoClone(void) const
{
    return new MushGameCamera(*this);
}

MushcoreVirtualObject *MushGameCamera::AutoCreate(void) const
{
    return new MushGameCamera;
}

MushcoreVirtualObject *MushGameCamera::AutoVirtualFactory(void)
{
    return new MushGameCamera;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameCamera", MushGameCamera::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameCamera::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "tiedPieceRef=" << m_tiedPieceRef << ", ";
    ioOut << "tiedPlayerRef=" << m_tiedPlayerRef;
    ioOut << "]";
}
bool
MushGameCamera::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "tiedPieceRef")
    {
        ioIn >> m_tiedPieceRef;
    }
    else if (inTagStr == "tiedPlayerRef")
    {
        ioIn >> m_tiedPlayerRef;
    }
    else
    {
        return false;
    }
    return true;
}
void
MushGameCamera::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("tiedPieceRef");
    ioOut << m_tiedPieceRef;
    ioOut.TagSet("tiedPlayerRef");
    ioOut << m_tiedPlayerRef;
}
//%outOfLineFunctions } sILENq5kDNWntwJb/rp+5w
