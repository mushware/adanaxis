//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Base.cpp
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
//%Header } gbDnjktEcZRVu1Pjunb9Dw
/*
 * $Id: MushMesh4Base.cpp,v 1.1 2006/06/16 01:02:31 southa Exp $
 * $Log: MushMesh4Base.cpp,v $
 * Revision 1.1  2006/06/16 01:02:31  southa
 * Ruby mesh generation
 *
 */

#include "MushMesh4Base.h"

using namespace Mushware;
using namespace std;

void
MushMesh4Base::Make(MushMesh4Mesh& ioMesh) const
{
	throw MushcoreRequestFail("MushMesh4Base::Make not overriden - cannot build base object");
}
//%outOfLineFunctions {

const char *MushMesh4Base::AutoName(void) const
{
    return "MushMesh4Base";
}

MushcoreVirtualObject *MushMesh4Base::AutoClone(void) const
{
    return new MushMesh4Base(*this);
}

MushcoreVirtualObject *MushMesh4Base::AutoCreate(void) const
{
    return new MushMesh4Base;
}

MushcoreVirtualObject *MushMesh4Base::AutoVirtualFactory(void)
{
    return new MushMesh4Base;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMesh4Base", MushMesh4Base::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMesh4Base::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushMesh4Base::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushMesh4Base::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } i40vBYeuo0UBHkAjdU0lGQ
