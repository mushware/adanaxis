//%includeGuardStart {
#ifndef ADANAXISSERVER_H
#define ADANAXISSERVER_H
//%includeGuardStart } idov99+c0mfn4CXxMSd9SQ
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisServer.h
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
//%Header } EQQqQtu6+TdDXiuNGH+BrQ

#include "AdanaxisStandard.h"

#include "AdanaxisSaveData.h"

#include "API/mushMushGame.h"

//:xml1base MushGameServer
//:generate virtual standard ostream xml1
class AdanaxisServer : public MushGameServer
{
public:
    virtual ~AdanaxisServer() {}
    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);

protected:
    virtual AdanaxisSaveData& SaveData() { return dynamic_cast<AdanaxisSaveData&>(MushGameServer::SaveData()); }

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
operator<<(std::ostream& ioOut, const AdanaxisServer& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } /afDGiM/9BzxU+Z77xYWvw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
