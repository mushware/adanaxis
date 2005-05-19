//%includeGuardStart {
#ifndef TESTMUSHCOREVIRTUALPOINTEROBJECT_H
#define TESTMUSHCOREVIRTUALPOINTEROBJECT_H
//%includeGuardStart } A6gr1bO23FkbXqc8xgtG3Q
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreVirtualPointerObject.h
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
//%Header } bPRUCJmmoAJZryzLENxKpg
/*
 * $Id: TestMushcoreVirtualPointerObject.h,v 1.3 2005/02/10 12:34:26 southa Exp $
 * $Log: TestMushcoreVirtualPointerObject.h,v $
 * Revision 1.3  2005/02/10 12:34:26  southa
 * Template fixes
 *
 * Revision 1.2  2005/02/03 21:03:14  southa
 * Build fixes
 *
 * Revision 1.1  2004/01/18 18:25:30  southa
 * XML stream upgrades
 *
 */

#include "TestMushcoreStandard.h"

#include "TestMushcoreObjectBase.h"
#include "TestMushcoreObjectSub.h"
#include "TestMushcoreObjectSubSub.h"

//:generate virtual standard basic ostream xml1
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
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual bool AutoEquals(const TestMushcoreVirtualPointerObject& inObj) const;
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } szVKtSZdY3zVkay2rikqKA
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
