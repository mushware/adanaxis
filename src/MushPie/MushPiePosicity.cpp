//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePosicity.cpp
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
//%Header } bTbHW3ecVLM7oxOlOs4JKQ
/*
 * $Id: MushPiePosicity.cpp,v 1.9 2006/06/01 15:39:37 southa Exp $
 * $Log: MushPiePosicity.cpp,v $
 * Revision 1.9  2006/06/01 15:39:37  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.7  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.6  2005/06/16 17:25:40  southa
 * Client/server work
 *
 * Revision 1.5  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.4  2005/03/25 19:13:50  southa
 * GameDialogue work
 *
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

const char *MushPiePosicity::AutoName(void) const
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
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
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
//%outOfLineFunctions } idsK+Gclj+9CkS88anChQQ
