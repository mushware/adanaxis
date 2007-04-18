//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4FaceGenerator.cpp
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
//%Header } gw5SlrejgmV6oSxGt57eiw
/*
 * $Id: MushMesh4FaceGenerator.cpp,v 1.2 2006/06/01 15:39:28 southa Exp $
 * $Log: MushMesh4FaceGenerator.cpp,v $
 * Revision 1.2  2006/06/01 15:39:28  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/12 20:39:04  southa
 * Mesh library work
 *
 */

#include "MushMesh4FaceGenerator.h"

//%outOfLineFunctions {

const char *MushMesh4FaceGenerator::AutoName(void) const
{
    return "MushMesh4FaceGenerator";
}

MushcoreVirtualObject *MushMesh4FaceGenerator::AutoClone(void) const
{
    return new MushMesh4FaceGenerator(*this);
}

MushcoreVirtualObject *MushMesh4FaceGenerator::AutoCreate(void) const
{
    return new MushMesh4FaceGenerator;
}

MushcoreVirtualObject *MushMesh4FaceGenerator::AutoVirtualFactory(void)
{
    return new MushMesh4FaceGenerator;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMesh4FaceGenerator", MushMesh4FaceGenerator::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMesh4FaceGenerator::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushMesh4FaceGenerator::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushMesh4FaceGenerator::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } bJsOs9s220IxHgITIdrBCQ
