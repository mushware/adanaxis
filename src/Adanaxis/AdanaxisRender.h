//%includeGuardStart {
#ifndef ADANAXISRENDER_H
#define ADANAXISRENDER_H
//%includeGuardStart } dZcfmpPUzEwmX2Q78sGR/A
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisRender.h
 *
 * Copyright: Andy Southgate 2005
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
//%Header } ApiIiDIkgHS1hGasLAa6EQ
/*
 * $Id: AdanaxisRender.h,v 1.3 2005/07/02 00:42:36 southa Exp $
 * $Log: AdanaxisRender.h,v $
 * Revision 1.3  2005/07/02 00:42:36  southa
 * Conditioning tweaks
 *
 * Revision 1.2  2005/07/01 10:03:30  southa
 * Projection work
 *
 * Revision 1.1  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 */

#include "AdanaxisStandard.h"

#include "API/mushMushGame.h"
#include "API/mushMushGL.h"

//:generate standard ostream xml1
class AdanaxisRender : public MushGameRender
{
public:
    AdanaxisRender();
    virtual ~AdanaxisRender() {}
    
    virtual void FrameRender(MushGameLogic& ioLogic, const MushGameCamera& inCamera);

protected:
    MushGLProjection m_projection;
    Mushware::tVal m_halfAngle; //:readwrite
    Mushware::tVal m_halfAngleAttractor; //:readwrite
    
private:
//%classPrototypes {
public:
    const Mushware::tVal& HalfAngle(void) const { return m_halfAngle; }
    void HalfAngleSet(const Mushware::tVal& inValue) { m_halfAngle=inValue; }
    const Mushware::tVal& HalfAngleAttractor(void) const { return m_halfAngleAttractor; }
    void HalfAngleAttractorSet(const Mushware::tVal& inValue) { m_halfAngleAttractor=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } GgpsTEU9hkWCMlscEoyb+w
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisRender& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } zxkPtj57KCCMub1Z+D17AQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
