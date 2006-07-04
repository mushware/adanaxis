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
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } lXOhNHrEv7a8Ndh1gy3P5A
/*
 * $Id: AdanaxisVolatileData.h,v 1.5 2006/07/02 21:08:54 southa Exp $
 * $Log: AdanaxisVolatileData.h,v $
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

#include "API/mushGame.h"
#include "API/mushMushGame.h"

//:xml1base MushGameVolatileData
//:generate virtual nocopy standard ostream xml1
class AdanaxisVolatileData : public MushGameVolatileData
{
public:
    typedef AdanaxisPieceDeco tDeco;
    typedef MushcoreMaptor<tDeco> tDecoList;
    AdanaxisVolatileData();
    virtual ~AdanaxisVolatileData() {}
    
private:
    tDecoList m_decoList; //:read :wref
    Mushware::tMsec m_modeKeypressMsec; //:readwrite
    Mushware::tMsec m_newMode; //:readwrite
    std::auto_ptr<MushRenderMesh> m_aRenderMesh; //:read :wref
	Mushware::tRubyValue m_rubySpace; //:readwrite
    
//%classPrototypes {
public:
    const tDecoList& DecoList(void) const { return m_decoList; }
    // Writable reference for m_decoList
    tDecoList& DecoListWRef(void) { return m_decoList; }
    const Mushware::tMsec& ModeKeypressMsec(void) const { return m_modeKeypressMsec; }
    void ModeKeypressMsecSet(const Mushware::tMsec& inValue) { m_modeKeypressMsec=inValue; }
    const Mushware::tMsec& NewMode(void) const { return m_newMode; }
    void NewModeSet(const Mushware::tMsec& inValue) { m_newMode=inValue; }
    const std::auto_ptr<MushRenderMesh>& ARenderMesh(void) const { return m_aRenderMesh; }
    // Writable reference for m_aRenderMesh
    std::auto_ptr<MushRenderMesh>& ARenderMeshWRef(void) { return m_aRenderMesh; }
    const Mushware::tRubyValue& RubySpace(void) const { return m_rubySpace; }
    void RubySpaceSet(const Mushware::tRubyValue& inValue) { m_rubySpace=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } uqxUYZcyTlp/oVwxUO86Ug
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
