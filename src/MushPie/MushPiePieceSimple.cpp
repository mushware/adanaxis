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
 * $Id$
 * $Log$
 */

#include "MushPiePieceSimple.h"

//%outOfLineFunctions {
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
void
MushPiePieceSimple::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushPiePiece::AutoPrint(ioOut);
    ioOut << "angle=" << m_angle << ", ";
    ioOut << "angularVel=" << m_angularVel;
    ioOut << "]";
}
bool
MushPiePieceSimple::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "angle")
    {
        ioIn >> m_angle;
    }
    else if (inTagStr == "angularVel")
    {
        ioIn >> m_angularVel;
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
    ioOut.TagSet("angle");
    ioOut << m_angle;
    ioOut.TagSet("angularVel");
    ioOut << m_angularVel;
}
//%outOfLineFunctions } YtZc5zcCzF9edO+0iruA6Q
