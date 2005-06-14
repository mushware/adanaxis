//%includeGuardStart {
#ifndef ADANAXISCONFIG_H
#define ADANAXISCONFIG_H
//%includeGuardStart } U1cBAMbPpT8Nfh33tQ1jHA
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisConfig.h
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
//%Header } 76Z23tD76SliFedbLacn1Q
/*
 * $Id: AdanaxisConfig.h,v 1.2 2005/06/14 13:25:33 southa Exp $
 * $Log: AdanaxisConfig.h,v $
 * Revision 1.2  2005/06/14 13:25:33  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/13 17:34:54  southa
 * Adanaxis creation
 *
 */

#include "AdanaxisStandard.h"
#include "API/mushMushGame.h"

//:xml1base MushGameConfigBase
//:generate standard ostream xml1
class AdanaxisConfig : public MushGameConfigBase
{
public:
    AdanaxisConfig();
    
    virtual void ToDefaultSet(void);
    virtual void AutoInputPrologue(MushcoreXMLIStream& ioIn);
    virtual void AutoOutputPrologue(MushcoreXMLOStream& ioOut) const;
    
private:
    enum
    {
        kVersion = 200506014,
    };
    
    Mushware::U32 m_displayMode; //:readwrite
    
//%classPrototypes {
public:
    const Mushware::U32& DisplayMode(void) const { return m_displayMode; }
    void DisplayModeSet(const Mushware::U32& inValue) { m_displayMode=inValue; }
    const char *AutoNameGet(void) const;
    MushcoreVirtualObject *AutoClone(void) const;
    MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    void AutoPrint(std::ostream& ioOut) const;
    bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1XpbtZygGPL5/RDE+coVug
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisConfig& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } fTUu9zxKe0/BLgROv3OE8g

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
