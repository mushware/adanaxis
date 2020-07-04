//%includeGuardStart {
#ifndef MUSHGAMEMESSAGECOLLISIONFATAL_H
#define MUSHGAMEMESSAGECOLLISIONFATAL_H
//%includeGuardStart } k50WhgWAT/XmvOrJxZe4NA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageCollisionFatal.h
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
//%Header } ErGQXAVY2CsSEdC9DsVCdw
/*
 * $Id: MushGameMessageCollisionFatal.h,v 1.2 2006/06/01 15:39:24 southa Exp $
 * $Log: MushGameMessageCollisionFatal.h,v $
 * Revision 1.2  2006/06/01 15:39:24  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/08/01 13:09:58  southa
 * Collision messaging
 *
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
