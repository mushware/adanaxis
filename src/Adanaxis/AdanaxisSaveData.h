//%includeGuardStart {
#ifndef ADANAXISSAVEDATA_H
#define ADANAXISSAVEDATA_H
//%includeGuardStart } Phse6V6gEtb3LIdaz1rQlw
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisSaveData.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } U4rY8j1m8KDu6kz8Bfsl2Q
/*
 * $Id: AdanaxisSaveData.h,v 1.24 2007/06/13 14:08:48 southa Exp $
 * $Log: AdanaxisSaveData.h,v $
 * Revision 1.24  2007/06/13 14:08:48  southa
 * Level 29
 *
 * Revision 1.23  2007/06/07 13:23:03  southa
 * Level 24
 *
 * Revision 1.22  2007/05/10 14:06:26  southa
 * Level 16 and retina spin
 *
 * Revision 1.21  2007/04/21 09:41:07  southa
 * Level work
 *
 * Revision 1.20  2007/04/18 09:22:04  southa
 * Header and level fixes
 *
 * Revision 1.19  2007/04/16 08:41:09  southa
 * Level and header mods
 *
 * Revision 1.18  2007/03/20 17:31:24  southa
 * Difficulty and GL options
 *
 * Revision 1.17  2006/11/03 18:46:33  southa
 * Damage effectors
 *
 * Revision 1.16  2006/10/19 15:41:36  southa
 * Item handling
 *
 * Revision 1.15  2006/08/01 17:21:29  southa
 * River demo
 *
 * Revision 1.14  2006/07/31 11:01:36  southa
 * Music and dialogues
 *
 * Revision 1.13  2006/07/28 11:14:28  southa
 * Records for multiple spaces
 *
 * Revision 1.12  2006/07/27 13:51:34  southa
 * Menu and control fixes
 *
 * Revision 1.11  2006/06/01 15:38:48  southa
 * DrawArray verification and fixes
 *
 * Revision 1.10  2005/08/01 13:09:57  southa
 * Collision messaging
 *
 * Revision 1.9  2005/07/29 14:59:49  southa
 * Maptor access
 *
 * Revision 1.8  2005/07/29 11:52:43  southa
 * MushcoreMaptor created
 *
 * Revision 1.7  2005/07/29 08:27:47  southa
 * Collision work
 *
 * Revision 1.6  2005/07/12 12:18:17  southa
 * Projectile work
 *
 * Revision 1.5  2005/06/30 14:26:35  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 * Revision 1.3  2005/06/20 14:30:33  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/16 17:25:37  southa
 * Client/server work
 *
 * Revision 1.1  2005/06/14 20:39:40  southa
 * Adanaxis work
 *
 */

#include "AdanaxisStandard.h"

#include "AdanaxisPieceEffector.h"
#include "AdanaxisPieceItem.h"
#include "AdanaxisPieceKhazi.h"
#include "AdanaxisPieceProjectile.h"

#include "API/mushGame.h"
#include "API/mushMushGame.h"

//:xml1base MushGameSaveData
//:generate virtual standard ostream xml1 nocopy
class AdanaxisSaveData : public MushGameSaveData
{
public:
    typedef AdanaxisPieceProjectile tProjectile;
    typedef MushcoreMaptor<tProjectile> tProjectileList;
    typedef AdanaxisPieceKhazi tKhazi;
    typedef MushcoreMaptor<tKhazi> tKhaziList;
    typedef AdanaxisPieceItem tItem;
    typedef MushcoreMaptor<tItem> tItemList;
    typedef AdanaxisPieceEffector tEffector;
    typedef MushcoreMaptor<tEffector> tEffectorList;

    AdanaxisSaveData();
    virtual ~AdanaxisSaveData() {}

    tProjectile& Projectile(Mushware::U32 inNum) { return m_projectileList.Get(inNum); }
    const tProjectile& Projectile(Mushware::U32 inNum) const { return m_projectileList.Get(inNum); }
    tKhazi& Khazi(Mushware::U32 inNum) { return m_khaziList.Get(inNum); }
    const tKhazi& Khazi(Mushware::U32 inNum) const { return m_khaziList.Get(inNum); }
    tEffector& Effector(Mushware::U32 inNum) { return m_effectorList.Get(inNum); }
    const tEffector& Effector(Mushware::U32 inNum) const { return m_effectorList.Get(inNum); }
    
private:
    tProjectileList m_projectileList; //:read :wref
    tKhaziList m_khaziList; //:read :wref
    tItemList m_itemList; //:read :wref
    tEffectorList m_effectorList; //:read :wref
    bool m_clockStarted; //:readwrite
    std::string m_spaceName; //:readwrite
    Mushware::U32 m_gameDifficulty; //:readwrite
    Mushware::U32 m_primaryType; //:readwrite
    Mushware::tVal m_retinaSpin; //:readwrite
    Mushware::tVal m_permanentSpin; //:readwrite
    Mushware::tVal m_permanentThrust; //:readwrite
    Mushware::tVal m_speedAugmentation; //:readwrite
    
//%classPrototypes {
public:
    const tProjectileList& ProjectileList(void) const { return m_projectileList; }
    // Writable reference for m_projectileList
    tProjectileList& ProjectileListWRef(void) { return m_projectileList; }
    const tKhaziList& KhaziList(void) const { return m_khaziList; }
    // Writable reference for m_khaziList
    tKhaziList& KhaziListWRef(void) { return m_khaziList; }
    const tItemList& ItemList(void) const { return m_itemList; }
    // Writable reference for m_itemList
    tItemList& ItemListWRef(void) { return m_itemList; }
    const tEffectorList& EffectorList(void) const { return m_effectorList; }
    // Writable reference for m_effectorList
    tEffectorList& EffectorListWRef(void) { return m_effectorList; }
    const bool& ClockStarted(void) const { return m_clockStarted; }
    void ClockStartedSet(const bool& inValue) { m_clockStarted=inValue; }
    const std::string& SpaceName(void) const { return m_spaceName; }
    void SpaceNameSet(const std::string& inValue) { m_spaceName=inValue; }
    const Mushware::U32& GameDifficulty(void) const { return m_gameDifficulty; }
    void GameDifficultySet(const Mushware::U32& inValue) { m_gameDifficulty=inValue; }
    const Mushware::U32& PrimaryType(void) const { return m_primaryType; }
    void PrimaryTypeSet(const Mushware::U32& inValue) { m_primaryType=inValue; }
    const Mushware::tVal& RetinaSpin(void) const { return m_retinaSpin; }
    void RetinaSpinSet(const Mushware::tVal& inValue) { m_retinaSpin=inValue; }
    const Mushware::tVal& PermanentSpin(void) const { return m_permanentSpin; }
    void PermanentSpinSet(const Mushware::tVal& inValue) { m_permanentSpin=inValue; }
    const Mushware::tVal& PermanentThrust(void) const { return m_permanentThrust; }
    void PermanentThrustSet(const Mushware::tVal& inValue) { m_permanentThrust=inValue; }
    const Mushware::tVal& SpeedAugmentation(void) const { return m_speedAugmentation; }
    void SpeedAugmentationSet(const Mushware::tVal& inValue) { m_speedAugmentation=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 2mlGh1qkeP5MjeZ4WabLrA
};

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisSaveData& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } +jNhUDLSnXe2KY7BCQ1TrA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
