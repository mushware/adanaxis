//%includeGuardStart {
#ifndef ADANAXISLOGIC_H
#define ADANAXISLOGIC_H
//%includeGuardStart } tlupkMe2RfcPxVQYrM2UbQ
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisLogic.h
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
//%Header } v0NoK60n2sQZAwN5ucHNyw
/*
 * $Id$
 * $Log$
 */

#include "AdanaxisStandard.h"

#include "AdanaxisSaveData.h"
#include "AdanaxisVolatileData.h"

#include "API/mushMushGame.h"

//:xml1base MushGameLogic
//:generate virtual standard ostream xml1
class AdanaxisLogic : public MushGameLogic 
{
public:
    virtual AdanaxisSaveData& SaveData(void);
    virtual AdanaxisVolatileData& VolatileData(void);
    
    // virtual AdanaxisHostSaveData& HostSaveData(void) { return m_hostDataRef.Ref().SaveDataRef().WRef(); }
    // virtual AdanaxisHostVolatileData& HostVolatileData(void) { return m_hostDataRef.Ref().VolatileDataRef().WRef(); }
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

inline AdanaxisSaveData&
AdanaxisLogic::SaveData(void)
{
    AdanaxisSaveData *pSaveData = dynamic_cast<AdanaxisSaveData *>(&MushGameLogic::SaveData());
    if (pSaveData == NULL)
    {
        throw MushcoreLogicFail("AdanaxisSaveData of wrong type");
    }
    return *pSaveData;
}

inline AdanaxisVolatileData&
AdanaxisLogic::VolatileData(void)
{
    AdanaxisVolatileData *pVolData = dynamic_cast<AdanaxisVolatileData *>(&MushGameLogic::VolatileData());
    if (pVolData == NULL)
    {
        throw MushcoreLogicFail("AdanaxisVolatileData of wrong type");
    }
    return *pVolData;
}
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisLogic& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } QIRY4KmklBxic6KkTAE0QQ

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
