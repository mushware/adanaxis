//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePiece.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } yFpbFvl0kLTLgwf8WZnbZA
/*
 * $Id$
 * $Log$
 */

#include "MushPiePiece.h"


//%outOfLineFunctions {
const char *MushPiePiece::AutoNameGet(void) const
{
    return "MushPiePiece";
}
MushPiePiece *MushPiePiece::AutoClone(void) const
{
    return new MushPiePiece(*this);
}
MushPiePiece *MushPiePiece::AutoCreate(void) const
{
    return new MushPiePiece;
}
MushcoreVirtualObject *MushPiePiece::AutoVirtualFactory(void)
{
    return new MushPiePiece;
}
namespace
{
void Install(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushPiePiece", MushPiePiece::AutoVirtualFactory);
}
MushcoreInstaller Installer(Install);
} // end anonymous namespace
void
MushPiePiece::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "position=" << m_position << ", ";
    ioOut << "velocity=" << m_velocity;
    ioOut << "]";
}
void
MushPiePiece::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "position")
    {
        ioIn >> m_position;
    }
    else if (inTagStr == "velocity")
    {
        ioIn >> m_velocity;
    }
    else
    {
        ioIn.Throw("Unrecognised tag '"+inTagStr+"'");
    }
}
void
MushPiePiece::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("position");
    ioOut << m_position;
    ioOut.TagSet("velocity");
    ioOut << m_velocity;
}
//%outOfLineFunctions } v9XBXIFMkQR4JR6Agt36Og
