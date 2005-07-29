//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisLogic.cpp
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
//%Header } ui3Az6sPZVE4olMwWeOmrw
/*
 * $Id: AdanaxisLogic.cpp,v 1.6 2005/07/29 08:27:46 southa Exp $
 * $Log: AdanaxisLogic.cpp,v $
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

#include "AdanaxisRender.h"

void
AdanaxisLogic::InitialDataCreate(void)
{
    VolatileData().ARenderMeshWRef().reset(new MushRenderMesh);
}

void
AdanaxisLogic::ProjectilesMove(void)
{
    typedef AdanaxisSaveData::tProjectileList tProjectileList;
    
    tProjectileList::tIter projectileEndIter = SaveData().ProjectileListWRef().end();
    for (tProjectileList::tIter p = SaveData().ProjectileListWRef().begin(); p != projectileEndIter;)
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
    
    tKhaziList::tIter khaziEndIter = SaveData().KhaziListWRef().end();
    for (tKhaziList::tIter p = SaveData().KhaziListWRef().begin(); p != khaziEndIter;)
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

// Slow version for debug - rechecks every object
void
AdanaxisLogic::ProjectilesFullCollide(void)
{
    typedef AdanaxisSaveData::tProjectileList tProjectileList;
    typedef AdanaxisSaveData::tKhaziList tKhaziList;
    
    MushCollisionResolver::Sgl().FrameMsecSet(VolatileData().FrameMsec());
    
    tProjectileList::tConstIter projectileEndIter = SaveData().ProjectileList().end();
    tKhaziList::tConstIter khaziEndIter = SaveData().KhaziList().end();
    for (tProjectileList::tConstIter p = SaveData().ProjectileList().begin(); p != projectileEndIter; ++p)
    {
        for (tKhaziList::tConstIter q = SaveData().KhaziList().begin(); q != khaziEndIter; ++q)
        {
            if (MushCollisionResolver::Sgl().Resolve(*p, *q) <= 0)
            {
                p->ExpireFlagSet(true);
                q->ExpireFlagSet(true);
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
}
//%outOfLineFunctions } CJla1G67YOsafSjFedjYqA
