//%includeGuardStart {
#ifndef MUSHGAMEMESSAGEFIRE_H
#define MUSHGAMEMESSAGEFIRE_H
//%includeGuardStart } 2NfNeCIksTDYOzOKngtC6A
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageFire.h
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
//%Header } T2lXJq2aB/L6MbrImgyYhg
/*
 * $Id: MushGameMessageFire.h,v 1.1 2005/07/12 12:18:18 southa Exp $
 * $Log: MushGameMessageFire.h,v $
 * Revision 1.1  2005/07/12 12:18:18  southa
 * Projectile work
 *
 */

#include "MushGameStandard.h"

#include "MushGameMessage.h"

//:xml1base MushGameMessage
//:generate virtual standard ostream xml1
class MushGameMessageFire : public MushGameMessage
{
public:
    explicit MushGameMessageFire(const std::string& inID = "") : MushGameMessage(inID) {}
    virtual ~MushGameMessageFire() {}

private:
    MushMeshPosticity m_post; //:readwrite :wref
    Mushware::U32 m_count; //:readwrite
    Mushware::U32 m_type; //:readwrite
    std::string m_owner; //:readwrite
//%classPrototypes {
public:
    const MushMeshPosticity& Post(void) const { return m_post; }
    void PostSet(const MushMeshPosticity& inValue) { m_post=inValue; }
    // Writable reference for m_post
    MushMeshPosticity& PostWRef(void) { return m_post; }
    const Mushware::U32& Count(void) const { return m_count; }
    void CountSet(const Mushware::U32& inValue) { m_count=inValue; }
    const Mushware::U32& Type(void) const { return m_type; }
    void TypeSet(const Mushware::U32& inValue) { m_type=inValue; }
    const std::string& Owner(void) const { return m_owner; }
    void OwnerSet(const std::string& inValue) { m_owner=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } SQxve7csnrjBohoVMeJKAw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameMessageFire& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Yeib1B1boEHjqXsekMgYjg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
