//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObjectSub.cpp
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
//%Header } bzZeP1dl7EEAL/nNQRoAFg
/*
 * $Id: TestMushcoreObjectSub.cpp,v 1.6 2005/06/20 14:30:39 southa Exp $
 * $Log: TestMushcoreObjectSub.cpp,v $
 * Revision 1.6  2005/06/20 14:30:39  southa
 * Adanaxis work
 *
 * Revision 1.5  2005/06/16 17:25:41  southa
 * Client/server work
 *
 * Revision 1.4  2005/05/19 13:02:24  southa
 * Mac release work
 *
 * Revision 1.3  2005/03/25 22:04:51  southa
 * Dialogue and MushcoreIO fixes
 *
 * Revision 1.2  2005/02/10 12:34:24  southa
 * Template fixes
 *
 * Revision 1.1  2004/01/18 18:25:29  southa
 * XML stream upgrades
 *
 */

#include "TestMushcoreObjectSub.h"

//%outOfLineFunctions {

const char *TestMushcoreObjectSub::AutoName(void) const
{
    return "TestMushcoreObjectSub";
}

MushcoreVirtualObject *TestMushcoreObjectSub::AutoClone(void) const
{
    return new TestMushcoreObjectSub(*this);
}

MushcoreVirtualObject *TestMushcoreObjectSub::AutoCreate(void) const
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
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
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
//%outOfLineFunctions } jKdWMvn2PupKHBpmwbmlAw
