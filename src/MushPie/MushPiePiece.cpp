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
 * $Id: MushPiePiece.cpp,v 1.1 2004/01/02 11:57:47 southa Exp $
 * $Log: MushPiePiece.cpp,v $
 * Revision 1.1  2004/01/02 11:57:47  southa
 * Created
 *
 */

#include "MushPiePiece.h"

using namespace Mushware;

void
operator>>(MushcoreXMLIStream& ioIn, MushPiePiece::tSleepState& outObj)
{
    U32 value;
    ioIn >> value;
    outObj = static_cast<MushPiePiece::tSleepState>(value);
}

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
    ioOut << "velocity=" << m_velocity << ", ";
    ioOut << "sleepState=" << m_sleepState << ", ";
    ioOut << "templateRef=" << m_templateRef;
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
    else if (inTagStr == "sleepState")
    {
        ioIn >> m_sleepState;
    }
    else if (inTagStr == "templateRef")
    {
        ioIn >> m_templateRef;
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
    ioOut.TagSet("sleepState");
    ioOut << m_sleepState;
    ioOut.TagSet("templateRef");
    ioOut << m_templateRef;
}
//%outOfLineFunctions } Oa3RP8cuKnW//vNLvPENFg
