//%includeGuardStart {
#ifndef MUSHMESHGROUP_H
#define MUSHMESHGROUP_H
//%includeGuardStart } 9fIFttytEvMqtk2wNgRXKw
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshGroup.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } dTlN3WjcCsNnDgQwcIUF1A
/*
 * $Id$
 * $Log$
 */

#include "MushMeshStandard.h"

#include "MushMeshMushcoreIO.h"
#include "MushMeshUtils.h"

//:generate ostream
class MushMeshGroup
{
public:
    typedef Mushware::U32 tIndex;
    typedef std::vector<tIndex> tGroup;
    typedef tGroup::iterator tGroupIterator;
    typedef std::vector<tGroup> tSuperGroup;
    typedef tSuperGroup::iterator tSuperGroupIterator;
    typedef std::vector<tSuperGroup> tOrder;
    typedef tOrder::iterator tOrderIterator;
    typedef tOrder::reverse_iterator tOrderReverseIterator;
    
    virtual ~MushMeshGroup() {}
    
    void IndexPush(const tIndex inVal = tIndex()) { m_group.back().back().push_back(inVal); }
    void GroupPush(const tGroup inVal = tGroup()) { m_group.back().push_back(inVal); }
    void OrderPush(const tSuperGroup inVal = tSuperGroup()) { m_group.push_back(inVal); }
    
    tOrderIterator OrderBegin() { return m_group.begin(); }
    tOrderIterator OrderEnd() { return m_group.end(); }
    tOrderReverseIterator OrderRBegin() { return m_group.rbegin(); }
    tOrderReverseIterator OrderREnd() { return m_group.rend(); }
    
private:    
    tOrder m_group;
//%classPrototypes {
public:
    virtual void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } b86DSDsq8lQQbiM0rrNtkg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshGroup& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } LezDd6cNeuEDG2Fmz/Y4mg

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
