//%includeGuardStart {
#ifndef MUSHGAMEMESSAGECOLLISION_H
#define MUSHGAMEMESSAGECOLLISION_H
//%includeGuardStart } QPQrOeEYWhDLCHjfAmk7Gg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageCollision.h
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
//%Header } RYSJOizl5rl474TJ4t29Dw
/*
 * $Id: MushGameMessageCollision.h,v 1.3 2006/10/12 22:04:49 southa Exp $
 * $Log: MushGameMessageCollision.h,v $
 * Revision 1.3  2006/10/12 22:04:49  southa
 * Collision events
 *
 * Revision 1.2  2006/06/01 15:39:24  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/08/01 13:09:58  southa
 * Collision messaging
 *
 */

#include "MushGameStandard.h"

#include "MushGameMessage.h"
#include "MushGamePiece.h"

//:xml1base MushGameMessage
//:generate virtual standard ostream xml1
class MushGameMessageCollision : public MushGameMessage
{
public:
    explicit MushGameMessageCollision(const std::string& inID = "") :
        MushGameMessage(inID),
        m_chunkNumsValid(false),
        m_piecesValid(false)
    {}

    MushGamePiece *Piece1(void) const { return m_piece1; }
    void Piece1Set(MushGamePiece *inValue) { m_piece1=inValue; }
    MushGamePiece *Piece2(void) const { return m_piece2; }
    void Piece2Set(MushGamePiece *inValue) { m_piece2=inValue; }
    
    Mushware::tRubyValue RubyObjectMake(void);
    
private:
    std::string m_objectName1; //:readwrite
    std::string m_objectName2; //:readwrite
    MushGamePiece *m_piece1;
    MushGamePiece *m_piece2;    
    Mushware::U32 m_chunkNum1; //:readwrite
    Mushware::U32 m_chunkNum2; //:readwrite
    Mushware::t4Val m_collisionPoint; //:readwrite
    bool m_chunkNumsValid; //:readwrite
    bool m_piecesValid; //:readwrite
    bool m_collisionPointValid; //:readwrite
    
//%classPrototypes {
public:
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
    const bool& ChunkNumsValid(void) const { return m_chunkNumsValid; }
    void ChunkNumsValidSet(const bool& inValue) { m_chunkNumsValid=inValue; }
    const bool& PiecesValid(void) const { return m_piecesValid; }
    void PiecesValidSet(const bool& inValue) { m_piecesValid=inValue; }
    const bool& CollisionPointValid(void) const { return m_collisionPointValid; }
    void CollisionPointValidSet(const bool& inValue) { m_collisionPointValid=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } skRaTHfC4tp4yYpymkLbxA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameMessageCollision& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 7rke0whDQgrG8sneg+XDNw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
