//%includeGuardStart {
#ifndef ADANAXISRENDER_H
#define ADANAXISRENDER_H
//%includeGuardStart } dZcfmpPUzEwmX2Q78sGR/A
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisRender.h
 *
 * Copyright: Andy Southgate 2005-2007
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
//%Header } PzP9jWQw0nNNZUi3UI/r5A
/*
 * $Id: AdanaxisRender.h,v 1.13 2007/02/08 17:55:14 southa Exp $
 * $Log: AdanaxisRender.h,v $
 * Revision 1.13  2007/02/08 17:55:14  southa
 * Common routines in space generation
 *
 * Revision 1.12  2006/08/01 17:21:27  southa
 * River demo
 *
 * Revision 1.11  2006/07/28 16:52:19  southa
 * Options work
 *
 * Revision 1.10  2006/07/25 13:30:57  southa
 * Initial scanner work
 *
 * Revision 1.9  2006/07/24 18:46:48  southa
 * Depth sorting
 *
 * Revision 1.8  2006/07/20 12:22:21  southa
 * Precache display
 *
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

#include "AdanaxisScanner.h"

#include "API/mushMushGame.h"
#include "API/mushMushGL.h"

class MushRenderMesh;

//:generate standard ostream xml1
class AdanaxisRender : public MushGameRender
{
public:
    AdanaxisRender();
    virtual ~AdanaxisRender() {}
    
    virtual void PrecacheRender(MushGameLogic& ioLogic, const MushGameCamera& inCamera);
    virtual void FrameRender(MushGameLogic& ioLogic, const MushGameCamera& inCamera);
    virtual void ScanRender(AdanaxisLogic& ioLogic, MushRenderMesh *inpRenderMesh, const MushGameCamera& inCamera);
    virtual void DamagePlot(MushGameLogic& ioLogic, const MushGameCamera& inCamera);
    virtual void OverPlot(MushGameLogic& ioLogic, const MushGameCamera& inCamera);
    virtual void RenderPreludeSet(Mushware::U32 inValue = 3) { m_renderPrelude = inValue; }
    virtual void SortAndDespatch(MushGameLogic& ioLogic, std::vector<MushGLJobRender *> inJobs);
    
private:
    typedef Mushware::t2GLVal tDamageVertex;
    typedef std::vector<tDamageVertex> tDamageVertices;
    typedef std::vector<tDamageVertices> tDamageVerticesList;
    typedef Mushware::t4GLVal tDamageColour;
    typedef std::vector<tDamageColour> tDamageColours;
    typedef std::vector<tDamageColours> tDamageColoursList;
    
    MushGLProjection m_projection;
    Mushware::tVal m_halfAngle; //:readwrite
    Mushware::tVal m_halfAngleAttractor; //:readwrite
    Mushware::U32 m_renderPrelude;
    std::vector<MushGLJobRender *> m_renderList;
    AdanaxisScanner m_scanner;
    tDamageVerticesList m_damageVertices;
    tDamageColoursList m_damageColours;

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
