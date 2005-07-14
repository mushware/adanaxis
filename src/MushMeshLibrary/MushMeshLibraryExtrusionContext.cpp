//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryExtrusionContext.cpp
 *
 * Copyright: Andy Southgate 2005
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } ypjcBRRJzy0DObpalZf23g
/*
 * $Id$
 * $Log$
 */

#include "MushMeshLibraryExtrusionContext.h"
//%outOfLineFunctions {

const char *MushMeshLibraryExtrusionContext::AutoName(void) const
{
    return "MushMeshLibraryExtrusionContext";
}

MushcoreVirtualObject *MushMeshLibraryExtrusionContext::AutoClone(void) const
{
    return new MushMeshLibraryExtrusionContext(*this);
}

MushcoreVirtualObject *MushMeshLibraryExtrusionContext::AutoCreate(void) const
{
    return new MushMeshLibraryExtrusionContext;
}

MushcoreVirtualObject *MushMeshLibraryExtrusionContext::AutoVirtualFactory(void)
{
    return new MushMeshLibraryExtrusionContext;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMeshLibraryExtrusionContext", MushMeshLibraryExtrusionContext::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMeshLibraryExtrusionContext::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "disp=" << m_disp << ", ";
    ioOut << "faceNum=" << m_faceNum << ", ";
    ioOut << "scaleThreshold=" << m_scaleThreshold << ", ";
    ioOut << "scaleVelocity=" << m_scaleVelocity << ", ";
    ioOut << "rollingDisp=" << m_rollingDisp << ", ";
    ioOut << "rollingFaceNum=" << m_rollingFaceNum;
    ioOut << "]";
}
bool
MushMeshLibraryExtrusionContext::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "disp")
    {
        ioIn >> m_disp;
    }
    else if (inTagStr == "faceNum")
    {
        ioIn >> m_faceNum;
    }
    else if (inTagStr == "scaleThreshold")
    {
        ioIn >> m_scaleThreshold;
    }
    else if (inTagStr == "scaleVelocity")
    {
        ioIn >> m_scaleVelocity;
    }
    else if (inTagStr == "rollingDisp")
    {
        ioIn >> m_rollingDisp;
    }
    else if (inTagStr == "rollingFaceNum")
    {
        ioIn >> m_rollingFaceNum;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushMeshLibraryExtrusionContext::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("disp");
    ioOut << m_disp;
    ioOut.TagSet("faceNum");
    ioOut << m_faceNum;
    ioOut.TagSet("scaleThreshold");
    ioOut << m_scaleThreshold;
    ioOut.TagSet("scaleVelocity");
    ioOut << m_scaleVelocity;
    ioOut.TagSet("rollingDisp");
    ioOut << m_rollingDisp;
    ioOut.TagSet("rollingFaceNum");
    ioOut << m_rollingFaceNum;
}
//%outOfLineFunctions } oJzsYXJ1o0ru9L1HM1iw3A
