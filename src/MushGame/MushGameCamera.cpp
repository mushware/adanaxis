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
 * $Id: MushGameCamera.cpp,v 1.1 2005/06/24 10:30:12 southa Exp $
 * $Log: MushGameCamera.cpp,v $
 * Revision 1.1  2005/06/24 10:30:12  southa
 * MushGame camera work
 *
 */

#include "MushGameCamera.h"

MushGameCamera::MushGameCamera() :
    m_pTiedRef(NULL)
{
}

MushGameCamera::~MushGameCamera()
{
    if (m_pTiedRef != NULL)
    {
        delete m_pTiedRef;
    }
}

void
MushGameCamera::TiedRefCopy(MushGameRef *inpRef)
{
    m_pTiedRef = dynamic_cast<MushGameRef *>(inpRef->AutoClone());
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
    if (m_pTiedRef == NULL)
    {
        ioOut << "pTiedRef=NULL" ;
    }
    else
    {
        ioOut << "pTiedRef=" << *m_pTiedRef;
    }
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
    else if (inTagStr == "pTiedRef")
    {
        ioIn >> m_pTiedRef;
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
    ioOut.TagSet("pTiedRef");
    ioOut << m_pTiedRef;
}
//%outOfLineFunctions } asC+Zd9beEpR3oQsIFTtKw
