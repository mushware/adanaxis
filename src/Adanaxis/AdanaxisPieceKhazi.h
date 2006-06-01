//%includeGuardStart {
#ifndef ADANAXISPIECEKHAZI_H
#define ADANAXISPIECEKHAZI_H
//%includeGuardStart } 1DybVjjopcgdO65Z1fH//g
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceKhazi.h
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } zxudYl+J614B+ona+VDSzQ
/*
 * $Id: AdanaxisPieceKhazi.h,v 1.6 2005/09/05 12:54:29 southa Exp $
 * $Log: AdanaxisPieceKhazi.h,v $
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

#include "API/mushMushCollision.h"
#include "API/mushMushGame.h"
#include "API/mushMushGL.h"
#include "API/mushMushMesh.h"
#include "API/mushMushRender.h"

//:xml1base MushGamePiece
//:generate virtual standard ostream xml1
class AdanaxisPieceKhazi : public MushGamePiece, public MushCollisionPiece
{
public:
    explicit AdanaxisPieceKhazi(const std::string& inID = "");
    virtual ~AdanaxisPieceKhazi() {}

    virtual void Move(MushGameLogic& ioLogic, const Mushware::tVal inFrameslice);
    virtual void Render(MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera);
    
    virtual void CollisionFatalConsume(MushGameLogic& ioLogic, const MushGameMessageCollisionFatal& inMessage);
    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);

    virtual const MushMesh4Mesh& CollisionMesh(void) const { return m_mesh; }
    virtual const MushMeshPosticity& CollisionPost(void) const { return Post(); }

    virtual void TexCoordBuffersNameSet(const std::string& inName) { m_texCoordBuffersRef.NameSet(inName); }
    
protected:
    virtual void Explode(MushGameLogic& ioLogic, const MushGameMessageCollisionFatal& inMessage);
    
private:
    std::string m_id; //:readwrite
    bool m_expireFlag; //:readwrite
    MushMesh4Mesh m_mesh; //:readwrite :wref
    MushGLBuffers::tDataRef m_buffersRef; //:readwrite
    MushGLBuffers::tSharedDataRef m_texCoordBuffersRef; //:readwrite
        
//%classPrototypes {
public:
    const std::string& Id(void) const { return m_id; }
    void IdSet(const std::string& inValue) { m_id=inValue; }
    const bool& ExpireFlag(void) const { return m_expireFlag; }
    void ExpireFlagSet(const bool& inValue) { m_expireFlag=inValue; }
    const MushMesh4Mesh& Mesh(void) const { return m_mesh; }
    void MeshSet(const MushMesh4Mesh& inValue) { m_mesh=inValue; }
    // Writable reference for m_mesh
    MushMesh4Mesh& MeshWRef(void) { return m_mesh; }
    const MushGLBuffers::tDataRef& BuffersRef(void) const { return m_buffersRef; }
    void BuffersRefSet(const MushGLBuffers::tDataRef& inValue) { m_buffersRef=inValue; }
    const MushGLBuffers::tSharedDataRef& TexCoordBuffersRef(void) const { return m_texCoordBuffersRef; }
    void TexCoordBuffersRefSet(const MushGLBuffers::tSharedDataRef& inValue) { m_texCoordBuffersRef=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } Slgxgt2LdHfWwvnW2K7VTQ
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
