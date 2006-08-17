//%includeGuardStart {
#ifndef MUSHGAMEPIECE_H
#define MUSHGAMEPIECE_H
//%includeGuardStart } fXnM4FD/EmJAfw+g836GPQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGamePiece.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } QiW5KaWfX1mBGolg1jxMIg
/*
 * $Id: MushGamePiece.h,v 1.11 2006/08/17 08:57:12 southa Exp $
 * $Log: MushGamePiece.h,v $
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

#include "API/mushMushMesh.h"
#include "API/mushMushGL.h"

//:generate virtual standard ostream xml1
class MushGamePiece : public virtual MushcoreVirtualObject
{
public:
    MushGamePiece(const std::string& inId = "");
    virtual ~MushGamePiece() {}
    virtual void PreControl(MushGameLogic& ioLogic) {}
    virtual void Move(MushGameLogic& ioLogic, const Mushware::tVal inFrameslice) {}
    
    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);

    virtual void TexCoordBuffersNameSet(const std::string& inName) { m_texCoordBuffersRef.NameSet(inName); }

    static Mushware::tRubyValue Klass(void);
    static void RubyInstall(void);
    
private:
    std::string m_id; //:readwrite
    MushMeshPosticity m_post; //:readwrite :wref
    MushMesh4Mesh m_mesh; //:read :wref
    bool m_expireFlag; //:readwrite    
    
    MushGLBuffers::tDataRef m_buffersRef; //:read :wref
    MushGLBuffers::tSharedDataRef m_texCoordBuffersRef; //:read :wref

    MushRubyValue m_rubyObj; //:readwrite
    
    static Mushware::tRubyValue m_rubyKlass;
    
//%classPrototypes {
public:
    const std::string& Id(void) const { return m_id; }
    void IdSet(const std::string& inValue) { m_id=inValue; }
    const MushMeshPosticity& Post(void) const { return m_post; }
    void PostSet(const MushMeshPosticity& inValue) { m_post=inValue; }
    // Writable reference for m_post
    MushMeshPosticity& PostWRef(void) { return m_post; }
    const MushMesh4Mesh& Mesh(void) const { return m_mesh; }
    // Writable reference for m_mesh
    MushMesh4Mesh& MeshWRef(void) { return m_mesh; }
    const bool& ExpireFlag(void) const { return m_expireFlag; }
    void ExpireFlagSet(const bool& inValue) { m_expireFlag=inValue; }
    const MushGLBuffers::tDataRef& BuffersRef(void) const { return m_buffersRef; }
    // Writable reference for m_buffersRef
    MushGLBuffers::tDataRef& BuffersRefWRef(void) { return m_buffersRef; }
    const MushGLBuffers::tSharedDataRef& TexCoordBuffersRef(void) const { return m_texCoordBuffersRef; }
    // Writable reference for m_texCoordBuffersRef
    MushGLBuffers::tSharedDataRef& TexCoordBuffersRefWRef(void) { return m_texCoordBuffersRef; }
    const MushRubyValue& RubyObj(void) const { return m_rubyObj; }
    void RubyObjSet(const MushRubyValue& inValue) { m_rubyObj=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } p5NQC4z4mOjwHXKZ+Le7/g
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
