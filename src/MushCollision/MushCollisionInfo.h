//%includeGuardStart {
#ifndef MUSHCOLLISIONINFO_H
#define MUSHCOLLISIONINFO_H
//%includeGuardStart } xW5fVWSdLoUsDln1OIT+cw
//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionInfo.h
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
//%Header } CH/ckZKHjAvgndOqhMVIiA
/*
 * $Id: MushCollisionInfo.h,v 1.4 2006/10/12 22:04:48 southa Exp $
 * $Log: MushCollisionInfo.h,v $
 * Revision 1.4  2006/10/12 22:04:48  southa
 * Collision events
 *
 * Revision 1.3  2006/06/01 15:39:15  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/08/01 20:24:03  southa
 * Backdrop and build fixes
 *
 * Revision 1.1  2005/08/01 13:09:57  southa
 * Collision messaging
 *
 */


#include "MushCollisionStandard.h"

//:generate virtual standard ostream xml1
class MushCollisionInfo : public MushcoreVirtualObject
{
public:
    MushCollisionInfo() : m_objectNamesValid(false), m_chunkNumsValid(false), m_collisionPointValid(false) {}
    
private:
    Mushware::tVal m_separatingDistance; //:readwrite
    std::string m_objectName1; //:readwrite
    std::string m_objectName2; //:readwrite
    Mushware::U32 m_chunkNum1; //:readwrite
    Mushware::U32 m_chunkNum2; //:readwrite
    Mushware::t4Val m_collisionPoint; //:readwrite
    bool m_objectNamesValid; //:readwrite
    bool m_chunkNumsValid; //:readwrite
    bool m_objectPointersValid; //:readwrite
    bool m_collisionPointValid; //:readwrite
    
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
    const Mushware::t4Val& CollisionPoint(void) const { return m_collisionPoint; }
    void CollisionPointSet(const Mushware::t4Val& inValue) { m_collisionPoint=inValue; }
    const bool& ObjectNamesValid(void) const { return m_objectNamesValid; }
    void ObjectNamesValidSet(const bool& inValue) { m_objectNamesValid=inValue; }
    const bool& ChunkNumsValid(void) const { return m_chunkNumsValid; }
    void ChunkNumsValidSet(const bool& inValue) { m_chunkNumsValid=inValue; }
    const bool& ObjectPointersValid(void) const { return m_objectPointersValid; }
    void ObjectPointersValidSet(const bool& inValue) { m_objectPointersValid=inValue; }
    const bool& CollisionPointValid(void) const { return m_collisionPointValid; }
    void CollisionPointValidSet(const bool& inValue) { m_collisionPointValid=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } NkEXN9Y/nsbsukoDOFr7mw
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
