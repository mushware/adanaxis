//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Extruder.cpp
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
//%Header } E8IABISKcx+ONheyDTfHbA
/*
 * $Id: MushMesh4Extruder.cpp,v 1.3 2006/06/16 01:02:31 southa Exp $
 * $Log: MushMesh4Extruder.cpp,v $
 * Revision 1.3  2006/06/16 01:02:31  southa
 * Ruby mesh generation
 *
 * Revision 1.2  2006/06/14 18:45:47  southa
 * Ruby mesh generation
 *
 * Revision 1.1  2006/06/14 11:20:07  southa
 * Ruby mesh generation
 *
 */

#include "MushMesh4Extruder.h"

MushMesh4Extruder::MushMesh4Extruder() :
	m_sourceFaceNum(0),
	m_disp(MushMeshDisplacement::Identity()),
	m_dispVel(MushMeshDisplacement::Identity()),
    m_numIterations(1),
    m_toPoint(false)
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
    ioOut << "dispVel=" << m_dispVel << ", ";
    ioOut << "numIterations=" << m_numIterations << ", ";
    ioOut << "toPoint=" << m_toPoint;
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
    else if (inTagStr == "numIterations")
    {
        ioIn >> m_numIterations;
    }
    else if (inTagStr == "toPoint")
    {
        ioIn >> m_toPoint;
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
    ioOut.TagSet("numIterations");
    ioOut << m_numIterations;
    ioOut.TagSet("toPoint");
    ioOut << m_toPoint;
}
//%outOfLineFunctions } flIOLpK70OsY8k91i87k0A
