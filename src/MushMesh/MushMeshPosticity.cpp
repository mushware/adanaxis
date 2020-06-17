//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPosticity.cpp
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
//%Header } kSFMWExRanxgojyP2Mt/nA
/*
 * $Id: MushMeshPosticity.cpp,v 1.3 2006/06/01 15:39:31 southa Exp $
 * $Log: MushMeshPosticity.cpp,v $
 * Revision 1.3  2006/06/01 15:39:31  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.1  2005/06/24 10:30:13  southa
 * MushGame camera work
 *
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
//%outOfLineFunctions } 9RLjOHmJ+KGuDf3hVF4yAw
