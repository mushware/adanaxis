//%includeGuardStart {
#ifndef ADANAXISCLIENT_H
#define ADANAXISCLIENT_H
//%includeGuardStart } 2sNIivWtxKZWCIEsJT7nEg
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisClient.h
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.4, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 8sclr6+jJgHexwz4+5WJhA
/*
 * $Id: AdanaxisClient.h,v 1.5 2007/04/18 09:21:59 southa Exp $
 * $Log: AdanaxisClient.h,v $
 * Revision 1.5  2007/04/18 09:21:59  southa
 * Header and level fixes
 *
 * Revision 1.4  2006/08/01 17:21:22  southa
 * River demo
 *
 * Revision 1.3  2006/06/01 15:38:46  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/06/20 14:30:33  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 10:49:57  southa
 * Client/server work
 *
 */

#include "AdanaxisStandard.h"

#include "API/mushMushGame.h"

//:xml1base MushGameClient
//:generate virtual standard ostream xml1
class AdanaxisClient : public MushGameClient
{
public:
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
operator<<(std::ostream& ioOut, const AdanaxisClient& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 88Tgs2k3k5hwpJuZ9Yc6rQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
