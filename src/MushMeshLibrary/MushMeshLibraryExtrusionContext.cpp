//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryExtrusionContext.cpp
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
//%Header } EtpeyyAoMvprLHvLGwsLnA
/*
 * $Id: MushMeshLibraryExtrusionContext.cpp,v 1.4 2007/04/18 09:22:53 southa Exp $
 * $Log: MushMeshLibraryExtrusionContext.cpp,v $
 * Revision 1.4  2007/04/18 09:22:53  southa
 * Header and level fixes
 *
 * Revision 1.3  2006/08/01 17:21:34  southa
 * River demo
 *
 * Revision 1.2  2006/06/01 15:39:34  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/14 12:50:31  southa
 * Extrusion work
 *
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
