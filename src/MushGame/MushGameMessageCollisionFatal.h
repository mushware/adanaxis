//%includeGuardStart {
#ifndef MUSHGAMEMESSAGECOLLISIONFATAL_H
#define MUSHGAMEMESSAGECOLLISIONFATAL_H
//%includeGuardStart } k50WhgWAT/XmvOrJxZe4NA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageCollisionFatal.h
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
//%Header } rNlh4SGSsLajtwTJf4PrQg
/*
 * $Id$
 * $Log$
 */

#include "MushGameStandard.h"

#include "MushGameMessage.h"
#include "MushGameMessageCollision.h"

//:xml1base MushGameMessageCollision
//:generate virtual standard ostream xml1
class MushGameMessageCollisionFatal : public MushGameMessageCollision
{
public:
    MushGameMessageCollisionFatal(const std::string& inID = "") :
        MushGameMessageCollision(inID),
        m_chunkNumsValid(false)
    {}
    
private:
    MushMeshPosticity m_post1; //:readwrite
    MushMeshPosticity m_post2; //:readwrite
    Mushware::U32 m_chunkNum1; //:readwrite
    Mushware::U32 m_chunkNum2; //:readwrite
    bool m_chunkNumsValid; //:readwrite

//%classPrototypes {
public:
    const MushMeshPosticity& Post1(void) const { return m_post1; }
    void Post1Set(const MushMeshPosticity& inValue) { m_post1=inValue; }
    const MushMeshPosticity& Post2(void) const { return m_post2; }
    void Post2Set(const MushMeshPosticity& inValue) { m_post2=inValue; }
    const Mushware::U32& ChunkNum1(void) const { return m_chunkNum1; }
    void ChunkNum1Set(const Mushware::U32& inValue) { m_chunkNum1=inValue; }
    const Mushware::U32& ChunkNum2(void) const { return m_chunkNum2; }
    void ChunkNum2Set(const Mushware::U32& inValue) { m_chunkNum2=inValue; }
    const bool& ChunkNumsValid(void) const { return m_chunkNumsValid; }
    void ChunkNumsValidSet(const bool& inValue) { m_chunkNumsValid=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } Sv3VR7OmiVNMnlncUZW0JA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameMessageCollisionFatal& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } rm48itjc/4h9QFqUzLeQCw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
