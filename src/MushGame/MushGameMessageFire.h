//%includeGuardStart {
#ifndef MUSHGAMEMESSAGEFIRE_H
#define MUSHGAMEMESSAGEFIRE_H
//%includeGuardStart } 2NfNeCIksTDYOzOKngtC6A
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageFire.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } 4NhrcRtJd1jVq6H7oDAUjA
/*
 * $Id: MushGameMessageFire.h,v 1.3 2006/06/01 15:39:24 southa Exp $
 * $Log: MushGameMessageFire.h,v $
 * Revision 1.3  2006/06/01 15:39:24  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
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
