//%includeGuardStart {
#ifndef ADANAXISEVENTS_H
#define ADANAXISEVENTS_H
//%includeGuardStart } PFClCvea6tI3loXKhvRBhA
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisEvents.h
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.3, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } lux+Ke8jIsvwTCElkqGblA
/*
 * $Id: AdanaxisEvents.h,v 1.3 2007/04/18 09:22:00 southa Exp $
 * $Log: AdanaxisEvents.h,v $
 * Revision 1.3  2007/04/18 09:22:00  southa
 * Header and level fixes
 *
 * Revision 1.2  2006/11/03 18:46:33  southa
 * Damage effectors
 *
 * Revision 1.1  2006/11/02 09:47:33  southa
 * Player weapon control
 *
 */

#include "AdanaxisStandard.h"

//:generate virtual standard ostream xml1
class AdanaxisEvents : public MushcoreVirtualObject, public MushcoreSingleton<AdanaxisEvents>
{
public:
    virtual ~AdanaxisEvents() {}
    
    MushRubyValue EventFireMake(const MushMeshPosticity& inPost);
    MushRubyValue EventKeyStateMake(void);
    void EventKeyStateAddState(MushRubyValue& ioEvent, Mushware::U32 inNum, bool inState);
    
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
operator<<(std::ostream& ioOut, const AdanaxisEvents& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 26CeuLmW+qc4ymzqMBFIPg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
