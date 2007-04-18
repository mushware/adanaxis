//%includeGuardStart {
#ifndef ADANAXISPIECEDECO_H
#define ADANAXISPIECEDECO_H
//%includeGuardStart } oqn4Y6tbxdOzvAL0fqtoXA
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceDeco.h
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.3, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 0362QeAIPpLpHkqDpB0oKA
/*
 * $Id: AdanaxisPieceDeco.h,v 1.13 2006/10/30 17:03:51 southa Exp $
 * $Log: AdanaxisPieceDeco.h,v $
 * Revision 1.13  2006/10/30 17:03:51  southa
 * Remnants creation
 *
 * Revision 1.12  2006/10/14 16:59:44  southa
 * Ruby Deco objects
 *
 * Revision 1.11  2006/08/01 17:21:25  southa
 * River demo
 *
 * Revision 1.10  2006/07/24 18:46:46  southa
 * Depth sorting
 *
 * Revision 1.9  2006/07/19 14:34:51  southa
 * Flare effects
 *
 * Revision 1.8  2006/06/30 15:05:31  southa
 * Texture and buffer purge
 *
 * Revision 1.7  2006/06/21 16:52:28  southa
 * Deco objects
 *
 * Revision 1.6  2006/06/01 15:38:47  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/07/12 12:18:17  southa
 * Projectile work
 *
 * Revision 1.4  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 * Revision 1.3  2005/07/01 10:36:46  southa
 * MushRender work
 *
 * Revision 1.2  2005/06/30 16:29:24  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/30 14:26:35  southa
 * Adanaxis work
 *
 */

#include "AdanaxisStandard.h"

#include "AdanaxisPiece.h"

#include "API/mushMushGL.h"
#include "API/mushMushMesh.h"
#include "API/mushMushRender.h"

//:xml1base MushGamePiece
//:generate virtual standard ostream xml1
class AdanaxisPieceDeco : public MushGamePiece
{
public:
    explicit AdanaxisPieceDeco(const std::string& inID = "", const MushRubyValue& inParams = MushRubyValue());
    virtual ~AdanaxisPieceDeco();
    
    virtual void Move(MushGameLogic& ioLogic, const Mushware::tVal inFrameSlice);
    virtual bool Render(MushGLJobRender& outRender,
                        MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera);

    virtual void Load(Mushware::tRubyValue inSelf);
    virtual void Save(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue RubyCreate(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue Klass(void);
    static void RubyInstall(void);

private:
    Mushware::tMsec m_lifeMsec; //:readwrite
    Mushware::tMsec m_launchMsec; //:readwrite
    
    static Mushware::tRubyValue m_rubyKlass; // Must duplicate this in derived classes
    
//%classPrototypes {
public:
    const Mushware::tMsec& LifeMsec(void) const { return m_lifeMsec; }
    void LifeMsecSet(const Mushware::tMsec& inValue) { m_lifeMsec=inValue; }
    const Mushware::tMsec& LaunchMsec(void) const { return m_launchMsec; }
    void LaunchMsecSet(const Mushware::tMsec& inValue) { m_launchMsec=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } gxBR9acaUSIzCXPdKsrH1A
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisPieceDeco& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } U59qcX7inEXnV9haw5/Q8Q
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
