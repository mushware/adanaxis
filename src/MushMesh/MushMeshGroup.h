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
 * $Id: MushMeshGroup.h,v 1.1 2005/01/26 00:48:46 southa Exp $
 * $Log: MushMeshGroup.h,v $
 * Revision 1.1  2005/01/26 00:48:46  southa
 * MushMeshGroup and rendering
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshMushcoreIO.h"
#include "MushMeshUtils.h"

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
    MushMeshUtils::BoundsCheck(inSuperGroup, m_group.size());
    MushMeshUtils::BoundsCheck(inGroup, m_group[inSuperGroup].size());
    MushMeshUtils::BoundsCheck(inIndex, m_group[inSuperGroup][inGroup].size());

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
    MushMeshUtils::BoundsCheck(inSuperGroup, m_group.size());
    return m_group[inSuperGroup];
}

inline MushMeshGroup::tSuperGroup&
MushMeshGroup::SuperGroup(const tSize inSuperGroup)
{
    MushMeshUtils::BoundsCheck(inSuperGroup, m_group.size());
    return m_group[inSuperGroup];
}

inline const MushMeshGroup::tGroup&
MushMeshGroup::GroupAtSuperGroupGroup(const tSize inSuperGroup, const tSize inGroup) const
{
    MushMeshUtils::BoundsCheck(inSuperGroup, m_group.size());
    MushMeshUtils::BoundsCheck(inGroup, m_group[inSuperGroup].size());
    return m_group[inSuperGroup][inGroup];
}

inline MushMeshGroup::tGroup&
MushMeshGroup::GroupAtSuperGroupGroup(const tSize inSuperGroup, const tSize inGroup)
{
    MushMeshUtils::BoundsCheck(inSuperGroup, m_group.size());
    MushMeshUtils::BoundsCheck(inGroup, m_group[inSuperGroup].size());
    return m_group[inSuperGroup][inGroup];
}

inline void
MushMeshGroup::ValuePush(const tValue inVal)
{
    MushMeshUtils::BoundsCheck(0, m_group.size());
    MushMeshUtils::BoundsCheck(0, m_group.back().size());
    m_group.back().back().push_back(inVal);
}

inline void
MushMeshGroup::GroupPush(const tGroup inVal)
{
    MushMeshUtils::BoundsCheck(0, m_group.size());
    m_group.back().push_back(inVal);
}

inline const MushMeshGroup::tSize
MushMeshGroup::SuperGroupSize(const tSize inSuperGroup) const
{
    MushMeshUtils::BoundsCheck(inSuperGroup, m_group.size());
    return m_group[inSuperGroup].size();
}

inline const MushMeshGroup::tSize
MushMeshGroup::GroupSize(const tSize inSuperGroup, const tSize inGroup) const
{
    MushMeshUtils::BoundsCheck(inSuperGroup, m_group.size());
    MushMeshUtils::BoundsCheck(inGroup, m_group[inSuperGroup].size());
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
