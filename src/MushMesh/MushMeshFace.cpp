//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshFace.cpp
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
//%Header } EdF8rw7ulzOAVAjW1Qr63A
/*
 * $Id: MushMeshFace.cpp,v 1.1 2005/06/30 12:04:55 southa Exp $
 * $Log: MushMeshFace.cpp,v $
 * Revision 1.1  2005/06/30 12:04:55  southa
 * Mesh work
 *
 */

#include "MushMeshFace.h"

//%outOfLineFunctions {

const char *MushMeshFace::AutoName(void) const
{
    return "MushMeshFace";
}

MushcoreVirtualObject *MushMeshFace::AutoClone(void) const
{
    return new MushMeshFace(*this);
}

MushcoreVirtualObject *MushMeshFace::AutoCreate(void) const
{
    return new MushMeshFace;
}

MushcoreVirtualObject *MushMeshFace::AutoVirtualFactory(void)
{
    return new MushMeshFace;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMeshFace", MushMeshFace::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMeshFace::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushMeshFace::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushMeshFace::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } D2wwK4GSXIijunstkr/qfg
