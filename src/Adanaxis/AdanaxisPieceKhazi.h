//%includeGuardStart {
#ifndef ADANAXISPIECEKHAZI_H
#define ADANAXISPIECEKHAZI_H
//%includeGuardStart } 1DybVjjopcgdO65Z1fH//g
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceKhazi.h
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
//%Header } 74exA7OMbAKKJXMcA6o41g
/*
 * $Id: AdanaxisPieceKhazi.h,v 1.26 2007/06/06 15:11:21 southa Exp $
 * $Log: AdanaxisPieceKhazi.h,v $
 * Revision 1.26  2007/06/06 15:11:21  southa
 * Level 23
 *
 * Revision 1.25  2007/04/18 09:22:02  southa
 * Header and level fixes
 *
 * Revision 1.24  2007/04/16 08:41:08  southa
 * Level and header mods
 *
 * Revision 1.23  2007/03/13 18:21:37  southa
 * Scanner jamming
 *
 * Revision 1.22  2007/03/13 12:22:51  southa
 * Scanner symbols
 *
 * Revision 1.21  2006/10/30 17:03:51  southa
 * Remnants creation
 *
 * Revision 1.20  2006/10/17 15:28:01  southa
 * Player collisions
 *
 * Revision 1.19  2006/10/17 11:05:55  southa
 * Expiry events
 *
 * Revision 1.18  2006/10/12 22:04:47  southa
 * Collision events
 *
 * Revision 1.17  2006/10/03 14:06:51  southa
 * Khazi and projectile creation
 *
 * Revision 1.16  2006/10/02 20:28:10  southa
 * Object lookup and target selection
 *
 * Revision 1.15  2006/08/24 13:04:38  southa
 * Event handling
 *
 * Revision 1.14  2006/08/20 14:19:20  southa
 * Seek operation
 *
 * Revision 1.13  2006/08/17 12:18:10  southa
 * Event handling
 *
 * Revision 1.12  2006/08/17 08:57:11  southa
 * Event handling
 *
 * Revision 1.11  2006/08/01 17:21:25  southa
 * River demo
 *
 * Revision 1.10  2006/07/24 18:46:47  southa
 * Depth sorting
 *
 * Revision 1.9  2006/06/30 15:05:31  southa
 * Texture and buffer purge
 *
 * Revision 1.8  2006/06/21 12:17:55  southa
 * Ruby object generation
 *
 * Revision 1.7  2006/06/01 15:38:47  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/09/05 12:54:29  southa
 * Solid rendering work
 *
 * Revision 1.5  2005/09/03 17:05:36  southa
 * Material work
 *
 * Revision 1.4  2005/08/01 17:58:51  southa
 * Object explosion
 *
 * Revision 1.3  2005/08/01 13:09:57  southa
 * Collision messaging
 *
 * Revision 1.2  2005/07/29 08:27:46  southa
 * Collision work
 *
 * Revision 1.1  2005/07/19 10:08:06  southa
 * Adanaxis work
 *
 */

#include "AdanaxisStandard.h"

#include "AdanaxisPiece.h"

#include "API/mushMushCollision.h"
#include "API/mushMushGL.h"
#include "API/mushMushMesh.h"
#include "API/mushMushRender.h"

//:xml1base MushGamePiece
//:generate virtual standard ostream xml1
class AdanaxisPieceKhazi : public MushGamePiece, public MushCollisionPiece
{
public:
    explicit AdanaxisPieceKhazi(const std::string& inID = "", const MushRubyValue& inParams = MushRubyValue());
    virtual ~AdanaxisPieceKhazi();

    virtual void Move(MushGameLogic& ioLogic, const Mushware::tVal inFrameslice);
    virtual bool Render(MushGLJobRender& outRender,
                        MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera);
    
    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);

    virtual const MushMesh4Mesh& CollisionMesh(void) const { return Mesh(); }
    virtual const MushMeshPosticity& CollisionPost(void) const { return Post(); }
    virtual void EventHandle(MushGameLogic& ioLogic, MushRubyValue inEvent, MushRubyValue inParams);
    
    virtual void Load(Mushware::tRubyValue inSelf);
    virtual void Save(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue RubyCreate(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    
    static Mushware::tRubyValue Klass(void);
    static void RubyInstall(void);
    
protected:
    
private:
    Mushware::U32 m_scannerSymbol; //:readwrite
    bool m_isJammer; //:readwrite
    bool m_isStealth; //:readwrite
    
    static Mushware::tRubyValue m_rubyKlass;

//%classPrototypes {
public:
    const Mushware::U32& ScannerSymbol(void) const { return m_scannerSymbol; }
    void ScannerSymbolSet(const Mushware::U32& inValue) { m_scannerSymbol=inValue; }
    const bool& IsJammer(void) const { return m_isJammer; }
    void IsJammerSet(const bool& inValue) { m_isJammer=inValue; }
    const bool& IsStealth(void) const { return m_isStealth; }
    void IsStealthSet(const bool& inValue) { m_isStealth=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } doY/2Qujnfmewd2xoRaAAA
};

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisPieceKhazi& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } blutLiRI/IwJMUW7CKPkuA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
