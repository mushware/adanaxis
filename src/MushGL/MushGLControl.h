//%includeGuardStart {
#ifndef MUSHGLCONTROL_H
#define MUSHGLCONTROL_H
//%includeGuardStart } wWjFvaLXjiunga82vYgvqw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLControl.h
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
//%Header } UkMB818AksLnlpxGaMOcNg
/*
 * $Id: MushGLControl.h,v 1.1 2005/06/13 17:35:37 southa Exp $
 * $Log: MushGLControl.h,v $
 * Revision 1.1  2005/06/13 17:35:37  southa
 * Adanaxis creation
 *
 */

#include "MushGLStandard.h"

//:generate virtual standard ostream xml1
class MushGLControl : public MushcoreVirtualObject, public MushcoreSingleton<MushGLControl>
{
public:
    MushGLControl() {}
    ~MushGLControl() {}
    
private:
    Mushware::tLongVal m_timestamp;
    std::vector<Mushware::U8> m_keys;
    std::vector<Mushware::tVal> m_axes;
//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLControl& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 72642ArDgf4qeAWjHmfQCQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
