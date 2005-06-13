//%includeGuardStart {
#ifndef ADANAXISCONFIG_H
#define ADANAXISCONFIG_H
//%includeGuardStart } U1cBAMbPpT8Nfh33tQ1jHA
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisConfig.h
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } BrE7yoZUpm837l9JJJwiIA
/*
 * $Id: AdanaxisConfig.h,v 1.5 2005/06/08 20:59:52 southa Exp $
 * $Log: AdanaxisConfig.h,v $
 */

#include "AdanaxisStandard.h"

//:generate standard ostream xml1
class AdanaxisConfig : public MushcoreVirtualObject
{
public:
    AdanaxisConfig();
    
private:
    Mushware::U32 m_version;
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
