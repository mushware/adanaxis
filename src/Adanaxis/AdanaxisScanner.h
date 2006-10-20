//%includeGuardStart {
#ifndef ADANAXISSCANNER_H
#define ADANAXISSCANNER_H
//%includeGuardStart } TSQCmL59URqpbDVw9ne1Cg
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisScanner.h
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
//%Header } XLKRQITGeEosZnXBO0QSEw
/*
 * $Id: AdanaxisScanner.h,v 1.4 2006/10/09 16:00:16 southa Exp $
 * $Log: AdanaxisScanner.h,v $
 * Revision 1.4  2006/10/09 16:00:16  southa
 * Intern generation
 *
 * Revision 1.3  2006/08/01 17:21:29  southa
 * River demo
 *
 * Revision 1.2  2006/07/25 20:31:03  southa
 * Scanner work
 *
 * Revision 1.1  2006/07/25 13:30:57  southa
 * Initial scanner work
 *
 */

#include "AdanaxisStandard.h"

#include "AdanaxisLogic.h"

#include "API/mushMushGame.h"
#include "API/mushMushGL.h"

class MushRenderMesh;

//:generate standard ostream xml1
class AdanaxisScanner : public MushcoreVirtualObject
{
public:
    enum
    {
        kObjectTypeInvalid,
        kObjectTypeNone,
        kObjectTypeKhazi,
        kObjectTypeItem
    } tObjectType;
    
    enum
    {
        kSymbolScanWhite = 0,
        kSymbolScanRed = 1,
        kSymbolScanGreen = 2,
        kSymbolScanX = 8,
        kSymbolScanY = 9,
        kSymbolScanZ = 10,
        kSymbolScanW = 11,
        kSymbolCrosshairSpecial = 16,
        kSymbolCrosshairOnTarget = 17,
        kSymbolCrosshairIdle = 18,
        kSymbolCrosshairInBoundary = 19,
        
        kSymbolHitPointsBarBorder = 24,
        kSymbolHitPointsBarInterior = 25,
        
        kTargetStateInvalid = 0,
        kTargetStateIdle,
        kTargetStateInBoundary,
        kTargetStateOnTarget
    };
    
    
    AdanaxisScanner();
    void ScanBegin(void) { m_targetState = kTargetStateIdle; }
    void ScanObjectRender(AdanaxisLogic& ioLogic, MushRenderMesh *inpMeshRender,
                          const MushGameCamera& inCamera, const MushGamePiece& inPiece,
                          Mushware::U32 inObjType);
    
    void ScanSymbolRender(Mushware::t4Val& inPos, Mushware::t4Val inParam,
                          Mushware::tVal inAlpha, Mushware::U32 inSymbol);
    void ScanCrosshairRender(AdanaxisLogic& ioLogic, MushRenderMesh *inpMeshRender,
                             const MushGameCamera& inCamera);
    
private:
    Mushware::t2Val m_symbolSize; //:readwrite
    MushGLFont::tDataRef m_symbolFontRef;
    Mushware::tVal m_sightAngle;
    Mushware::U32 m_targetState;
    Mushware::tVal m_targetHitPointRatio;
    
//%classPrototypes {
public:
    const Mushware::t2Val& SymbolSize(void) const { return m_symbolSize; }
    void SymbolSizeSet(const Mushware::t2Val& inValue) { m_symbolSize=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } +yJMaswq2Z2VTrPV3IxJWg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisScanner& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } l46wPyowyPeR7MSifqYPTw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw

