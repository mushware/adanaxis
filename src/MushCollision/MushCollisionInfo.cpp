//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionInfo.cpp
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
//%Header } pkcKvrOG/sfo/+8dZ22gHg
/*
 *  MushCollisionInfo.cpp
 *  project
 *
 *  Created by Andy Southgate on 01/08/2005.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include "MushCollisionInfo.h"

//%outOfLineFunctions {

const char *MushCollisionInfo::AutoName(void) const
{
    return "MushCollisionInfo";
}

MushcoreVirtualObject *MushCollisionInfo::AutoClone(void) const
{
    return new MushCollisionInfo(*this);
}

MushcoreVirtualObject *MushCollisionInfo::AutoCreate(void) const
{
    return new MushCollisionInfo;
}

MushcoreVirtualObject *MushCollisionInfo::AutoVirtualFactory(void)
{
    return new MushCollisionInfo;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushCollisionInfo", MushCollisionInfo::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushCollisionInfo::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "separatingDistance=" << m_separatingDistance << ", ";
    ioOut << "objectName1=" << m_objectName1 << ", ";
    ioOut << "objectName2=" << m_objectName2 << ", ";
    ioOut << "chunkNum1=" << m_chunkNum1 << ", ";
    ioOut << "chunkNum2=" << m_chunkNum2 << ", ";
    ioOut << "collisionPoint=" << m_collisionPoint << ", ";
    ioOut << "objectNamesValid=" << m_objectNamesValid << ", ";
    ioOut << "chunkNumsValid=" << m_chunkNumsValid << ", ";
    ioOut << "objectPointersValid=" << m_objectPointersValid << ", ";
    ioOut << "collisionPointValid=" << m_collisionPointValid;
    ioOut << "]";
}
bool
MushCollisionInfo::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "separatingDistance")
    {
        ioIn >> m_separatingDistance;
    }
    else if (inTagStr == "objectName1")
    {
        ioIn >> m_objectName1;
    }
    else if (inTagStr == "objectName2")
    {
        ioIn >> m_objectName2;
    }
    else if (inTagStr == "chunkNum1")
    {
        ioIn >> m_chunkNum1;
    }
    else if (inTagStr == "chunkNum2")
    {
        ioIn >> m_chunkNum2;
    }
    else if (inTagStr == "collisionPoint")
    {
        ioIn >> m_collisionPoint;
    }
    else if (inTagStr == "objectNamesValid")
    {
        ioIn >> m_objectNamesValid;
    }
    else if (inTagStr == "chunkNumsValid")
    {
        ioIn >> m_chunkNumsValid;
    }
    else if (inTagStr == "objectPointersValid")
    {
        ioIn >> m_objectPointersValid;
    }
    else if (inTagStr == "collisionPointValid")
    {
        ioIn >> m_collisionPointValid;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushCollisionInfo::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("separatingDistance");
    ioOut << m_separatingDistance;
    ioOut.TagSet("objectName1");
    ioOut << m_objectName1;
    ioOut.TagSet("objectName2");
    ioOut << m_objectName2;
    ioOut.TagSet("chunkNum1");
    ioOut << m_chunkNum1;
    ioOut.TagSet("chunkNum2");
    ioOut << m_chunkNum2;
    ioOut.TagSet("collisionPoint");
    ioOut << m_collisionPoint;
    ioOut.TagSet("objectNamesValid");
    ioOut << m_objectNamesValid;
    ioOut.TagSet("chunkNumsValid");
    ioOut << m_chunkNumsValid;
    ioOut.TagSet("objectPointersValid");
    ioOut << m_objectPointersValid;
    ioOut.TagSet("collisionPointValid");
    ioOut << m_collisionPointValid;
}
//%outOfLineFunctions } 5MagyiLHMt7rU5HPQj9wTQ
