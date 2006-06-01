//%includeGuardStart {
#ifndef MUSHGAMEANIMPOSTMANIP_H
#define MUSHGAMEANIMPOSTMANIP_H
//%includeGuardStart } kKBUf99bhDV6sUzDfKprzw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameAnimPostManip.h
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
//%Header } zn08WOenIGzlbo2RAXrZvg
/*
 * $Id: MushGameAnimPostManip.h,v 1.2 2005/07/05 16:35:53 southa Exp $
 * $Log: MushGameAnimPostManip.h,v $
 * Revision 1.2  2005/07/05 16:35:53  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 */

#include "MushGameStandard.h"

//:generate standard ostream xml1
class MushGameAnimPostManip : public MushcoreVirtualObject
{
public:
    MushGameAnimPostManip();
    virtual ~MushGameAnimPostManip() {}
    void PostAdjust(MushMeshPosticity& ioPost);

private:
    Mushware::tVal m_posSpeed; //:readwrite
    Mushware::tVal m_angSpeed; //:readwrite
    
//%classPrototypes {
public:
    const Mushware::tVal& PosSpeed(void) const { return m_posSpeed; }
    void PosSpeedSet(const Mushware::tVal& inValue) { m_posSpeed=inValue; }
    const Mushware::tVal& AngSpeed(void) const { return m_angSpeed; }
    void AngSpeedSet(const Mushware::tVal& inValue) { m_angSpeed=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } aU1OUTIp4fMMoMAB0QR5OA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameAnimPostManip& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } vjiZSxLd/otw4RLWhr3hKA

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
