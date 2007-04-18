//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameRefPiece.cpp
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
//%Header } Co0IJLhLLStr6Bb/e9IODA
/*
 * $Id: MushGameRefPiece.cpp,v 1.3 2006/06/01 15:39:26 southa Exp $
 * $Log: MushGameRefPiece.cpp,v $
 * Revision 1.3  2006/06/01 15:39:26  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.1  2005/06/29 09:07:56  southa
 * MushGame camera work
 *
 */

#include "MushGameRefPiece.h"

//%outOfLineFunctions {

const char *MushGameRefPiece::AutoName(void) const
{
    return "MushGameRefPiece";
}

MushcoreVirtualObject *MushGameRefPiece::AutoClone(void) const
{
    return new MushGameRefPiece(*this);
}

MushcoreVirtualObject *MushGameRefPiece::AutoCreate(void) const
{
    return new MushGameRefPiece;
}

MushcoreVirtualObject *MushGameRefPiece::AutoVirtualFactory(void)
{
    return new MushGameRefPiece;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameRefPiece", MushGameRefPiece::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameRefPiece::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameRef::AutoPrint(ioOut);
    ioOut << "pieceRef=" << m_pieceRef;
    ioOut << "]";
}
bool
MushGameRefPiece::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "pieceRef")
    {
        ioIn >> m_pieceRef;
    }
    else if (MushGameRef::AutoXMLDataProcess(ioIn, inTagStr))
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
MushGameRefPiece::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameRef::AutoXMLPrint(ioOut);
    ioOut.TagSet("pieceRef");
    ioOut << m_pieceRef;
}
//%outOfLineFunctions } g3D5qPrkMolOUeAya1U8Vw
