//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePosicity.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 0niOQpG0nEHxTZPccDWOjQ
/*
 * $Id: MushPiePosicity.cpp,v 1.3 2004/01/08 22:41:10 southa Exp $
 * $Log: MushPiePosicity.cpp,v $
 * Revision 1.3  2004/01/08 22:41:10  southa
 * MushModel commands
 *
 * Revision 1.2  2004/01/06 00:34:56  southa
 * MushPie testing
 *
 * Revision 1.1  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 */

#include "MushPiePosicity.h"

using namespace Mushware;

//%outOfLineFunctions {

const char *MushPiePosicity::AutoNameGet(void) const
{
    return "MushPiePosicity";
}

MushcoreVirtualObject *MushPiePosicity::AutoClone(void) const
{
    return new MushPiePosicity(*this);
}

MushcoreVirtualObject *MushPiePosicity::AutoCreate(void) const
{
    return new MushPiePosicity;
}

MushcoreVirtualObject *MushPiePosicity::AutoVirtualFactory(void)
{
    return new MushPiePosicity;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushPiePosicity", MushPiePosicity::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
bool
MushPiePosicity::AutoEquals(const MushPiePosicity& inObj) const
{
    return 1
        && (m_angPos == inObj.m_angPos)
        && (m_angVel == inObj.m_angVel)
        && (m_pos == inObj.m_pos)
        && (m_vel == inObj.m_vel)
    ;
}
void
MushPiePosicity::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "angPos=" << m_angPos << ", ";
    ioOut << "angVel=" << m_angVel << ", ";
    ioOut << "pos=" << m_pos << ", ";
    ioOut << "vel=" << m_vel;
    ioOut << "]";
}
bool
MushPiePosicity::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
    else if (inTagStr == "pos")
    {
        ioIn >> m_pos;
    }
    else if (inTagStr == "vel")
    {
        ioIn >> m_vel;
    }
    else
    {
        return false;
    }
    return true;
}
void
MushPiePosicity::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("angPos");
    ioOut << m_angPos;
    ioOut.TagSet("angVel");
    ioOut << m_angVel;
    ioOut.TagSet("pos");
    ioOut << m_pos;
    ioOut.TagSet("vel");
    ioOut << m_vel;
}
//%outOfLineFunctions } HyVByFbjAGYwIihEgHCa1Q
