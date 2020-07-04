//%includeGuardStart {
#ifndef MUSHGAMEDIGEST_H
#define MUSHGAMEDIGEST_H
//%includeGuardStart } UTdLACVl8zAuBSOebfTrvQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameDigest.h
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
//%Header } JMbo7ykckMfNuL+qynz7Fg
/*
 * $Id: MushGameDigest.h,v 1.4 2006/06/01 15:39:21 southa Exp $
 * $Log: MushGameDigest.h,v $
 * Revision 1.4  2006/06/01 15:39:21  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/06/20 16:14:30  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/20 14:30:36  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 10:48:59  southa
 * Client/server work
 *
 */

#include "MushGameStandard.h"

#include "MushGameMessage.h"

//:generate virtual standard ostream xml1
class MushGameDigest : public MushcoreVirtualObject
{
public:
    MushGameDigest();
    virtual ~MushGameDigest() {}
    virtual void Give(MushGameMessage *iopMessage);
    virtual bool TakeIfAvailable(MushGameMessage *& iopMessage);
    
private:
    Mushware::U32 m_digestID; //:readwrite
    std::deque<MushGameMessage *> m_deque;
    
//%classPrototypes {
public:
    const Mushware::U32& DigestID(void) const { return m_digestID; }
    void DigestIDSet(const Mushware::U32& inValue) { m_digestID=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } rYWAYE1irJJ/I55hzbYJew
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameDigest& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } RRbv32opygA93qNKNAusHw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
