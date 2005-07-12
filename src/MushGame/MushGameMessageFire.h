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
 * $Id$
 * $Log$
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
    Mushware::U32 m_type; //:readwrite
    std::string m_owner; //:readwrite
//%classPrototypes {
public:
    const MushMeshPosticity& Post(void) const { return m_post; }
    void PostSet(const MushMeshPosticity& inValue) { m_post=inValue; }
    // Writable reference for m_post
    MushMeshPosticity& PostWRef(void) { return m_post; }
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
//%classPrototypes } F33/hFDOiCw7KeTmvueA5g
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
