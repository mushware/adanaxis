//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePieceMobile.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } yQV718sdUzJEMF7KFdA6Ew
/*
 * $Id: MushPiePieceMobile.cpp,v 1.4 2005/02/01 13:40:37 southa Exp $
 * $Log: MushPiePieceMobile.cpp,v $
 * Revision 1.4  2005/02/01 13:40:37  southa
 * Rotating spheres and hypercube
 *
 * Revision 1.3  2004/09/27 22:42:10  southa
 * MSVC compilation fixes
 *
 * Revision 1.2  2004/01/06 00:34:56  southa
 * MushPie testing
 *
 * Revision 1.1  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 */

#include "MushPiePieceMobile.h"

MushPiePieceMobile::MushPiePieceMobile() :
    m_currentPosIndex(0), 
    m_newPosIndex(1) 
{
}



//%outOfLineFunctions {

const char *MushPiePieceMobile::AutoNameGet(void) const
{
    return "MushPiePieceMobile";
}

MushcoreVirtualObject *MushPiePieceMobile::AutoClone(void) const
{
    return new MushPiePieceMobile(*this);
}

MushcoreVirtualObject *MushPiePieceMobile::AutoCreate(void) const
{
    return new MushPiePieceMobile;
}

MushcoreVirtualObject *MushPiePieceMobile::AutoVirtualFactory(void)
{
    return new MushPiePieceMobile;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushPiePieceMobile", MushPiePieceMobile::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushPiePieceMobile::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushPiePiece::AutoPrint(ioOut);
    ioOut << "pos0=" << m_pos0 << ", ";
    ioOut << "pos1=" << m_pos1 << ", ";
    ioOut << "currentPosIndex=" << m_currentPosIndex << ", ";
    ioOut << "newPosIndex=" << m_newPosIndex;
    ioOut << "]";
}
bool
MushPiePieceMobile::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "pos0")
    {
        ioIn >> m_pos0;
    }
    else if (inTagStr == "pos1")
    {
        ioIn >> m_pos1;
    }
    else if (inTagStr == "currentPosIndex")
    {
        ioIn >> m_currentPosIndex;
    }
    else if (inTagStr == "newPosIndex")
    {
        ioIn >> m_newPosIndex;
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
MushPiePieceMobile::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushPiePiece::AutoXMLPrint(ioOut);
    ioOut.TagSet("pos0");
    ioOut << m_pos0;
    ioOut.TagSet("pos1");
    ioOut << m_pos1;
    ioOut.TagSet("currentPosIndex");
    ioOut << m_currentPosIndex;
    ioOut.TagSet("newPosIndex");
    ioOut << m_newPosIndex;
}
//%outOfLineFunctions } qq52mgjwReQpZLCl4JoYDQ
