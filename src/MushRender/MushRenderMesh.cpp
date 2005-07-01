//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderMesh.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } RGouKCAnfPKJ4WGuheaYpA
/*
 * $Id$
 * $Log$
 */

#include "MushRenderMesh.h"

void
MushRenderMesh::MeshRender(const MushRenderSpec& inSpec, const MushMeshMesh& inMesh)
{
    // Fill me in
}

//%outOfLineFunctions {

const char *MushRenderMesh::AutoName(void) const
{
    return "MushRenderMesh";
}

MushcoreVirtualObject *MushRenderMesh::AutoClone(void) const
{
    return new MushRenderMesh(*this);
}

MushcoreVirtualObject *MushRenderMesh::AutoCreate(void) const
{
    return new MushRenderMesh;
}

MushcoreVirtualObject *MushRenderMesh::AutoVirtualFactory(void)
{
    return new MushRenderMesh;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushRenderMesh", MushRenderMesh::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushRenderMesh::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushRenderMesh::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushRenderMesh::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } Cjkt0e4dBA+PpRgbWo3blg
