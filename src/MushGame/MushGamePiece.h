//%includeGuardStart {
#ifndef MUSHGAMEPIECE_H
#define MUSHGAMEPIECE_H
//%includeGuardStart } fXnM4FD/EmJAfw+g836GPQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGamePiece.h
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
//%Header } C6Rzkyt1nPacEwGSacFwbQ
/*
 * $Id: MushGamePiece.h,v 1.24 2006/10/17 15:28:02 southa Exp $
 * $Log: MushGamePiece.h,v $
 * Revision 1.24  2006/10/17 15:28:02  southa
 * Player collisions
 *
 * Revision 1.23  2006/10/17 11:05:55  southa
 * Expiry events
 *
 * Revision 1.22  2006/10/16 14:36:51  southa
 * Deco handling
 *
 * Revision 1.21  2006/10/15 17:12:54  southa
 * Scripted explosions
 *
 * Revision 1.20  2006/10/09 16:00:17  southa
 * Intern generation
 *
 * Revision 1.19  2006/10/08 11:31:33  southa
 * Hit points
 *
 * Revision 1.18  2006/10/06 11:54:58  southa
 * Scaled rendering
 *
 * Revision 1.17  2006/10/03 14:06:52  southa
 * Khazi and projectile creation
 *
 * Revision 1.16  2006/10/02 20:28:11  southa
 * Object lookup and target selection
 *
 * Revision 1.15  2006/09/09 11:16:41  southa
 * One-time vertex buffer generation
 *
 * Revision 1.14  2006/08/25 01:44:57  southa
 * Khazi fire
 *
 * Revision 1.13  2006/08/20 14:19:21  southa
 * Seek operation
 *
 * Revision 1.12  2006/08/17 12:18:11  southa
 * Event handling
 *
 * Revision 1.11  2006/08/17 08:57:12  southa
 * Event handling
 *
 * Revision 1.10  2006/06/30 15:05:35  southa
 * Texture and buffer purge
 *
 * Revision 1.9  2006/06/01 15:39:25  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/07/27 18:07:31  southa
 * Collision checking
 *
 * Revision 1.7  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.6  2005/07/07 16:54:17  southa
 * Control tweaks
 *
 * Revision 1.5  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 * Revision 1.4  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 * Revision 1.3  2005/07/01 16:42:54  southa
 * Render work
 *
 * Revision 1.2  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 * Revision 1.1  2005/06/24 10:30:12  southa
 * MushGame camera work
 *
 */

#include "MushGameStandard.h"

class MushGameLogic;
class MushGameMessage;

#include "API/mushMushCollision.h"
#include "API/mushMushMesh.h"
#include "API/mushMushGL.h"

