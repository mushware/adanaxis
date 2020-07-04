//%includeGuardStart {
#ifndef ADANAXISSCANNER_H
#define ADANAXISSCANNER_H
//%includeGuardStart } TSQCmL59URqpbDVw9ne1Cg
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisScanner.h
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
//%Header } I3zFdN9r+HuiUZK4uqeDEQ
/*
 * $Id: AdanaxisScanner.h,v 1.11 2007/04/18 09:22:04 southa Exp $
 * $Log: AdanaxisScanner.h,v $
 * Revision 1.11  2007/04/18 09:22:04  southa
 * Header and level fixes
 *
 * Revision 1.10  2007/04/16 08:41:09  southa
 * Level and header mods
 *
 * Revision 1.9  2007/03/13 18:21:37  southa
 * Scanner jamming
 *
 * Revision 1.8  2007/03/13 12:22:51  southa
 * Scanner symbols
 *
 * Revision 1.7  2007/03/12 21:06:00  southa
 * Scanner symbols
 *
 * Revision 1.6  2006/11/12 20:09:55  southa
 * Missile guidance
 *
 * Revision 1.5  2006/10/20 15:38:52  southa
 * Item collection
 *
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
        kSymbolScanNone = 0,
        kSymbolScanWhite = 8,
        kSymbolScanRed = 9,
        kSymbolScanGreen = 10,
        kSymbolScanYellow = 11,
        kSymbolScanX = 16,
        kSymbolScanY = 17,
        kSymbolScanZ = 18,
        kSymbolScanW = 19,
        kSymbolCrosshairSpecial = 24,
        kSymbolCrosshairOnTarget = 25,
        kSymbolCrosshairIdle = 26,
        kSymbolCrosshairInBoundary = 27,
        
        kSymbolHitPointsBarBorder = 32,
        kSymbolHitPointsBarInterior = 33,
        
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
    std::string m_targetID; //:read
    
//%classPrototypes {
public:
    const Mushware::t2Val& SymbolSize(void) const { return m_symbolSize; }
    void SymbolSizeSet(const Mushware::t2Val& inValue) { m_symbolSize=inValue; }
    const std::string& TargetID(void) const { return m_targetID; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } Pqfki30KZ4zYaNr6Shu+LQ
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

