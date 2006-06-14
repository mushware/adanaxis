//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Extruder.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } 9JPXJ2bpwRb+KLjiunD82Q
/*
 * $Id: MushMesh4Extruder.cpp,v 1.1 2006/06/14 11:20:07 southa Exp $
 * $Log: MushMesh4Extruder.cpp,v $
 * Revision 1.1  2006/06/14 11:20:07  southa
 * Ruby mesh generation
 *
 */

#include "MushMesh4Extruder.h"

MushMesh4Extruder::MushMesh4Extruder() :
	m_sourceFaceNum(0),
	m_disp(MushMeshDisplacement::Identity()),
	m_dispVel(MushMeshDisplacement::Identity())
{
}

//%outOfLineFunctions {

const char *MushMesh4Extruder::AutoName(void) const
{
    return "MushMesh4Extruder";
}

MushcoreVirtualObject *MushMesh4Extruder::AutoClone(void) const
{
    return new MushMesh4Extruder(*this);
}

MushcoreVirtualObject *MushMesh4Extruder::AutoCreate(void) const
{
    return new MushMesh4Extruder;
}

MushcoreVirtualObject *MushMesh4Extruder::AutoVirtualFactory(void)
{
    return new MushMesh4Extruder;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMesh4Extruder", MushMesh4Extruder::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMesh4Extruder::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "sourceFaceNum=" << m_sourceFaceNum << ", ";
    ioOut << "disp=" << m_disp << ", ";
    ioOut << "dispVel=" << m_dispVel;
    ioOut << "]";
}
bool
MushMesh4Extruder::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "sourceFaceNum")
    {
        ioIn >> m_sourceFaceNum;
    }
    else if (inTagStr == "disp")
    {
        ioIn >> m_disp;
    }
    else if (inTagStr == "dispVel")
    {
        ioIn >> m_dispVel;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushMesh4Extruder::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("sourceFaceNum");
    ioOut << m_sourceFaceNum;
    ioOut.TagSet("disp");
    ioOut << m_disp;
    ioOut.TagSet("dispVel");
    ioOut << m_dispVel;
}
//%outOfLineFunctions } KTwsvpv/gjAz5GQnmxDFdQ
