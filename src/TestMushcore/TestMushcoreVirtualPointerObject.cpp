//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreVirtualPointerObject.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } ZakQe8n4v2EUcmOXTokzrw
/*
 * $Id: TestMushcoreVirtualPointerObject.cpp,v 1.1 2004/01/18 18:25:30 southa Exp $
 * $Log: TestMushcoreVirtualPointerObject.cpp,v $
 * Revision 1.1  2004/01/18 18:25:30  southa
 * XML stream upgrades
 *
 */

#include "TestMushcoreVirtualPointerObject.h"


void
TestMushcoreVirtualPointerObject::PopulateObjects1(void)
{
    DeleteObjects();
    m_basePtr = new TestMushcoreObjectBase;
    m_subPtr = new TestMushcoreObjectSub;
    m_subSubPtr = new TestMushcoreObjectSubSub;
}

void
TestMushcoreVirtualPointerObject::PopulateObjects2(void)
{
    DeleteObjects();
    m_basePtr = new TestMushcoreObjectSubSub;
    m_subPtr = new TestMushcoreObjectSubSub;
    m_subSubPtr = new TestMushcoreObjectSubSub;
}

void
TestMushcoreVirtualPointerObject::DeleteObjects(void)
{
    if (m_basePtr != NULL) { delete m_basePtr; m_basePtr = NULL; }
    if (m_subPtr != NULL) { delete m_subPtr; m_subPtr = NULL; }
    if (m_subSubPtr != NULL) { delete m_subSubPtr; m_subSubPtr = NULL; }
}

//%outOfLineFunctions {

const char *TestMushcoreVirtualPointerObject::AutoNameGet(void) const
{
    return "TestMushcoreVirtualPointerObject";
}

MushcoreVirtualObject *TestMushcoreVirtualPointerObject::AutoClone(void) const
{
    return new TestMushcoreVirtualPointerObject(*this);
}

MushcoreVirtualObject *TestMushcoreVirtualPointerObject::AutoCreate(void) const
{
    return new TestMushcoreVirtualPointerObject;
}

MushcoreVirtualObject *TestMushcoreVirtualPointerObject::AutoVirtualFactory(void)
{
    return new TestMushcoreVirtualPointerObject;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("TestMushcoreVirtualPointerObject", TestMushcoreVirtualPointerObject::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
bool
TestMushcoreVirtualPointerObject::AutoEquals(const TestMushcoreVirtualPointerObject& inObj) const
{
    return 1
        && (m_virtualPointerObjectValue == inObj.m_virtualPointerObjectValue)
        && (m_basePtr == inObj.m_basePtr || (m_basePtr != NULL && inObj.m_basePtr != NULL && *m_basePtr == *inObj.m_basePtr))
        && (m_subPtr == inObj.m_subPtr || (m_subPtr != NULL && inObj.m_subPtr != NULL && *m_subPtr == *inObj.m_subPtr))
        && (m_subSubPtr == inObj.m_subSubPtr || (m_subSubPtr != NULL && inObj.m_subSubPtr != NULL && *m_subSubPtr == *inObj.m_subSubPtr))
    ;
}
void
TestMushcoreVirtualPointerObject::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "virtualPointerObjectValue=" << m_virtualPointerObjectValue << ", ";
    if (m_basePtr == NULL)
    {
        ioOut << "basePtr=NULL"  << ", ";
    }
    else
    {
        ioOut << "basePtr=" << *m_basePtr << ", ";
    }
    if (m_subPtr == NULL)
    {
        ioOut << "subPtr=NULL"  << ", ";
    }
    else
    {
        ioOut << "subPtr=" << *m_subPtr << ", ";
    }
    if (m_subSubPtr == NULL)
    {
        ioOut << "subSubPtr=NULL" ;
    }
    else
    {
        ioOut << "subSubPtr=" << *m_subSubPtr;
    }
    ioOut << "]";
}
bool
TestMushcoreVirtualPointerObject::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "virtualPointerObjectValue")
    {
        ioIn >> m_virtualPointerObjectValue;
    }
    else if (inTagStr == "basePtr")
    {
        ioIn >> m_basePtr;
    }
    else if (inTagStr == "subPtr")
    {
        ioIn >> m_subPtr;
    }
    else if (inTagStr == "subSubPtr")
    {
        ioIn >> m_subSubPtr;
    }
    else
    {
        return false;
    }
    return true;
}
void
TestMushcoreVirtualPointerObject::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("virtualPointerObjectValue");
    ioOut << m_virtualPointerObjectValue;
    ioOut.TagSet("basePtr");
    ioOut << m_basePtr;
    ioOut.TagSet("subPtr");
    ioOut << m_subPtr;
    ioOut.TagSet("subSubPtr");
    ioOut << m_subSubPtr;
}
//%outOfLineFunctions } zSfwSdmNgaEsqCr8lEDI2w
