//%includeGuardStart {
#ifndef MUSHGAMEMESSAGE_H
#define MUSHGAMEMESSAGE_H
//%includeGuardStart } AuJtZN1+Qznoby6CEcmFkg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessage.h
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
//%Header } RnfBTssvKEC42xNFd5qXwA
/*
 * $Id: MushGameMessage.h,v 1.6 2006/06/27 11:58:09 southa Exp $
 * $Log
 */

#include "MushGameStandard.h"

#include "MushGameAddress.h"

//:generate virtual standard ostream xml1
class MushGameMessage : public MushcoreVirtualObject
{
public:
    explicit MushGameMessage(const std::string& inID = "") : m_id(inID) { ++m_instanceCounter; }
    
    MushGameMessage(const MushGameMessage& inObj) : MushcoreVirtualObject(),
        m_srcAddrRef(inObj.m_srcAddrRef),
        m_id(inObj.m_id)    
    {
            ++m_instanceCounter;
    }
    virtual ~MushGameMessage() { --m_instanceCounter; }
    
private:
    MushcoreDataRef<MushGameAddress> m_srcAddrRef; //:xmlignore :readwrite
    std::string m_id; //:readwrite
    static Mushware::S32 m_instanceCounter; //:readwrite
        
//%classPrototypes {
public:
    const MushcoreDataRef<MushGameAddress>& SrcAddrRef(void) const { return m_srcAddrRef; }
    void SrcAddrRefSet(const MushcoreDataRef<MushGameAddress>& inValue) { m_srcAddrRef=inValue; }
    const std::string& Id(void) const { return m_id; }
    void IdSet(const std::string& inValue) { m_id=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 50R194PmRusVUXoMrok/1A
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameMessage& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } XHukHzRIO+OljzoePNw14w
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
