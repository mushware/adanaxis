//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePieceSimple.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 2bfNYCnBe7Dts6IyFoxENQ
/*
 * $Id: MushPiePieceSimple.cpp,v 1.1 2004/01/02 21:13:11 southa Exp $
 * $Log: MushPiePieceSimple.cpp,v $
 * Revision 1.1  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 */

#include "MushPiePieceSimple.h"

//%outOfLineFunctions {
void
MushPiePieceSimple::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushPiePiece::AutoPrint(ioOut);
    ioOut << "angPos=" << m_angPos << ", ";
    ioOut << "angVel=" << m_angVel;
    ioOut << "]";
}
bool
MushPiePieceSimple::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "angPos")
    {
        ioIn >> m_angPos;
    }
    else if (inTagStr == "angVel")
    {
        ioIn >> m_angVel;
    }
    else if (MushPiePiece::AutoXMLDataProcess(ioIn, inTagStr))
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
MushPiePieceSimple::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushPiePiece::AutoXMLPrint(ioOut);
    ioOut.TagSet("angPos");
    ioOut << m_angPos;
    ioOut.TagSet("angVel");
    ioOut << m_angVel;
}
const char *MushPiePieceSimple::AutoNameGet(void) const
{
    return "MushPiePieceSimple";
}
MushPiePieceSimple *MushPiePieceSimple::AutoClone(void) const
{
    return new MushPiePieceSimple(*this);
}
MushPiePieceSimple *MushPiePieceSimple::AutoCreate(void) const
{
    return new MushPiePieceSimple;
}
MushcoreVirtualObject *MushPiePieceSimple::AutoVirtualFactory(void)
{
    return new MushPiePieceSimple;
}
namespace
{
void Install(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushPiePieceSimple", MushPiePieceSimple::AutoVirtualFactory);
}
MushcoreInstaller Installer(Install);
} // end anonymous namespace
//%outOfLineFunctions } c2ZhQ1udZ+pqBaSP0D4VvA
