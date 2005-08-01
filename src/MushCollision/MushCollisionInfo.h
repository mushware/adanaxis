//%includeGuardStart {
#ifndef MUSHCOLLISIONINFO_H
#define MUSHCOLLISIONINFO_H
//%includeGuardStart } xW5fVWSdLoUsDln1OIT+cw
//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionInfo.h
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
//%Header } XC7ySvvC8bbl/ig/EYoMxg
/*
 * $Id$
 * $Log$
 */

//:generate virtual standard ostream xml1
class MushCollisionInfo : public MushcoreVirtualObject
{
public:
    MushCollisionInfo() : m_objectNamesValid(false), m_chunkNumsValid(false) {}
    
private:
    Mushware::tVal m_separatingDistance; //:readwrite
    std::string m_objectName1; //:readwrite
    std::string m_objectName2; //:readwrite
    Mushware::U32 m_chunkNum1; //:readwrite
    Mushware::U32 m_chunkNum2; //:readwrite
    bool m_objectNamesValid; //:readwrite
    bool m_chunkNumsValid; //:readwrite
    
//%classPrototypes {
public:
    const Mushware::tVal& SeparatingDistance(void) const { return m_separatingDistance; }
    void SeparatingDistanceSet(const Mushware::tVal& inValue) { m_separatingDistance=inValue; }
    const std::string& ObjectName1(void) const { return m_objectName1; }
    void ObjectName1Set(const std::string& inValue) { m_objectName1=inValue; }
    const std::string& ObjectName2(void) const { return m_objectName2; }
    void ObjectName2Set(const std::string& inValue) { m_objectName2=inValue; }
    const Mushware::U32& ChunkNum1(void) const { return m_chunkNum1; }
    void ChunkNum1Set(const Mushware::U32& inValue) { m_chunkNum1=inValue; }
    const Mushware::U32& ChunkNum2(void) const { return m_chunkNum2; }
    void ChunkNum2Set(const Mushware::U32& inValue) { m_chunkNum2=inValue; }
    const bool& ObjectNamesValid(void) const { return m_objectNamesValid; }
    void ObjectNamesValidSet(const bool& inValue) { m_objectNamesValid=inValue; }
    const bool& ChunkNumsValid(void) const { return m_chunkNumsValid; }
    void ChunkNumsValidSet(const bool& inValue) { m_chunkNumsValid=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 7rptE1azCoGvB9iJ23fF0g
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushCollisionInfo& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 7fnU7Q7I0EQwaf8MLgCGtg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
