//%includeGuardStart {
#ifndef TESTMUSHCOREVIRTUALPOINTEROBJECT_H
#define TESTMUSHCOREVIRTUALPOINTEROBJECT_H
//%includeGuardStart } A6gr1bO23FkbXqc8xgtG3Q
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreVirtualPointerObject.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } YBw5+nlofmmkMYnll0Z0xg
/*
 * $Id: TestMushcoreVirtualPointerObject.h,v 1.1 2004/01/18 18:25:30 southa Exp $
 * $Log: TestMushcoreVirtualPointerObject.h,v $
 * Revision 1.1  2004/01/18 18:25:30  southa
 * XML stream upgrades
 *
 */

#include "TestMushcoreStandard.h"

#include "TestMushcoreObjectBase.h"
#include "TestMushcoreObjectSub.h"
#include "TestMushcoreObjectSubSub.h"

//:generate standard basic ostream xml1
class TestMushcoreVirtualPointerObject : public MushcoreVirtualObject
{
public:
    TestMushcoreVirtualPointerObject() :
        m_virtualPointerObjectValue(10),
        m_basePtr(NULL),
        m_subPtr(NULL),
        m_subSubPtr(NULL)
        {}
    
    void PopulateObjects1(void);
    void PopulateObjects2(void);
    void DeleteObjects(void);
    
    virtual ~TestMushcoreVirtualPointerObject() { DeleteObjects(); }
    
private:
    Mushware::U32 m_virtualPointerObjectValue; //:readwrite
    TestMushcoreObjectBase *m_basePtr;
    TestMushcoreObjectSub *m_subPtr;
    TestMushcoreObjectSubSub *m_subSubPtr;
//%classPrototypes {
public:
    const Mushware::U32& VirtualPointerObjectValue(void) const { return m_virtualPointerObjectValue; }
    void VirtualPointerObjectValueSet(const Mushware::U32& inValue) { m_virtualPointerObjectValue=inValue; }
    virtual const char *AutoNameGet(void) const;
    virtual TestMushcoreVirtualPointerObject *AutoClone(void) const;
    virtual TestMushcoreVirtualPointerObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual bool AutoEquals(const TestMushcoreVirtualPointerObject& inObj) const;
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } oIJhcGk3h+FUqHqwFaQIKw
};
//%inlineHeader {
inline bool
operator==(const TestMushcoreVirtualPointerObject& inA, const TestMushcoreVirtualPointerObject& inB)
{
    return inA.AutoEquals(inB);
}
inline bool
operator!=(const TestMushcoreVirtualPointerObject& inA, const TestMushcoreVirtualPointerObject& inB)
{
    return !inA.AutoEquals(inB);
}
inline std::ostream&
operator<<(std::ostream& ioOut, const TestMushcoreVirtualPointerObject& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } fjxQ0pKCxxXKAXpc/kMFGw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
