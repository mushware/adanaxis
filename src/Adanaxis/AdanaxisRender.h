//%includeGuardStart {
#ifndef ADANAXISRENDER_H
#define ADANAXISRENDER_H
//%includeGuardStart } dZcfmpPUzEwmX2Q78sGR/A
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisRender.h
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
//%Header } jpyq9WjuLQC6cyA1T6bbWw
/*
 * $Id: AdanaxisRender.h,v 1.7 2006/06/30 17:26:10 southa Exp $
 * $Log: AdanaxisRender.h,v $
 * Revision 1.7  2006/06/30 17:26:10  southa
 * Render prelude
 *
 * Revision 1.6  2006/06/01 15:38:48  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/08/02 11:11:47  southa
 * Adanaxis control demo work
 *
 * Revision 1.4  2005/07/05 16:35:53  southa
 * Adanaxis work
 *
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
    
    virtual void PreCacheRender(MushGameLogic& ioLogic, const MushGameCamera& inCamera);
    virtual void FrameRender(MushGameLogic& ioLogic, const MushGameCamera& inCamera);
    virtual void Overplot(MushGameLogic& ioLogic, const MushGameCamera& inCamera);
    virtual void RenderPreludeSet(Mushware::U32 inValue = 3) { m_renderPrelude = inValue; }
    
protected:
    MushGLProjection m_projection;
    Mushware::tVal m_halfAngle; //:readwrite
    Mushware::tVal m_halfAngleAttractor; //:readwrite
    bool m_scannerOn; //:readwrite
    Mushware::U32 m_renderPrelude;
    
private:
//%classPrototypes {
public:
    const Mushware::tVal& HalfAngle(void) const { return m_halfAngle; }
    void HalfAngleSet(const Mushware::tVal& inValue) { m_halfAngle=inValue; }
    const Mushware::tVal& HalfAngleAttractor(void) const { return m_halfAngleAttractor; }
    void HalfAngleAttractorSet(const Mushware::tVal& inValue) { m_halfAngleAttractor=inValue; }
    const bool& ScannerOn(void) const { return m_scannerOn; }
    void ScannerOnSet(const bool& inValue) { m_scannerOn=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } E+QOfl/VxCxg9fXFuIyMAQ
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
