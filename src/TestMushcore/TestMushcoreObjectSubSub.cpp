//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObjectSubSub.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 9znNwW1jX3oyltuN3bjB7g
/*
 * $Id: TestMushcoreObjectSubSub.cpp,v 1.1 2004/01/18 18:25:30 southa Exp $
 * $Log: TestMushcoreObjectSubSub.cpp,v $
 * Revision 1.1  2004/01/18 18:25:30  southa
 * XML stream upgrades
 *
 */

#include "TestMushcoreObjectSubSub.h"

//%outOfLineFunctions {

const char *TestMushcoreObjectSubSub::AutoNameGet(void) const
{
    return "TestMushcoreObjectSubSub";
}

MushcoreVirtualObject *TestMushcoreObjectSubSub::AutoClone(void) const
{
    return new TestMushcoreObjectSubSub(*this);
}

MushcoreVirtualObject *TestMushcoreObjectSubSub::AutoCreate(void) const
{
    return new TestMushcoreObjectSubSub;
}

MushcoreVirtualObject *TestMushcoreObjectSubSub::AutoVirtualFactory(void)
{
    return new TestMushcoreObjectSubSub;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("TestMushcoreObjectSubSub", TestMushcoreObjectSubSub::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
bool
TestMushcoreObjectSubSub::AutoEquals(const TestMushcoreObjectSubSub& inObj) const
{
    return 1
        && TestMushcoreObjectSub::AutoEquals(inObj)
        && (m_subSubObjectValue == inObj.m_subSubObjectValue)
    ;
}
void
TestMushcoreObjectSubSub::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    TestMushcoreObjectSub::AutoPrint(ioOut);
    ioOut << "subSubObjectValue=" << m_subSubObjectValue;
    ioOut << "]";
}
bool
TestMushcoreObjectSubSub::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "subSubObjectValue")
    {
        ioIn >> m_subSubObjectValue;
    }
    else if (TestMushcoreObjectSub::AutoXMLDataProcess(ioIn, inTagStr))
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
TestMushcoreObjectSubSub::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    TestMushcoreObjectSub::AutoXMLPrint(ioOut);
    ioOut.TagSet("subSubObjectValue");
    ioOut << m_subSubObjectValue;
}
//%outOfLineFunctions } BKsh9/ZsEUaoufXIUdMe6Q
