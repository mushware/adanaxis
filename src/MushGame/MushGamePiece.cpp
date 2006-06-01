//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGamePiece.cpp
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
//%Header } rVCNunlW+wZoonHnGB5a7Q
/*
 * $Id: MushGamePiece.cpp,v 1.5 2005/07/06 19:08:27 southa Exp $
 * $Log: MushGamePiece.cpp,v $
 * Revision 1.5  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 * Revision 1.4  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.3  2005/07/01 16:42:54  southa
 * Render work
 *
 * Revision 1.2  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 * Revision 1.1  2005/06/24 10:30:12  southa
 * MushGame camera work
 *
 */

#include "MushGamePiece.h"

#include "MushGameMessage.h"

MUSHCORE_DATA_INSTANCE(MushGamePiece);

MushGamePiece::MushGamePiece()
{
    m_post.ToIdentitySet();
}

void
MushGamePiece::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    throw MushcoreDataFail(std::string("Unhandled message type ")+inMessage.AutoName()+" in "+AutoName());
}

//%outOfLineFunctions {

const char *MushGamePiece::AutoName(void) const
{
    return "MushGamePiece";
}

MushcoreVirtualObject *MushGamePiece::AutoClone(void) const
{
    return new MushGamePiece(*this);
}

MushcoreVirtualObject *MushGamePiece::AutoCreate(void) const
{
    return new MushGamePiece;
}

MushcoreVirtualObject *MushGamePiece::AutoVirtualFactory(void)
{
    return new MushGamePiece;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGamePiece", MushGamePiece::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGamePiece::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "post=" << m_post;
    ioOut << "]";
}
bool
MushGamePiece::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "post")
    {
        ioIn >> m_post;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGamePiece::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("post");
    ioOut << m_post;
}
//%outOfLineFunctions } FmY+VRhBiBMRCR5fji3QdQ
