//%includeGuardStart {
#ifndef MUSHCOLLISIONLIST_H
#define MUSHCOLLISIONLIST_H
//%includeGuardStart } RjnI1PZh5MrTQsvhqXyLPQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionList.h
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
//%Header } rt9w+XErFgaPukpHJBS/3w
/*
 * $Id: MushCollisionList.h,v 1.2 2006/06/01 15:39:15 southa Exp $
 * $Log: MushCollisionList.h,v $
 * Revision 1.2  2006/06/01 15:39:15  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/27 18:09:59  southa
 * Collision checking
 *
 */

#include "MushCollisionStandard.h"

#include "MushCollisionListEntry.h"

//:generate standard ostream xml1
class MushCollisionList : public MushcoreVirtualObject
{
public:
    typedef MushCollisionListEntry *tListEntry;
    typedef std::list<tListEntry> tList;
    
private:
    tList m_list; //:readwrite :wref
//%classPrototypes {
public:
    const tList& List(void) const { return m_list; }
    void ListSet(const tList& inValue) { m_list=inValue; }
    // Writable reference for m_list
    tList& ListWRef(void) { return m_list; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 77r+pOgBUkhEW5WZOiu/Jg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushCollisionList& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } xKr6lzHkbXOI9uu0yhuKXA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
