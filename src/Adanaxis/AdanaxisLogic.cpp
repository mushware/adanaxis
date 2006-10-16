//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisLogic.cpp
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
//%Header } Mac7dWHONvkZIg39sQnwww
/*
 * $Id: AdanaxisLogic.cpp,v 1.25 2006/10/14 16:59:44 southa Exp $
 * $Log: AdanaxisLogic.cpp,v $
 * Revision 1.25  2006/10/14 16:59:44  southa
 * Ruby Deco objects
 *
 * Revision 1.24  2006/10/12 22:04:46  southa
 * Collision events
 *
 * Revision 1.23  2006/10/09 16:00:16  southa
 * Intern generation
 *
 * Revision 1.22  2006/10/08 11:31:32  southa
 * Hit points
 *
 * Revision 1.21  2006/10/04 13:35:22  southa
 * Selective targetting
 *
 * Revision 1.20  2006/10/02 20:28:10  southa
 * Object lookup and target selection
 *
 * Revision 1.19  2006/08/25 01:44:56  southa
 * Khazi fire
 *
 * Revision 1.18  2006/08/01 17:21:24  southa
 * River demo
 *
 * Revision 1.17  2006/07/31 11:01:36  southa
 * Music and dialogues
 *
 * Revision 1.16  2006/07/28 11:14:27  southa
 * Records for multiple spaces
 *
 * Revision 1.15  2006/07/27 13:51:33  southa
 * Menu and control fixes
 *
 * Revision 1.14  2006/07/20 12:22:20  southa
 * Precache display
 *
 * Revision 1.13  2006/07/19 14:34:50  southa
 * Flare effects
 *
 * Revision 1.12  2006/06/01 15:38:47  southa
 * DrawArray verification and fixes
 *
 * Revision 1.11  2005/08/02 14:37:44  southa
 * Adanaxis control demo work
 *
 * Revision 1.10  2005/08/02 11:11:47  southa
 * Adanaxis control demo work
 *
 * Revision 1.9  2005/08/01 13:09:57  southa
 * Collision messaging
 *
 * Revision 1.8  2005/07/30 19:06:14  southa
 * Collision checking
 *
 * Revision 1.7  2005/07/29 14:59:49  southa
 * Maptor access
 *
 * Revision 1.6  2005/07/29 08:27:46  southa
 * Collision work
 *
 * Revision 1.5  2005/07/12 12:18:17  southa
 * Projectile work
 *
 * Revision 1.4  2005/07/02 00:42:36  southa
 * Conditioning tweaks
 *
 * Revision 1.3  2005/07/01 16:42:54  southa
 * Render work
 *
 * Revision 1.2  2005/07/01 14:58:59  southa
 * Mushcore auto_ptr and binary string fixes
 *
 * Revision 1.1  2005/06/30 16:29:24  southa
 * Adanaxis work
 *
 */

#include "AdanaxisLogic.h"

#include "AdanaxisAppHandler.h"
#include "AdanaxisData.h"
#include "AdanaxisIntern.h"
#include "AdanaxisRender.h"
#include "AdanaxisUtil.h"

using namespace Mushware;
using namespace std;

AdanaxisLogic::AdanaxisLogic() :
    MushGameLogic(),
    m_khaziCount(1),
    m_preCacheResult(0)
{
}

