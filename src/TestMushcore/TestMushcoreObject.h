//%includeGuardStart {
#ifndef TESTMUSHCOREOBJECT_H
#define TESTMUSHCOREOBJECT_H
//%includeGuardStart } ZbgVXkoAm05vlwSoai7fLw
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObject.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 6Pvz7HiimjBXCxXQxlnIcA
/*
 * $Id$
 * $Log$
 */

#include "Mushcore.h"

//:generate xml1
class TestMushcoreObject : public MushcoreObject
{
public:
    TestMushcoreObject() :
        m_u8(1),
        m_u32(2)
    {}
    
private:
    Mushware::U8 m_u8;
    Mushware::U32 m_u32;
//%classPrototypes {
public:
    void AutoXMLPrint(MushcoreXMLOStream& ioOut, const std::string& inName) const;
//%classPrototypes } N6iskTKtPY7c4fIZSV6ABQ
};
//%inlineHeader {
namespace Mushcore
{

inline void
Pickle(MushcoreXMLOStream& ioOut, const TestMushcoreObject& inObj, const std::string& inName="")
{
    inObj.AutoXMLPrint(ioOut, inName);
}

} // end namespace Mushcore
//%inlineHeader } +Fjvv2DYljqARHYMR/7PLA




//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