//:generate virtual standard ostream xml1
class MushGamePiece : public virtual MushcoreVirtualObject
{
public:
    MushGamePiece(const std::string& inId = "");
    virtual ~MushGamePiece() {}
    virtual void PreControl(MushGameLogic& ioLogic) {}
    virtual void Move(MushGameLogic& ioLogic, const Mushware::tVal inFrameslice);
    
    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);
    virtual Mushware::tVal HitPointRatio(void) const;

    virtual void ActionValueHandle(MushGameLogic& ioLogic, const MushRubyValue& inActionValue);
    virtual void EventHandle(MushGameLogic& ioLogic, MushRubyValue inEvent, MushRubyValue inParams);
    
    virtual void SharedBuffersNameSet(const std::string& inName) { m_sharedBuffersRef.NameSet(inName); }
    
    virtual void Load(Mushware::tRubyValue inSelf);
    virtual void Save(Mushware::tRubyValue inSelf);
    virtual MushRubyValue RubyEventHandle(const MushRubyValue& inEvent);
    
    // Called from constructor so not virtual
    void RubyPieceConstructor(const std::string& inID, const MushRubyValue& inParams,
                              const MushRubyValue& inKlass);
    void RubyPieceDestructor(void); // nothrow
    
    static Mushware::tRubyValue RubyLoad(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue RubySave(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue Klass(void);

    static Mushware::tRubyValue RubyPost(Mushware::tRubyValue inSelf);
    
    static void RubyInstall(void);
    
private:
    std::string m_id; //:readwrite
    std::string m_meshName; //:readwrite
    MushMeshPosticity m_post; //:readwrite :wref
    MushMesh4Mesh m_mesh; //:readwrite :wref
    Mushware::t4Val m_renderScale; //:readwrite :wref
    Mushware::tMsec m_actionMsec; //:readwrite
    
    bool m_expireFlag; //:readwrite   
    Mushware::tVal m_hitPoints; //:readwrite
    Mushware::tVal m_initialHitPoints; //:readwrite
    Mushware::tVal m_alphaStutter; //:readwrite
    
    MushGLBuffers::tDataRef m_buffersRef; //:read :wref
    MushGLBuffers::tSharedDataRef m_sharedBuffersRef; //:read :wref

    MushRubyValue m_rubyObj; //:readwrite
    MushcoreAutoMonkey m_rubyObjMonkey;
    
    static Mushware::tRubyValue m_rubyKlass; // Must duplicate this in derived classes
    
//%classPrototypes {
public:
    const std::string& Id(void) const { return m_id; }
    void IdSet(const std::string& inValue) { m_id=inValue; }
    const std::string& MeshName(void) const { return m_meshName; }
    void MeshNameSet(const std::string& inValue) { m_meshName=inValue; }
    const MushMeshPosticity& Post(void) const { return m_post; }
    void PostSet(const MushMeshPosticity& inValue) { m_post=inValue; }
    // Writable reference for m_post
    MushMeshPosticity& PostWRef(void) { return m_post; }
    const MushMesh4Mesh& Mesh(void) const { return m_mesh; }
    void MeshSet(const MushMesh4Mesh& inValue) { m_mesh=inValue; }
    // Writable reference for m_mesh
    MushMesh4Mesh& MeshWRef(void) { return m_mesh; }
    const Mushware::t4Val& RenderScale(void) const { return m_renderScale; }
    void RenderScaleSet(const Mushware::t4Val& inValue) { m_renderScale=inValue; }
    // Writable reference for m_renderScale
    Mushware::t4Val& RenderScaleWRef(void) { return m_renderScale; }
    const Mushware::tMsec& ActionMsec(void) const { return m_actionMsec; }
    void ActionMsecSet(const Mushware::tMsec& inValue) { m_actionMsec=inValue; }
    const bool& ExpireFlag(void) const { return m_expireFlag; }
    void ExpireFlagSet(const bool& inValue) { m_expireFlag=inValue; }
    const Mushware::tVal& HitPoints(void) const { return m_hitPoints; }
    void HitPointsSet(const Mushware::tVal& inValue) { m_hitPoints=inValue; }
    const Mushware::tVal& InitialHitPoints(void) const { return m_initialHitPoints; }
    void InitialHitPointsSet(const Mushware::tVal& inValue) { m_initialHitPoints=inValue; }
    const Mushware::tVal& AlphaStutter(void) const { return m_alphaStutter; }
    void AlphaStutterSet(const Mushware::tVal& inValue) { m_alphaStutter=inValue; }
    const MushGLBuffers::tDataRef& BuffersRef(void) const { return m_buffersRef; }
    // Writable reference for m_buffersRef
    MushGLBuffers::tDataRef& BuffersRefWRef(void) { return m_buffersRef; }
    const MushGLBuffers::tSharedDataRef& SharedBuffersRef(void) const { return m_sharedBuffersRef; }
    // Writable reference for m_sharedBuffersRef
    MushGLBuffers::tSharedDataRef& SharedBuffersRefWRef(void) { return m_sharedBuffersRef; }
    const MushRubyValue& RubyObj(void) const { return m_rubyObj; }
    void RubyObjSet(const MushRubyValue& inValue) { m_rubyObj=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 2uX1Pw56raLSBjulPQwRQw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGamePiece& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } hzo4AnwoYg7g4RrSJcViWQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
