//%includeGuardStart {
#ifndef MUSHGAMEADDRESS_H
#define MUSHGAMEADDRESS_H
//%includeGuardStart } L8/7BLdqwh1+COyQm5NWvw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameAddress.h
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
//%Header } tNaJVrjsdhtRwzD4kot+Iw
/*
 * $Id: MushGameAddress.h,v 1.3 2006/06/01 15:39:19 southa Exp $
 * $Log: MushGameAddress.h,v $
 * Revision 1.3  2006/06/01 15:39:19  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/06/23 11:58:28  southa
 * MushGame link work
 *
 * Revision 1.1  2005/06/22 20:01:58  southa
 * MushGame link work
 *
 */

#include "MushGameStandard.h"

class MushGameLink;

//:generate virtual standard ostream xml1
class MushGameAddress : public MushcoreVirtualObject
{
public:
    MushGameAddress() {}
    explicit MushGameAddress(const std::string& inName);
    virtual ~MushGameAddress() {}
    const std::string& Name(void) const { return m_name; }
    virtual void NameSet(const std::string& inValue) { m_name=inValue; m_linkRef.NameSet(m_name); }
    
private:
    std::string m_name;
    MushcoreDataRef<MushGameLink> m_linkRef; //:readwrite :wref

//%classPrototypes {
public:
    const MushcoreDataRef<MushGameLink>& LinkRef(void) const { return m_linkRef; }
    void LinkRefSet(const MushcoreDataRef<MushGameLink>& inValue) { m_linkRef=inValue; }
    // Writable reference for m_linkRef
    MushcoreDataRef<MushGameLink>& LinkRefWRef(void) { return m_linkRef; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } M40yAD0sQnsx4C7/XGw2AQ
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameAddress& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } hRmbmkNx+6bS+4XgtVFp+Q
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
