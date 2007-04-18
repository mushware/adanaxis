//%includeGuardStart {
#ifndef MUSHMESHGROUP_H
#define MUSHMESHGROUP_H
//%includeGuardStart } 9fIFttytEvMqtk2wNgRXKw
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshGroup.h
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
//%Header } UGv2U/eTAOH9WHo7rPvZJA
/*
 * $Id: MushMeshGroup.h,v 1.7 2006/06/01 15:39:30 southa Exp $
 * $Log: MushMeshGroup.h,v $
 * Revision 1.7  2006/06/01 15:39:30  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.5  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.4  2005/05/19 13:02:10  southa
 * Mac release work
 *
 * Revision 1.3  2005/02/10 12:34:05  southa
 * Template fixes
 *
 * Revision 1.2  2005/01/27 21:00:39  southa
 * Division and rendering
 *
 * Revision 1.1  2005/01/26 00:48:46  southa
 * MushMeshGroup and rendering
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshMushcoreIO.h"

/* Terminology
 *
 * At the top level there are supergroups.  Each supergroup is referred to
 * by its order.  There is a single order 0 supergroup, a single order 1
 * supergroup, and so on.
 *
 * Each supergroup contains a variable number of groups.
 *
 * Each group contains a various number of end values.
 *
 * Storage is in m_group, a three dimensional array.  A particular end
 * value exists at
 *
 * m_group[superGroup][group][index]
 *
 */

//:generate ostream
class MushMeshGroup
{
public:
     // Index/size for std::vector
    typedef std::size_t tSize;
    
     // End value - what the group actually stores
    typedef Mushware::U32 tValue;

    // Group type and iterators
    typedef std::vector<tValue> tGroup;
    typedef tGroup::const_iterator tGroupConstItr;
    typedef tGroup::iterator tGroupItr;

    // Supergroup type and iterators
    typedef std::vector<tGroup> tSuperGroup;
    typedef tSuperGroup::iterator tSuperGroupItr;
    typedef tSuperGroup::const_iterator tSuperGroupConstItr;

    // Order type and iterators
    typedef std::vector<tSuperGroup> tOrder;
    typedef tOrder::iterator tOrderItr;
    typedef tOrder::const_iterator tOrderConstItr;
    typedef tOrder::reverse_iterator tOrderRevItr;
    typedef tOrder::const_reverse_iterator tOrderConstRevItr;
    
    virtual ~MushMeshGroup() {}
    
    void ValuePush(const tValue inVal = tValue());
    void GroupPush(const tGroup inVal = tGroup());
    void SuperGroupPush(const tSuperGroup inVal = tSuperGroup()) { m_group.push_back(inVal); }

    const tSuperGroup& SuperGroup(const tSize inSuperGroup) const;
    tSuperGroup& SuperGroup(const tSize inSuperGroup);
    const tGroup& GroupAtSuperGroupGroup(const tSize inSuperGroup, const tSize inGroup) const;
    tGroup& GroupAtSuperGroupGroup(const tSize inSuperGroup, const tSize inGroup);
    
    const tValue Value(const tSize inSuperGroup, const tSize inGroup, const tSize inIndex) const;
    void ValueAdd(const tValue inVal, const tSize inSuperGroup, const tSize inGroup, const tSize inIndex); 

    const tSize SuperGroupSize(const tSize inSuperGroup) const;
    const tSize GroupSize(const tSize inSuperGroup, const tSize inGroup) const;
    
    void OrderResize(const tSize inSize) { m_group.resize(inSize); }
    tSize OrderSize() const { return m_group.size(); }
    
