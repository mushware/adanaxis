//%includeGuardStart {
#ifndef MUSHPIESIGNAL_H
#define MUSHPIESIGNAL_H
//%includeGuardStart } 4Ppb7qlwhe1x6KEcwB9Qug
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieSignal.h
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
//%Header } pJ3Ndkz2M6+Snlv4VP0kBw
/*
 * $Id: MushPieSignal.h,v 1.3 2005/05/19 13:02:13 southa Exp $
 * $Log: MushPieSignal.h,v $
 * Revision 1.3  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.2  2005/02/10 12:34:16  southa
 * Template fixes
 *
 * Revision 1.1  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
 */

#include "MushPieStandard.h"

//:generate virtual standard ostream xml1
class MushPieSignal : public MushcoreVirtualObject
{
public:
    MushPieSignal() {}
    virtual ~MushPieSignal() {}
    
private:
    
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
operator<<(std::ostream& ioOut, const MushPieSignal& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } U1OYYIdjfEmHGMjXtntbzw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
