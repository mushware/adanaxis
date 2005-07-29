//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionResolver.cpp
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
//%Header } ut0PZ9K0qO+aZi1YpU+JsA
/*
 * $Id: MushCollisionResolver.cpp,v 1.1 2005/07/27 18:09:59 southa Exp $
 * $Log: MushCollisionResolver.cpp,v $
 * Revision 1.1  2005/07/27 18:09:59  southa
 * Collision checking
 *
 */

#include "MushCollisionResolver.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MushCollisionResolver);

Mushware::tVal
MushCollisionResolver::Resolve(const MushCollisionPiece& inPiece1, const MushCollisionPiece& inPiece2) const
{
    return 0;
}



//%outOfLineFunctions {

const char *MushCollisionResolver::AutoName(void) const
{
    return "MushCollisionResolver";
}

MushcoreVirtualObject *MushCollisionResolver::AutoClone(void) const
{
    return new MushCollisionResolver(*this);
}

MushcoreVirtualObject *MushCollisionResolver::AutoCreate(void) const
{
    return new MushCollisionResolver;
}

MushcoreVirtualObject *MushCollisionResolver::AutoVirtualFactory(void)
{
    return new MushCollisionResolver;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushCollisionResolver", MushCollisionResolver::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushCollisionResolver::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "frameMsec=" << m_frameMsec;
    ioOut << "]";
}
bool
MushCollisionResolver::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "frameMsec")
    {
        ioIn >> m_frameMsec;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushCollisionResolver::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("frameMsec");
    ioOut << m_frameMsec;
}
//%outOfLineFunctions } Wu3J/g5sj6Eo9u+Jjy0hSw
