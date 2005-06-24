//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPosticity.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } 6t5YCxegLAOWEyrIZSFPLw
/*
 * $Id$
 * $Log$
 */

#include "MushMeshPosticity.h"

//%outOfLineFunctions {

const char *MushMeshPosticity::AutoName(void) const
{
    return "MushMeshPosticity";
}

MushcoreVirtualObject *MushMeshPosticity::AutoClone(void) const
{
    return new MushMeshPosticity(*this);
}

MushcoreVirtualObject *MushMeshPosticity::AutoCreate(void) const
{
    return new MushMeshPosticity;
}

MushcoreVirtualObject *MushMeshPosticity::AutoVirtualFactory(void)
{
    return new MushMeshPosticity;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMeshPosticity", MushMeshPosticity::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
bool
MushMeshPosticity::AutoEquals(const MushMeshPosticity& inObj) const
{
    return 1
        && (m_angPos == inObj.m_angPos)
        && (m_angVel == inObj.m_angVel)
        && (m_pos == inObj.m_pos)
        && (m_vel == inObj.m_vel)
        && (m_timestamp == inObj.m_timestamp)
        && (m_timeValid == inObj.m_timeValid)
    ;
}
void
MushMeshPosticity::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "angPos=" << m_angPos << ", ";
    ioOut << "angVel=" << m_angVel << ", ";
    ioOut << "pos=" << m_pos << ", ";
    ioOut << "vel=" << m_vel << ", ";
    ioOut << "timestamp=" << m_timestamp << ", ";
    ioOut << "timeValid=" << m_timeValid;
    ioOut << "]";
}
bool
MushMeshPosticity::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
    else if (inTagStr == "timestamp")
    {
        ioIn >> m_timestamp;
    }
    else if (inTagStr == "timeValid")
    {
        ioIn >> m_timeValid;
    }
    else
    {
        return false;
    }
    return true;
}
void
MushMeshPosticity::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("angPos");
    ioOut << m_angPos;
    ioOut.TagSet("angVel");
    ioOut << m_angVel;
    ioOut.TagSet("pos");
    ioOut << m_pos;
    ioOut.TagSet("vel");
    ioOut << m_vel;
    ioOut.TagSet("timestamp");
    ioOut << m_timestamp;
    ioOut.TagSet("timeValid");
    ioOut << m_timeValid;
}
//%outOfLineFunctions } 5pOGc6kB3mKRYmjI4W/LKA
