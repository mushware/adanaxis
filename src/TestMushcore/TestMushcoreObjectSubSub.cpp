//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObjectSubSub.cpp
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
//%Header } KIdxnUyOTil5902vWlZ1jw
/*
 * $Id: TestMushcoreObjectSubSub.cpp,v 1.5 2005/06/20 14:30:40 southa Exp $
 * $Log: TestMushcoreObjectSubSub.cpp,v $
 * Revision 1.5  2005/06/20 14:30:40  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/06/16 17:25:41  southa
 * Client/server work
 *
 * Revision 1.3  2005/05/19 13:02:24  southa
 * Mac release work
 *
 * Revision 1.2  2005/02/10 12:34:24  southa
 * Template fixes
 *
 * Revision 1.1  2004/01/18 18:25:30  southa
 * XML stream upgrades
 *
 */

#include "TestMushcoreObjectSubSub.h"

//%outOfLineFunctions {

const char *TestMushcoreObjectSubSub::AutoName(void) const
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
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
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
//%outOfLineFunctions } WjnZxyeFgv033VVqckJPCw
