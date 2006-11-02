//%includeGuardStart {
#ifndef ADANAXISEVENTS_H
#define ADANAXISEVENTS_H
//%includeGuardStart } PFClCvea6tI3loXKhvRBhA
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisEvents.h
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
//%Header } YcOjz32Z5hdWMepzrGLbUQ
/*
 * $Id$
 * $Log$
 */

#include "MushGameStandard.h"

//:generate virtual standard ostream xml1
class AdanaxisEvents : public MushcoreVirtualObject, public MushcoreSingleton<AdanaxisEvents>
{
public:
    virtual ~AdanaxisEvents() {}
    
    MushRubyValue EventFireMake(const MushMeshPosticity& inPost);
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
