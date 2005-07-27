//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionList.cpp
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
//%Header } /PoJWskflNonNJ2YThgWkg
/*
 * $Id$
 * $Log$
 */

#include "MushCollisionList.h"

using namespace Mushware;
using namespace std;

//%outOfLineFunctions {

const char *MushCollisionList::AutoName(void) const
{
    return "MushCollisionList";
}

MushcoreVirtualObject *MushCollisionList::AutoClone(void) const
{
    return new MushCollisionList(*this);
}

MushcoreVirtualObject *MushCollisionList::AutoCreate(void) const
{
    return new MushCollisionList;
}

MushcoreVirtualObject *MushCollisionList::AutoVirtualFactory(void)
{
    return new MushCollisionList;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushCollisionList", MushCollisionList::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushCollisionList::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "list=" << m_list;
    ioOut << "]";
}
bool
MushCollisionList::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "list")
    {
        ioIn >> m_list;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushCollisionList::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("list");
    ioOut << m_list;
}
//%outOfLineFunctions } kpG6fz4MD7vUeDKuOM3xLQ
