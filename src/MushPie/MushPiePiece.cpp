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
 * $Id: MushPiePiece.cpp,v 1.5 2004/01/04 17:02:30 southa Exp $
 * $Log: MushPiePiece.cpp,v $
 * Revision 1.5  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 * Revision 1.4  2004/01/04 14:36:37  southa
 * Handle 'inline' in source conditioner
 *
 * Revision 1.3  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 * Revision 1.2  2004/01/02 17:31:48  southa
 * MushPie work and XML fixes
 *
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
bool
MushPiePiece::AutoEquals(const MushPiePiece& inObj) const
{
    return 1
        && (m_sleepState == inObj.m_sleepState)
    ;
}
void
MushPiePiece::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "sleepState=" << m_sleepState;
    ioOut << "]";
}
bool
MushPiePiece::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "sleepState")
    {
        ioIn >> m_sleepState;
    }
    else
    {
        return false;
    }
    return true;
}
void
MushPiePiece::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("sleepState");
    ioOut << m_sleepState;
}
//%outOfLineFunctions } ycf4SyVlSzuzXZclBSCDmQ
