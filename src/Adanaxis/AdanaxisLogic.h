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
 * software licence version 1.1, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 3LuiErcM0vO3wOyNDCFVeQ
/*
 * $Id: AdanaxisLogic.h,v 1.26 2007/03/07 16:59:44 southa Exp $
 * $Log: AdanaxisLogic.h,v $
 * Revision 1.26  2007/03/07 16:59:44  southa
 * Khazi spawning and level ends
 *
 * Revision 1.25  2007/02/08 17:55:14  southa
 * Common routines in space generation
 *
 * Revision 1.24  2006/12/14 15:59:23  southa
 * Fire and cutscene fixes
 *
 * Revision 1.23  2006/11/21 10:08:24  southa
 * Initial cut scene handling
 *
 * Revision 1.22  2006/11/03 18:46:33  southa
 * Damage effectors
 *
 * Revision 1.21  2006/10/20 15:38:52  southa
 * Item collection
 *
 * Revision 1.20  2006/10/19 15:41:35  southa
 * Item handling
 *
 * Revision 1.19  2006/10/17 15:28:01  southa
 * Player collisions
 *
 * Revision 1.18  2006/10/16 22:00:21  southa
 * Tweaks
 *
 * Revision 1.17  2006/10/12 22:04:47  southa
 * Collision events
 *
 * Revision 1.16  2006/10/04 13:35:22  southa
 * Selective targetting
 *
 * Revision 1.15  2006/10/02 20:28:10  southa
 * Object lookup and target selection
 *
 * Revision 1.14  2006/10/02 17:25:04  southa
 * Object lookup and target selection
 *
 * Revision 1.13  2006/08/01 17:21:24  southa
 * River demo
 *
 * Revision 1.12  2006/07/27 13:51:34  southa
 * Menu and control fixes
 *
 * Revision 1.11  2006/07/20 12:22:21  southa
 * Precache display
 *
 * Revision 1.10  2006/07/19 14:34:50  southa
 * Flare effects
 *
 * Revision 1.9  2006/06/01 15:38:47  southa
 * DrawArray verification and fixes
 *
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
#include "AdanaxisPiecePlayer.h"
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
    
    virtual MushGamePiecePlayer *PlayerNew(const MushGameMessage *inpMessage) { return new AdanaxisPiecePlayer; }
    
    virtual void TargetPieceSearch(std::string& ioID,  Mushware::tVal& ioDistSquared, const Mushware::t4Val& inPos,
                                   const std::string& inObjType, const std::string& inExcludeID) const;
    virtual void ProjectilesMove(void);
    virtual void DecoMove(void);
    virtual void EffectorsMove(void);
    virtual void ItemsMove(void);
    virtual void KhaziMove(void);
    virtual void MoveSequence(void);
    virtual void CollideSequence(void);
    virtual void ReceiveSequence(void);
    virtual void PrecacheSequence(void);
    virtual void RenderSequence(void);
    virtual void CutSceneSequence(void);
    virtual void Tick100msSequence(void);
    virtual void ProjectilesKhaziFullCollide(void);
    virtual void KhaziKhaziFullCollide(void);
    virtual void ProjectilesPlayersFullCollide(void);
    virtual void KhaziPlayersFullCollide(void);
    virtual void ItemsPlayersFullCollide(void);
    virtual void ProjectilesItemsFullCollide(void);
    virtual void EffectorsFullCollide(void);    
    virtual void MenuModeEnter(void);
    
    virtual void CollisionConsume(MushGameLogic& ioLogic, const MushGameMessageCollision& inMessage);
    virtual void CollisionMessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);
    
    virtual AdanaxisSaveData& SaveData(void) const;
    virtual const AdanaxisSaveData& ConstSaveData(void) const;
    virtual AdanaxisVolatileData& VolatileData(void) const;
    virtual const AdanaxisVolatileData& ConstVolatileData(void) const;
    virtual Mushware::U32 PrecachePercentage(void) const { return m_preCacheResult; }
    
protected:
    virtual void CollisionHandle(MushGamePiece *iopPiece1, MushGamePiece *iopPiece2, const MushCollisionInfo& inCollInfo);
    
private:
    Mushware::tMsec m_startTime; //:readwrite
    Mushware::tMsec m_endTime; //:readwrite
    Mushware::tMsec m_recordTime; //:readwrite
    Mushware::U32 m_preCacheResult; //:read
    
//%classPrototypes {
public:
    const Mushware::tMsec& StartTime(void) const { return m_startTime; }
    void StartTimeSet(const Mushware::tMsec& inValue) { m_startTime=inValue; }
    const Mushware::tMsec& EndTime(void) const { return m_endTime; }
    void EndTimeSet(const Mushware::tMsec& inValue) { m_endTime=inValue; }
    const Mushware::tMsec& RecordTime(void) const { return m_recordTime; }
    void RecordTimeSet(const Mushware::tMsec& inValue) { m_recordTime=inValue; }
    const Mushware::U32& PreCacheResult(void) const { return m_preCacheResult; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } GMf0rLHTbqXRe5+4KYUE3g
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
