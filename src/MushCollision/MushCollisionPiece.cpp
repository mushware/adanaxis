//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionPiece.cpp
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
//%Header } WV+Zfql/63Y6iHwT6AXVfQ
/*
 * $Id$
 * $Log$
 */

#include "MushCollisionPiece.h"

using namespace Mushware;
using namespace std;

const MushMesh4Mesh&
MushCollisionPiece::CollisionMesh(void) const
{
    throw MushcoreDataFail(std::string("Request for collision mesh unsupported for type '")+AutoName()+"'");
}

const MushMeshPosticity&
MushCollisionPiece::CollisionPost(void) const
{
    throw MushcoreDataFail(std::string("Request for collision post unsupported for type '")+AutoName()+"'");
}

//%outOfLineFunctions {

const char *MushCollisionPiece::AutoName(void) const
{
    return "MushCollisionPiece";
}

MushcoreVirtualObject *MushCollisionPiece::AutoClone(void) const
{
    return new MushCollisionPiece(*this);
}

MushcoreVirtualObject *MushCollisionPiece::AutoCreate(void) const
{
    return new MushCollisionPiece;
}

MushcoreVirtualObject *MushCollisionPiece::AutoVirtualFactory(void)
{
    return new MushCollisionPiece;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushCollisionPiece", MushCollisionPiece::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushCollisionPiece::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushCollisionPiece::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushCollisionPiece::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } rr64XEbE2865DW9MUmyBQg
