//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameCamera.cpp
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
//%Header } JwGK0YFCvLvhXQNIhU/jng
/*
 * $Id: MushGameCamera.cpp,v 1.7 2006/07/24 18:46:50 southa Exp $
 * $Log: MushGameCamera.cpp,v $
 * Revision 1.7  2006/07/24 18:46:50  southa
 * Depth sorting
 *
 * Revision 1.6  2006/06/01 15:39:20  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.3  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 * Revision 1.2  2005/06/29 09:07:56  southa
 * MushGame camera work
 *
 * Revision 1.1  2005/06/24 10:30:12  southa
 * MushGame camera work
 *
 */

#include "MushGameCamera.h"

MushGameCamera::MushGameCamera() :
    m_pTiedRef(NULL)
{
        PostWRef().ToIdentitySet();
}

const MushGameCamera&
MushGameCamera::operator=(const MushGameCamera& inCamera)
{
    if (this != &inCamera)
    {
        MushGameCamera tempObj(inCamera);
        std::swap(tempObj, *this);
    }
    return *this;
}

MushGameCamera::~MushGameCamera()
{
    if (m_pTiedRef != NULL)
    {
        delete m_pTiedRef;
    }
}

void
MushGameCamera::FromTiedObjectUpdate(void)
{
    if (m_pTiedRef == NULL)
    {
        throw MushcoreDataFail(std::string(AutoName())+": No tied object to update from");
    }
    MushGamePiece *pPiece = dynamic_cast<MushGamePiece *>(&m_pTiedRef->Ref());
    if (pPiece == NULL)
    {
        throw MushcoreDataFail(std::string(AutoName())+": Tied object of wrong type");
    }
    PostSet(pPiece->Post());
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
    MushGLCamera::AutoPrint(ioOut);
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
    else if (MushGLCamera::AutoXMLDataProcess(ioIn, inTagStr))
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
MushGameCamera::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGLCamera::AutoXMLPrint(ioOut);
    ioOut.TagSet("pTiedRef");
    ioOut << m_pTiedRef;
}
//%outOfLineFunctions } Lskz4OegNj5RsVWxixrr3A
