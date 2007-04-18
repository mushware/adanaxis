//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObjectBase.cpp
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
//%Header } esI9gq1O18PgcUgDmtWU+A
/*
 * $Id: TestMushcoreObjectBase.cpp,v 1.7 2006/06/01 15:40:05 southa Exp $
 * $Log: TestMushcoreObjectBase.cpp,v $
 * Revision 1.7  2006/06/01 15:40:05  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/07/02 00:42:39  southa
 * Conditioning tweaks
 *
 * Revision 1.5  2005/06/20 14:30:39  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/06/16 17:25:41  southa
 * Client/server work
 *
 * Revision 1.3  2005/05/19 13:02:24  southa
 * Mac release work
 *
 * Revision 1.2  2005/02/10 12:34:23  southa
 * Template fixes
 *
 * Revision 1.1  2004/01/18 18:25:29  southa
 * XML stream upgrades
 *
 */

#include "TestMushcoreObjectBase.h"

//%outOfLineFunctions {

const char *TestMushcoreObjectBase::AutoName(void) const
{
    return "TestMushcoreObjectBase";
}

MushcoreVirtualObject *TestMushcoreObjectBase::AutoClone(void) const
{
    return new TestMushcoreObjectBase(*this);
}

MushcoreVirtualObject *TestMushcoreObjectBase::AutoCreate(void) const
{
    return new TestMushcoreObjectBase;
}

MushcoreVirtualObject *TestMushcoreObjectBase::AutoVirtualFactory(void)
{
    return new TestMushcoreObjectBase;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("TestMushcoreObjectBase", TestMushcoreObjectBase::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
bool
TestMushcoreObjectBase::AutoEquals(const TestMushcoreObjectBase& inObj) const
{
    return 1
        && (m_baseObjectValue == inObj.m_baseObjectValue)
    ;
}
void
TestMushcoreObjectBase::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "baseObjectValue=" << m_baseObjectValue;
    ioOut << "]";
}
bool
TestMushcoreObjectBase::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "baseObjectValue")
    {
        ioIn >> m_baseObjectValue;
    }
    else 
    {
        return false;
    }
    return true;
}
void
TestMushcoreObjectBase::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("baseObjectValue");
    ioOut << m_baseObjectValue;
}
//%outOfLineFunctions } jyHQaNSLvV01nl5Rs3KDig