void
AdanaxisLogic::TargetPieceSearch(std::string& ioID,
                                 Mushware::tVal& ioDistSquared,
                                 const Mushware::t4Val& inPos,
                                 const std::string& inObjType,
                                 const std::string& inExcludeID) const
{
    if (inObjType.size() < 1)
    {
        throw MushcoreDataFail("Object type of zero length");
    }
    switch (inObjType[0])
    {
        case AdanaxisData::kCharKhazi:
        {
            typedef AdanaxisSaveData::tKhaziList::const_iterator tIterator;
            const AdanaxisSaveData::tKhaziList& pieceData = SaveData().KhaziList();
            for (tIterator p = pieceData.begin(); p != pieceData.end(); ++p)
            {
                // For each Khazi...
                t4Val vecToObj = inPos - p->Post().Pos();
                tVal distToObjSquared = vecToObj.MagnitudeSquared();
                // If we have no current candidate, or this object is nearer than the current candidate...
                if (ioID == "" || distToObjSquared < ioDistSquared)
                {
                    std::string newID = p->Id();
                    // If it's not the excluded ID (which prevents us targeting ourselves)...
                    if (newID != inExcludeID)
                    {
                        // If the first characters of the ID match the requested type...
                        if (newID.substr(0, inObjType.length()) == inObjType)
                        {
                            // Choose this object as the new current candidate
                            ioDistSquared = distToObjSquared;
                            ioID = newID;
                        }
                    }
                }
            }
        }
        break;
            
        default:
            MushGameLogic::TargetPieceSearch(ioID, ioDistSquared, inPos, inObjType, inExcludeID);
            break;
    }
}

void
AdanaxisLogic::InitialDataCreate(void)
{
    VolatileData().ARenderMeshWRef().reset(new MushRenderMesh);
}

void
AdanaxisLogic::ProjectilesMove(void)
{
    typedef AdanaxisSaveData::tProjectileList tProjectileList;
    
    tProjectileList::iterator projectileEndIter = SaveData().ProjectileListWRef().end();
    for (tProjectileList::iterator p = SaveData().ProjectileListWRef().begin(); p != projectileEndIter;)
    {
        p->Move(*this, 1);
        
        if (p->ExpireFlag())
        {
            SaveData().ProjectileListWRef().Delete(p++);
        }
        else
        {
            ++p;   
        }
    }
}

void
AdanaxisLogic::DecoMove(void)
{
    typedef AdanaxisVolatileData::tDecoList tDecoList;
    
    tDecoList::iterator objEndIter = VolatileData().DecoListWRef().end();
    for (tDecoList::iterator p = VolatileData().DecoListWRef().begin(); p != objEndIter;)
    {
        p->Move(*this, 1);
        
        if (p->ExpireFlag())
        {
            VolatileData().DecoListWRef().Delete(p++);
        }
        else
        {
            ++p;   
        }
    }
}

void
AdanaxisLogic::KhaziMove(void)
{
    typedef AdanaxisSaveData::tKhaziList tKhaziList;
    
    tKhaziList::iterator khaziEndIter = SaveData().KhaziListWRef().end();
    for (tKhaziList::iterator p = SaveData().KhaziListWRef().begin(); p != khaziEndIter;)
    {
        p->Move(*this, 1);
        
        if (p->ExpireFlag())
        {
            SaveData().KhaziListWRef().Delete(p++);
        }
        else
        {
            ++p;   
        }
    }
}

void
AdanaxisLogic::CollisionHandle(MushGamePiece *iopPiece1, MushGamePiece *iopPiece2, const MushCollisionInfo& inCollInfo)
{
    MUSHCOREASSERT(inCollInfo.ObjectNamesValid());

    MushGameMessageCollision collMesg("c:");
    collMesg.ObjectName1Set(inCollInfo.ObjectName1());
    collMesg.ObjectName2Set(inCollInfo.ObjectName2());
    collMesg.Piece1Set(iopPiece1);
    collMesg.Piece2Set(iopPiece2);
    collMesg.PiecesValidSet(true);
    if (inCollInfo.ChunkNumsValid())
    {
        collMesg.ChunkNum1Set(inCollInfo.ChunkNum1());
        collMesg.ChunkNum2Set(inCollInfo.ChunkNum2());
        collMesg.ChunkNumsValidSet(true);
    }
    else
    {
        collMesg.ChunkNumsValidSet(false);
    }
    
    MushRubyValue collObj(collMesg.RubyObjectMake());
    
    RubyLogic().Call(AdanaxisIntern::Sgl().mCollisionEventConsume(), collObj);
    
    // CopyAndBroadcast(collMesg);
}

