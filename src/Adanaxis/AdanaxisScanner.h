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
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 193nrcElHZdqkj3k/yUpIg
/*
 * $Id: AdanaxisScanner.h,v 1.1 2006/07/25 13:30:57 southa Exp $
 * $Log: AdanaxisScanner.h,v $
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
        kObjectTypeKhazi
    } tObjectType;
    
    enum
    {
        kSymbolScanWhite = 0,
        kSymbolScanX = 8,
        kSymbolScanY = 9,
        kSymbolScanZ = 10,
        kSymbolScanW = 11,
        kSymbolCrosshairSpecial = 16,
        kSymbolCrosshairOnTarget = 17,
        kSymbolCrosshairIdle = 18,
        kSymbolCrosshairInBoundary = 19,
        
        kTargetStateInvalid = 0,
        kTargetStateIdle,
        kTargetStateInBoundary,
        kTargetStateOnTarget
    };
    
    
    AdanaxisScanner();
    void ScanBegin(void) { m_targetState = kTargetStateIdle; }
    void ScanObjectRender(AdanaxisLogic& ioLogic, MushRenderMesh *inpMeshRender,
                          const MushGameCamera& inCamera, const MushMeshPosticity& inPost,
                          const MushMesh4Mesh& inMesh, Mushware::U32 inObjType);
    
    void ScanSymbolRender(Mushware::t4Val& inPos, Mushware::t4Val inParam, Mushware::tVal inAlpha);
    void ScanCrosshairRender(AdanaxisLogic& ioLogic, MushRenderMesh *inpMeshRender,
                             const MushGameCamera& inCamera);
    
private:
    Mushware::t2Val m_symbolSize; //:readwrite
    MushGLFont::tDataRef m_symbolFontRef;
    Mushware::tVal m_sightAngle;
    Mushware::U32 m_targetState;
    
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

