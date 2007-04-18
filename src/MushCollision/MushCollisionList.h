//%includeGuardStart {
#ifndef MUSHCOLLISIONLIST_H
#define MUSHCOLLISIONLIST_H
//%includeGuardStart } RjnI1PZh5MrTQsvhqXyLPQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionList.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } NxWBAqVa0K+ReYo9vzm/fA
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