void
AdanaxisLogic::ProjectilesKhaziFullCollide(void)
{
    typedef AdanaxisSaveData::tProjectileList tList1;
    typedef AdanaxisSaveData::tKhaziList tList2;
    
    const tList1& list1Ref = SaveData().ProjectileList();
    const tList2& list2Ref = SaveData().KhaziList();
    
    tList1::const_iterator list1EndIter = list1Ref.end();
    tList2::const_iterator list2EndIter = list2Ref.end();
    for (tList1::const_iterator p = list1Ref.begin(); p != list1EndIter; ++p)
    {
        std::string projOwner = p->Owner();
        if (!p->ExpireFlag())
        {
            for (tList2::const_iterator q = list2Ref.begin(); q != list2EndIter; ++q)
            {
                // if this object hasn't expired and doesn't own the projectile...
                if (!q->ExpireFlag() && projOwner != q->Id())
                {
                    MushCollisionInfo collInfo;
                    MushCollisionResolver::Sgl().Resolve(collInfo, *p, *q);
                    if (collInfo.SeparatingDistance() <= 0)
                    {
                        collInfo.ObjectName1Set(p->Id());
                        collInfo.ObjectName2Set(q->Id());
                        collInfo.ObjectNamesValidSet(true);
                        
                        CollisionHandle(&*p, &*q, collInfo);
                    }
                }
            }
        }
    }
}

void
AdanaxisLogic::KhaziKhaziFullCollide(void)
{
    typedef AdanaxisSaveData::tKhaziList tList1;
    
    const tList1& list1Ref = SaveData().KhaziList();
    
    tList1::const_iterator list1EndIter = list1Ref.end();

    for (tList1::const_iterator p = list1Ref.begin(); p != list1EndIter; ++p)
    {
        if (!p->ExpireFlag())
        {
            for (tList1::const_iterator q = p; ++q != list1EndIter; )
            {
                if (!q->ExpireFlag())
                {
                    MushCollisionInfo collInfo;
                    MushCollisionResolver::Sgl().Resolve(collInfo, *p, *q);
                    if (collInfo.SeparatingDistance() <= 0)
                    {
                        collInfo.ObjectName1Set(p->Id());
                        collInfo.ObjectName2Set(q->Id());
                        collInfo.ObjectNamesValidSet(true);
                        
                        CollisionHandle(&*p, &*q, collInfo);
                    }
                }
            }
        }
    }
}

void
AdanaxisLogic::MoveSequence(void)
{
    MushGameLogic::MoveSequence();
    KhaziMove();
    ProjectilesMove();
    DecoMove();
}

void
AdanaxisLogic::CollideSequence(void)
{
    MushCollisionResolver::Sgl().FrameMsecSet(VolatileData().FrameMsec());
    KhaziKhaziFullCollide();
    ProjectilesKhaziFullCollide();
}

void
AdanaxisLogic::PreCacheSequence(void)
{
    m_preCacheResult = MushRubyValue(MushRubyExec::Sgl().Call(VolatileData().RubySpace(), MushRubyIntern::mPreCache())).U32();
    
    if (m_preCacheResult >= 100)
    {
        MushRubyExec::Sgl().Call(VolatileData().RubySpace(), MushRubyIntern::mHandleGameStart());
        PreCacheModeExit();
    }
}

void
AdanaxisLogic::RenderSequence(void)
{
    m_khaziCount = 0;
    AdanaxisData::tKhaziList::iterator khaziEndIter = SaveData().KhaziListWRef().end();
    for (AdanaxisData::tKhaziList::iterator p = SaveData().KhaziListWRef().begin(); p != khaziEndIter; ++p)
    {
        ++m_khaziCount;
    }  
    
    if (m_khaziCount != 0)
    {
        EndTimeSet(FrameMsec());
    }
    
    MushGameLogic::RenderSequence();
}

MushGamePiece&
AdanaxisLogic::PieceLookup(const std::string& inName) const
{
    MushGamePiece *pPiece = NULL;
    std::string objType;
    Mushware::U32 objNum;
    MushGameUtil::ObjectNameDecode(objType, objNum, inName);
    switch (objType[0])
    {
        case AdanaxisData::kCharProjectile:
            pPiece = &SaveData().Projectile(objNum);
            break;
            
        case AdanaxisData::kCharKhazi:
            pPiece = &SaveData().Khazi(objNum);
            break;
            
        default:
            pPiece = &MushGameLogic::PieceLookup(inName);
            break;
    }
    return *pPiece;
}

