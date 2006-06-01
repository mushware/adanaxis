//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisLogic.cpp
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
//%Header } kEA/hGTYr5TaTuBUG+UAGA
/*
 * $Id: AdanaxisLogic.cpp,v 1.11 2005/08/02 14:37:44 southa Exp $
 * $Log: AdanaxisLogic.cpp,v $
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
#include "AdanaxisRender.h"
#include "AdanaxisUtil.h"

using namespace Mushware;
using namespace std;

AdanaxisLogic::AdanaxisLogic() :
    MushGameLogic(),
    m_khaziCount(1)
{
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
AdanaxisLogic::CollisionHandle(AdanaxisSaveData::tProjectile& ioProj,
                               AdanaxisSaveData::tKhazi& ioKhazi, const MushCollisionInfo& inCollInfo)
{
    bool fatal = true;
    
    MUSHCOREASSERT(inCollInfo.ObjectNamesValid());
    
    if (fatal)
    {
        MushGameMessageCollisionFatal fatalMesg("c:");
        fatalMesg.ObjectName1Set(inCollInfo.ObjectName1());
        fatalMesg.ObjectName2Set(inCollInfo.ObjectName2());
        fatalMesg.Post1Set(ioProj.Post());
        fatalMesg.Post2Set(ioProj.Post());
        if (inCollInfo.ChunkNumsValid())
        {
            fatalMesg.ChunkNum1Set(inCollInfo.ChunkNum1());
            fatalMesg.ChunkNum2Set(inCollInfo.ChunkNum2());
            fatalMesg.ChunkNumsValidSet(true);
        }
        else
        {
            fatalMesg.ChunkNumsValidSet(false);
        }
        CopyAndBroadcast(fatalMesg);
    }
}

// Slow version for debug - rechecks every object
void
AdanaxisLogic::ProjectilesFullCollide(void)
{
    typedef AdanaxisSaveData::tProjectileList tProjectileList;
    typedef AdanaxisSaveData::tKhaziList tKhaziList;

    MushCollisionResolver::Sgl().FrameMsecSet(VolatileData().FrameMsec());
    
    tProjectileList::const_iterator projectileEndIter = SaveData().ProjectileList().end();
    tKhaziList::const_iterator khaziEndIter = SaveData().KhaziList().end();
    for (tProjectileList::const_iterator p = SaveData().ProjectileList().begin(); p != projectileEndIter; ++p)
    {
        if (!p->ExpireFlag())
        {
            for (tKhaziList::const_iterator q = SaveData().KhaziList().begin(); q != khaziEndIter; ++q)
            {
                if (!q->ExpireFlag())
                {
                    MushCollisionInfo collInfo;
                    MushCollisionResolver::Sgl().Resolve(collInfo, *p, *q);
                    if (collInfo.SeparatingDistance() <= 0)
                    {
                        collInfo.ObjectName1Set(MushGameUtil::ObjectName(AdanaxisData::kCharProjectile, p.Key()));
                        collInfo.ObjectName2Set(MushGameUtil::ObjectName(AdanaxisData::kCharKhazi, q.Key()));
                        collInfo.ObjectNamesValidSet(true);
                        
                        CollisionHandle(*p, *q, collInfo);
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
}

void
AdanaxisLogic::CollideSequence(void)
{
    ProjectilesFullCollide();
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
    
    AdanaxisAppHandler& appHandler = AdanaxisUtil::AppHandler();
    
    if (appHandler.LatchedKeyStateTake('z'))
    {
        static bool show = true;
        if (show)
        {
            MushGameDialogueUtils::NamedDialoguesAdd(SaveData().DialoguesWRef(), "^keyhelp");
        }
        else
        {
            SaveData().DialoguesWRef().Clear();
        }
        show = !show;
    }
    
    MushGameLogic::RenderSequence();
}

MushGamePiece&
AdanaxisLogic::PieceLookup(const std::string& inName) const
{
    MushGamePiece *pPiece = NULL;
    Mushware::U8 objType;
    Mushware::U32 objNum;
    MushGameUtil::ObjectNameDecode(objType, objNum, inName);
    switch (objType)
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
AdanaxisLogic::CollisionFatalConsume(MushGameLogic& ioLogic, const MushGameMessageCollisionFatal& inMessage)
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
    const MushGameMessageCollisionFatal *pCollisionFatal;
    
    if ((pCollisionFatal = dynamic_cast<const MushGameMessageCollisionFatal *>(&inMessage)) != NULL)
    {
        CollisionFatalConsume(ioLogic, *pCollisionFatal);
    }
    else
    {
        MushGameLogic::CollisionMessageConsume(ioLogic, inMessage);
    }
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
    ioOut << "recordTime=" << m_recordTime;
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
}
//%outOfLineFunctions } bCjjtTQxMbrlyKOMMqlD2Q
