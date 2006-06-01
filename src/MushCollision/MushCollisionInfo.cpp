//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionInfo.cpp
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
//%Header } OhkB4+wLY2tpRyaHhubwOw
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
    ioOut << "objectNamesValid=" << m_objectNamesValid << ", ";
    ioOut << "chunkNumsValid=" << m_chunkNumsValid;
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
    else if (inTagStr == "objectNamesValid")
    {
        ioIn >> m_objectNamesValid;
    }
    else if (inTagStr == "chunkNumsValid")
    {
        ioIn >> m_chunkNumsValid;
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
    ioOut.TagSet("objectNamesValid");
    ioOut << m_objectNamesValid;
    ioOut.TagSet("chunkNumsValid");
    ioOut << m_chunkNumsValid;
}
//%outOfLineFunctions } NAPE+1z1/Y/9+kqYcqN5Dw
