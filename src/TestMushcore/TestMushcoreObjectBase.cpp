//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObjectBase.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 2/hOq2YO5tgIn4JHoD/exQ
/*
 * $Id: TestMushcoreObjectBase.cpp,v 1.1 2004/01/18 18:25:29 southa Exp $
 * $Log: TestMushcoreObjectBase.cpp,v $
 * Revision 1.1  2004/01/18 18:25:29  southa
 * XML stream upgrades
 *
 */

#include "TestMushcoreObjectBase.h"

//%outOfLineFunctions {

const char *TestMushcoreObjectBase::AutoNameGet(void) const
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
        ioIn >> *this;
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
//%outOfLineFunctions } ACldnHdFk7OaVTSAxuU6bQ
