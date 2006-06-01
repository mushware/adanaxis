//%includeGuardStart {
#ifndef MUSHGAMECONFIGBASE_H
#define MUSHGAMECONFIGBASE_H
//%includeGuardStart } zQu2zIPg08TdUfi/So0AiQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameConfigBase.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } j+QdgpgaMWOYWMDzkr6iXg
/*
 * $Id: MushGameConfigBase.h,v 1.1 2005/06/14 20:39:41 southa Exp $
 * $Log: MushGameConfigBase.h,v $
 * Revision 1.1  2005/06/14 20:39:41  southa
 * Adanaxis work
 *
 */

#include "MushGameStandard.h"

//:generate virtual ostream xml1
class MushGameConfigBase : public MushcoreVirtualObject
{
public:
    MushGameConfigBase();
    virtual void ToDefaultSet(void);
    virtual void AutoInputPrologue(MushcoreXMLIStream& ioIn);
    virtual void AutoOutputPrologue(MushcoreXMLOStream& ioOut) const;
    
private:
    Mushware::U32 m_version; //:readwrite
    Mushware::U32 m_safeMode; //:readwrite
    
//%classPrototypes {
public:
    const Mushware::U32& Version(void) const { return m_version; }
    void VersionSet(const Mushware::U32& inValue) { m_version=inValue; }
    const Mushware::U32& SafeMode(void) const { return m_safeMode; }
    void SafeModeSet(const Mushware::U32& inValue) { m_safeMode=inValue; }
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } nrDh7o2kpymliVX8DHeBNg
};

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameConfigBase& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 3DZUQfm9aDXA3S2kw7plyA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