void
AdanaxisLogic::CollisionConsume(MushGameLogic& ioLogic, const MushGameMessageCollision& inMessage)
{    
    // Forward this message to both colliding objects
    try
    {
        PieceLookup(inMessage.ObjectName1()).MessageConsume(ioLogic, inMessage);
    }
    catch (MushcoreNonFatalFail& e)
    {
        MushcoreLog::Sgl().WarningLog() << "CollisionMessageConsume(1): " << e.what() << endl;    
    }
    try
    {
        PieceLookup(inMessage.ObjectName2()).MessageConsume(ioLogic, inMessage);
    }
    catch (MushcoreNonFatalFail& e)
    {
        MushcoreLog::Sgl().WarningLog() << "CollisionMessageConsume(2): " << e.what() << endl;    
    }
}

void
AdanaxisLogic::CollisionMessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    const MushGameMessageCollision *pCollision;
    
    if ((pCollision = dynamic_cast<const MushGameMessageCollision *>(&inMessage)) != NULL)
    {
        CollisionConsume(ioLogic, *pCollision);
    }
    else
    {
        MushGameLogic::CollisionMessageConsume(ioLogic, inMessage);
    }
}

void
AdanaxisLogic::MenuModeEnter(void)
{
    if (VolatileData().RubyGame().Value() != Mushware::kRubyQnil)
    {
        bool allowResume = SaveData().ClockStarted();
        
        MushRubyExec::Sgl().Call(VolatileData().RubyGame(),
                                 MushRubyIntern::mReset(),
                                 MushRubyValue(allowResume));
    }
    
    MushGameLogic::MenuModeEnter();
}

//%outOfLineFunctions {

const char *AdanaxisLogic::AutoName(void) const
{
    return "AdanaxisLogic";
}

MushcoreVirtualObject *AdanaxisLogic::AutoClone(void) const
{
    return new AdanaxisLogic(*this);
}

MushcoreVirtualObject *AdanaxisLogic::AutoCreate(void) const
{
    return new AdanaxisLogic;
}

MushcoreVirtualObject *AdanaxisLogic::AutoVirtualFactory(void)
{
    return new AdanaxisLogic;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisLogic", AdanaxisLogic::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisLogic::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameLogic::AutoPrint(ioOut);
    ioOut << "khaziCount=" << m_khaziCount << ", ";
    ioOut << "startTime=" << m_startTime << ", ";
    ioOut << "endTime=" << m_endTime << ", ";
    ioOut << "recordTime=" << m_recordTime << ", ";
    ioOut << "preCacheResult=" << m_preCacheResult;
    ioOut << "]";
}
bool
AdanaxisLogic::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "khaziCount")
    {
        ioIn >> m_khaziCount;
    }
    else if (inTagStr == "startTime")
    {
        ioIn >> m_startTime;
    }
    else if (inTagStr == "endTime")
    {
        ioIn >> m_endTime;
    }
    else if (inTagStr == "recordTime")
    {
        ioIn >> m_recordTime;
    }
    else if (inTagStr == "preCacheResult")
    {
        ioIn >> m_preCacheResult;
    }
    else if (MushGameLogic::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
AdanaxisLogic::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameLogic::AutoXMLPrint(ioOut);
    ioOut.TagSet("khaziCount");
    ioOut << m_khaziCount;
    ioOut.TagSet("startTime");
    ioOut << m_startTime;
    ioOut.TagSet("endTime");
    ioOut << m_endTime;
    ioOut.TagSet("recordTime");
    ioOut << m_recordTime;
    ioOut.TagSet("preCacheResult");
    ioOut << m_preCacheResult;
}
//%outOfLineFunctions } a70sQwDFt5hHHuygTk9r7A
