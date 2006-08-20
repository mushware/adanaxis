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
 * software licence version 1.1, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Bm3nTDDsM5QE9iTgAOLr3w
/*
 * $Id: AdanaxisPieceKhazi.h,v 1.13 2006/08/17 12:18:10 southa Exp $
 * $Log: AdanaxisPieceKhazi.h,v $
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
    virtual ~AdanaxisPieceKhazi();

    virtual void Initialise(MushGameLogic& ioLogic);
    virtual void Move(MushGameLogic& ioLogic, const Mushware::tVal inFrameslice);
    virtual bool Render(MushGLJobRender& outRender,
                        MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera);
    
    virtual void CollisionFatalConsume(MushGameLogic& ioLogic, const MushGameMessageCollisionFatal& inMessage);
    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);

    virtual const MushMesh4Mesh& CollisionMesh(void) const { return Mesh(); }
    virtual const MushMeshPosticity& CollisionPost(void) const { return Post(); }
    virtual void ActionValueHandle(MushGameLogic& ioLogic, const MushRubyValue& inActionValue);
    virtual void EventHandle(MushGameLogic& ioLogic, MushRubyValue inEvent, MushRubyValue inParams);
    
    static Mushware::tRubyValue RubyPostLoad(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue RubyPostSave(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue Klass(void);
    static void RubyInstall(void);
    
protected:
    virtual void Explode(MushGameLogic& ioLogic, const MushGameMessageCollisionFatal& inMessage);
    
private:
    bool m_initialised;
    Mushware::tMsec m_actionMsec;
        
    static Mushware::tRubyValue m_rubyKlass;

//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
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
