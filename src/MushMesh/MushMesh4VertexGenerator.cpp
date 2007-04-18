//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4VertexGenerator.cpp
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
//%Header } M+ebTpyvLIRoPbqPbxv9cw
/*
 * $Id: MushMesh4VertexGenerator.cpp,v 1.2 2006/06/01 15:39:28 southa Exp $
 * $Log: MushMesh4VertexGenerator.cpp,v $
 * Revision 1.2  2006/06/01 15:39:28  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 */

#include "MushMesh4VertexGenerator.h"

//%outOfLineFunctions {

const char *MushMesh4VertexGenerator::AutoName(void) const
{
    return "MushMesh4VertexGenerator";
}

MushcoreVirtualObject *MushMesh4VertexGenerator::AutoClone(void) const
{
    return new MushMesh4VertexGenerator(*this);
}

MushcoreVirtualObject *MushMesh4VertexGenerator::AutoCreate(void) const
{
    return new MushMesh4VertexGenerator;
}

MushcoreVirtualObject *MushMesh4VertexGenerator::AutoVirtualFactory(void)
{
    return new MushMesh4VertexGenerator;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMesh4VertexGenerator", MushMesh4VertexGenerator::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMesh4VertexGenerator::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushMesh4VertexGenerator::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushMesh4VertexGenerator::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } lyeVTCecrUbXkcWUQLvJPw