    tOrderItr OrderBegin() { return m_group.begin(); }
    tOrderItr OrderEnd() { return m_group.end(); }
    tOrderRevItr OrderRBegin() { return m_group.rbegin(); }
    tOrderRevItr OrderREnd() { return m_group.rend(); }
    
private:
    // Unimplemented stuff
    void ValueAtSuperGroupGroupIndexSet(const tValue inVal);
    void ValueToSuperGroupGroupPush(const tSize inSuperGroup, const tSize inGroup, const tValue inVal = tValue());
    void GroupToSuperGroupPush(const tSize inOrder, const tGroup inVal = tGroup());
    
private:    
    tOrder m_group;
//%classPrototypes {
public:
    virtual void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } b86DSDsq8lQQbiM0rrNtkg
};

inline const MushMeshGroup::tValue
MushMeshGroup::Value(const tSize inSuperGroup, const tSize inGroup, const tSize inIndex) const
{
    MushcoreUtil::BoundsCheck(inSuperGroup, m_group.size());
    MushcoreUtil::BoundsCheck(inGroup, m_group[inSuperGroup].size());
    MushcoreUtil::BoundsCheck(inIndex, m_group[inSuperGroup][inGroup].size());

    return m_group[inSuperGroup][inGroup][inIndex];
}

inline void
MushMeshGroup::ValueAdd(const tValue inVal, const tSize inSuperGroup, const tSize inGroup, const tSize inIndex)
{
    if (inSuperGroup >= m_group.size())
    {
        m_group.resize(inSuperGroup+1);
    }
    if (inGroup >= m_group[inSuperGroup].size())
    {
        m_group[inSuperGroup].resize(inGroup+1);
    }
    if (inIndex >= m_group[inSuperGroup][inGroup].size())
    {
        m_group[inSuperGroup][inGroup].resize(inIndex+1);
    }
    m_group[inSuperGroup][inGroup][inIndex] = inVal;
}

inline const MushMeshGroup::tSuperGroup&
MushMeshGroup::SuperGroup(const tSize inSuperGroup) const
{
    MushcoreUtil::BoundsCheck(inSuperGroup, m_group.size());
    return m_group[inSuperGroup];
}

inline MushMeshGroup::tSuperGroup&
MushMeshGroup::SuperGroup(const tSize inSuperGroup)
{
    MushcoreUtil::BoundsCheck(inSuperGroup, m_group.size());
    return m_group[inSuperGroup];
}

inline const MushMeshGroup::tGroup&
MushMeshGroup::GroupAtSuperGroupGroup(const tSize inSuperGroup, const tSize inGroup) const
{
    MushcoreUtil::BoundsCheck(inSuperGroup, m_group.size());
    MushcoreUtil::BoundsCheck(inGroup, m_group[inSuperGroup].size());
    return m_group[inSuperGroup][inGroup];
}

inline MushMeshGroup::tGroup&
MushMeshGroup::GroupAtSuperGroupGroup(const tSize inSuperGroup, const tSize inGroup)
{
    MushcoreUtil::BoundsCheck(inSuperGroup, m_group.size());
    MushcoreUtil::BoundsCheck(inGroup, m_group[inSuperGroup].size());
    return m_group[inSuperGroup][inGroup];
}

inline void
MushMeshGroup::ValuePush(const tValue inVal)
{
    MushcoreUtil::BoundsCheck(0, m_group.size());
    MushcoreUtil::BoundsCheck(0, m_group.back().size());
    m_group.back().back().push_back(inVal);
}

inline void
MushMeshGroup::GroupPush(const tGroup inVal)
{
    MushcoreUtil::BoundsCheck(0, m_group.size());
    m_group.back().push_back(inVal);
}

inline const MushMeshGroup::tSize
MushMeshGroup::SuperGroupSize(const tSize inSuperGroup) const
{
    MushcoreUtil::BoundsCheck(inSuperGroup, m_group.size());
    return m_group[inSuperGroup].size();
}

inline const MushMeshGroup::tSize
MushMeshGroup::GroupSize(const tSize inSuperGroup, const tSize inGroup) const
{
    MushcoreUtil::BoundsCheck(inSuperGroup, m_group.size());
    MushcoreUtil::BoundsCheck(inGroup, m_group[inSuperGroup].size());
    return m_group[inSuperGroup][inGroup].size();
}

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
