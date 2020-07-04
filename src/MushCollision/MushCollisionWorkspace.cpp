//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionWorkspace.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } YsUc1GMJLEm7KSB2m0LF/w
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
