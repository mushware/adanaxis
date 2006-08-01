//%includeGuardStart {
#ifndef ADANAXISVOLATILEDATA_H
#define ADANAXISVOLATILEDATA_H
//%includeGuardStart } WOSmULytubQRWj1H0kbf4g
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisVolatileData.h
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
//%Header } /G5prPJmGC4DIKgcQWm0Bg
/*
 * $Id: AdanaxisVolatileData.h,v 1.10 2006/07/28 16:52:20 southa Exp $
 * $Log: AdanaxisVolatileData.h,v $
 * Revision 1.10  2006/07/28 16:52:20  southa
 * Options work
 *
 * Revision 1.9  2006/07/28 11:14:28  southa
 * Records for multiple spaces
 *
 * Revision 1.8  2006/07/26 16:37:21  southa
 * Options menu
 *
 * Revision 1.7  2006/07/19 10:22:16  southa
 * World objects
 *
 * Revision 1.6  2006/07/04 16:55:26  southa
 * Ruby key handling
 *
 * Revision 1.5  2006/07/02 21:08:54  southa
 * Ruby menu work
 *
 * Revision 1.4  2006/06/21 16:52:30  southa
 * Deco objects
 *
 * Revision 1.3  2006/06/01 15:38:49  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/01 16:42:54  southa
 * Render work
 *
 * Revision 1.1  2005/06/30 14:26:35  southa
 * Adanaxis work
 *
 */

#include "AdanaxisStandard.h"
#include "AdanaxisPieceDeco.h"
#include "AdanaxisPieceWorld.h"

#include "API/mushGame.h"
#include "API/mushMushGame.h"

//:xml1base MushGameVolatileData
//:generate virtual nocopy standard ostream xml1
class AdanaxisVolatileData : public MushGameVolatileData
{
public:
    typedef AdanaxisPieceDeco tDeco;
    typedef MushcoreMaptor<tDeco> tDecoList;
    typedef AdanaxisPieceWorld tWorld;
    typedef MushcoreMaptor<tWorld> tWorldList;
    AdanaxisVolatileData();
    virtual ~AdanaxisVolatileData() {}
    
private:
    tDecoList m_decoList; //:read :wref
    tWorldList m_worldList; //:read :wref
    std::auto_ptr<MushRenderMesh> m_aRenderMesh; //:read :wref
	MushRubyValue m_rubySpace; //:readwrite
    Mushware::tVal m_brightness; //:readwrite
    bool m_scannerOn; //:readwrite
    
//%classPrototypes {
public:
    const tDecoList& DecoList(void) const { return m_decoList; }
    // Writable reference for m_decoList
    tDecoList& DecoListWRef(void) { return m_decoList; }
    const tWorldList& WorldList(void) const { return m_worldList; }
    // Writable reference for m_worldList
    tWorldList& WorldListWRef(void) { return m_worldList; }
    const std::auto_ptr<MushRenderMesh>& ARenderMesh(void) const { return m_aRenderMesh; }
    // Writable reference for m_aRenderMesh
    std::auto_ptr<MushRenderMesh>& ARenderMeshWRef(void) { return m_aRenderMesh; }
    const MushRubyValue& RubySpace(void) const { return m_rubySpace; }
    void RubySpaceSet(const MushRubyValue& inValue) { m_rubySpace=inValue; }
    const Mushware::tVal& Brightness(void) const { return m_brightness; }
    void BrightnessSet(const Mushware::tVal& inValue) { m_brightness=inValue; }
    const bool& ScannerOn(void) const { return m_scannerOn; }
    void ScannerOnSet(const bool& inValue) { m_scannerOn=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } R56rnaV/PEXuBbYuqyTioA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisVolatileData& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } f8H5o1BtmcymrIW1lWAphw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
