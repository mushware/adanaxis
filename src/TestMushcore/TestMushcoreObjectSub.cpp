//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObjectSub.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } oqxNy4x7iWPXWGYg7HWL+w
/*
 * $Id$
 * $Log$
 */

#include "TestMushcoreObjectSub.h"

//%outOfLineFunctions {
const char *TestMushcoreObjectSub::AutoNameGet(void) const
{
    return "TestMushcoreObjectSub";
}
TestMushcoreObjectSub *TestMushcoreObjectSub::AutoClone(void) const
{
    return new TestMushcoreObjectSub(*this);
}
TestMushcoreObjectSub *TestMushcoreObjectSub::AutoCreate(void) const
{
    return new TestMushcoreObjectSub;
}
MushcoreVirtualObject *TestMushcoreObjectSub::AutoVirtualFactory(void)
{
    return new TestMushcoreObjectSub;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("TestMushcoreObjectSub", TestMushcoreObjectSub::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
bool
TestMushcoreObjectSub::AutoEquals(const TestMushcoreObjectSub& inObj) const
{
    return 1
        && TestMushcoreObjectBase::AutoEquals(inObj)
        && (m_subObjectValue == inObj.m_subObjectValue)
    ;
}
void
TestMushcoreObjectSub::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    TestMushcoreObjectBase::AutoPrint(ioOut);
    ioOut << "subObjectValue=" << m_subObjectValue;
    ioOut << "]";
}
bool
TestMushcoreObjectSub::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "subObjectValue")
    {
        ioIn >> m_subObjectValue;
    }
    else if (TestMushcoreObjectBase::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else
    {
        return false;
    }
    return true;
}
void
TestMushcoreObjectSub::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    TestMushcoreObjectBase::AutoXMLPrint(ioOut);
    ioOut.TagSet("subObjectValue");
    ioOut << m_subObjectValue;
}
//%outOfLineFunctions } IHZZt0cpdbHv3RYlA8xusQ
