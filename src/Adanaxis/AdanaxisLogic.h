//%includeGuardStart {
#ifndef ADANAXISLOGIC_H
#define ADANAXISLOGIC_H
//%includeGuardStart } tlupkMe2RfcPxVQYrM2UbQ
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisLogic.h
 *
 * Copyright: Andy Southgate 2005-2006
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
//%Header } nTy3CMXyGBhzHaXXoJENIg
/*
 * $Id: AdanaxisLogic.h,v 1.8 2005/08/02 14:37:44 southa Exp $
 * $Log: AdanaxisLogic.h,v $
 * Revision 1.8  2005/08/02 14:37:44  southa
 * Adanaxis control demo work
 *
 * Revision 1.7  2005/08/02 11:11:47  southa
 * Adanaxis control demo work
 *
 * Revision 1.6  2005/08/01 13:09:57  southa
 * Collision messaging
 *
 * Revision 1.5  2005/07/29 08:27:46  southa
 * Collision work
 *
 * Revision 1.4  2005/07/12 12:18:17  southa
 * Projectile work
 *
 * Revision 1.3  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/07/01 14:58:59  southa
 * Mushcore auto_ptr and binary string fixes
 *
 * Revision 1.1  2005/06/30 16:29:24  southa
 * Adanaxis work
 *
 */

#include "AdanaxisStandard.h"

#include "AdanaxisSaveData.h"
#include "AdanaxisPlayer.h"
#include "AdanaxisVolatileData.h"

#include "API/mushMushGame.h"
#include "API/mushMushCollision.h"

//:xml1base MushGameLogic
//:generate virtual standard ostream xml1
class AdanaxisLogic : public MushGameLogic 
{
public:
    AdanaxisLogic();
    virtual MushGamePiece& PieceLookup(const std::string& inName) const;
    virtual void InitialDataCreate(void);
    
    virtual MushGamePlayer *PlayerNew(const MushGameMessage *inpMessage) { return new AdanaxisPlayer; }
    
    virtual void ProjectilesMove(void);
    virtual void KhaziMove(void);
    virtual void MoveSequence(void);
    virtual void CollideSequence(void);
    virtual void RenderSequence(void);
    virtual void ProjectilesFullCollide(void);
    
    virtual void CollisionFatalConsume(MushGameLogic& ioLogic, const MushGameMessageCollisionFatal& inMessage);
    virtual void CollisionMessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);
    
    virtual AdanaxisSaveData& SaveData(void) const;
    virtual const AdanaxisSaveData& ConstSaveData(void) const;
    virtual AdanaxisVolatileData& VolatileData(void) const;
    virtual const AdanaxisVolatileData& ConstVolatileData(void) const;
    
    // virtual AdanaxisHostSaveData& HostSaveData(void) { return m_hostDataRef.Ref().SaveDataRef().WRef(); }
    // virtual AdanaxisHostVolatileData& HostVolatileData(void) { return m_hostDataRef.Ref().VolatileDataRef().WRef(); }
    
protected:
    void CollisionHandle(AdanaxisSaveData::tProjectile& ioProj,
                         AdanaxisSaveData::tKhazi& ioKhazi,
                         const MushCollisionInfo& inCollInfo);
    
private:
    Mushware::U32 m_khaziCount; //:readwrite
    Mushware::tMsec m_startTime; //:readwrite
    Mushware::tMsec m_endTime; //:readwrite
    Mushware::tMsec m_recordTime; //:readwrite
    
//%classPrototypes {
public:
    const Mushware::U32& KhaziCount(void) const { return m_khaziCount; }
    void KhaziCountSet(const Mushware::U32& inValue) { m_khaziCount=inValue; }
    const Mushware::tMsec& StartTime(void) const { return m_startTime; }
    void StartTimeSet(const Mushware::tMsec& inValue) { m_startTime=inValue; }
    const Mushware::tMsec& EndTime(void) const { return m_endTime; }
    void EndTimeSet(const Mushware::tMsec& inValue) { m_endTime=inValue; }
    const Mushware::tMsec& RecordTime(void) const { return m_recordTime; }
    void RecordTimeSet(const Mushware::tMsec& inValue) { m_recordTime=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } dl8cBZqIOtan46mtOs/q1w
};

inline AdanaxisSaveData&
AdanaxisLogic::SaveData(void) const
{
    AdanaxisSaveData *pSaveData = dynamic_cast<AdanaxisSaveData *>(&MushGameLogic::SaveData());
    if (pSaveData == NULL)
    {
        throw MushcoreLogicFail("AdanaxisSaveData of wrong type");
    }
    return *pSaveData;
}

inline const AdanaxisSaveData&
AdanaxisLogic::ConstSaveData(void) const
{
    const AdanaxisSaveData *pSaveData = dynamic_cast<const AdanaxisSaveData *>(&MushGameLogic::ConstSaveData());
    if (pSaveData == NULL)
    {
        throw MushcoreLogicFail("AdanaxisSaveData of wrong type");
    }
    return *pSaveData;
}

inline AdanaxisVolatileData&
AdanaxisLogic::VolatileData(void) const
{
    AdanaxisVolatileData *pVolData = dynamic_cast<AdanaxisVolatileData *>(&MushGameLogic::VolatileData());
    if (pVolData == NULL)
    {
        throw MushcoreLogicFail("AdanaxisVolatileData of wrong type");
    }
    return *pVolData;
}

inline const AdanaxisVolatileData&
AdanaxisLogic::ConstVolatileData(void) const
{
    const AdanaxisVolatileData *pVolData = dynamic_cast<const AdanaxisVolatileData *>(&MushGameLogic::ConstVolatileData());
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
