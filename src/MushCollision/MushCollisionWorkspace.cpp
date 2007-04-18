//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionWorkspace.cpp
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
//%Header } MB95HEgQqHUR6mA2GpAqeQ
/*
 * $Id: MushCollisionWorkspace.cpp,v 1.3 2006/06/01 15:39:16 southa Exp $
 * $Log: MushCollisionWorkspace.cpp,v $
 * Revision 1.3  2006/06/01 15:39:16  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/29 08:27:47  southa
 * Collision work
 *
 * Revision 1.1  2005/07/27 18:09:59  southa
 * Collision checking
 *
 */

#include "MushCollisionWorkspace.h"

using namespace Mushware;
using namespace std;

MushCollisionWorkspace::MushCollisionWorkspace() :
    m_frameMsec(0)
{
    Touch();    
}

// Called by constructor
void
MushCollisionWorkspace::Touch(void)
{
    m_centroidValid = false;
    m_chunkCentroidsValid = false;    
}

void
MushCollisionWorkspace::ResetIfNeeded(Mushware::tMsec inFrameMsec)
{
    if (m_frameMsec != inFrameMsec)
    {
        Touch();
        m_frameMsec = inFrameMsec;
    }
}

//%outOfLineFunctions {

const char *MushCollisionWorkspace::AutoName(void) const
{
    return "MushCollisionWorkspace";
}

MushcoreVirtualObject *MushCollisionWorkspace::AutoClone(void) const
{
    return new MushCollisionWorkspace(*this);
}

MushcoreVirtualObject *MushCollisionWorkspace::AutoCreate(void) const
{
    return new MushCollisionWorkspace;
}

MushcoreVirtualObject *MushCollisionWorkspace::AutoVirtualFactory(void)
{
    return new MushCollisionWorkspace;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushCollisionWorkspace", MushCollisionWorkspace::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushCollisionWorkspace::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "frameMsec=" << m_frameMsec << ", ";
    ioOut << "centroid=" << m_centroid << ", ";
    ioOut << "chunkCentroids=" << m_chunkCentroids << ", ";
    ioOut << "centroidValid=" << m_centroidValid << ", ";
    ioOut << "chunkCentroidsValid=" << m_chunkCentroidsValid;
    ioOut << "]";
}
bool
MushCollisionWorkspace::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "frameMsec")
    {
        ioIn >> m_frameMsec;
    }
    else if (inTagStr == "centroid")
    {
        ioIn >> m_centroid;
    }
    else if (inTagStr == "chunkCentroids")
    {
        ioIn >> m_chunkCentroids;
    }
    else if (inTagStr == "centroidValid")
    {
        ioIn >> m_centroidValid;
    }
    else if (inTagStr == "chunkCentroidsValid")
    {
        ioIn >> m_chunkCentroidsValid;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushCollisionWorkspace::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("frameMsec");
    ioOut << m_frameMsec;
    ioOut.TagSet("centroid");
    ioOut << m_centroid;
    ioOut.TagSet("chunkCentroids");
    ioOut << m_chunkCentroids;
    ioOut.TagSet("centroidValid");
    ioOut << m_centroidValid;
    ioOut.TagSet("chunkCentroidsValid");
    ioOut << m_chunkCentroidsValid;
}
//%outOfLineFunctions } UqBfnTcNY4hBO786+WrQWA
