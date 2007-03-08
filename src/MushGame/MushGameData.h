//%includeGuardStart {
#ifndef MUSHGAMEDATA_H
#define MUSHGAMEDATA_H
//%includeGuardStart } J0x3N00IB49vTygTs4E50g
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameData.h
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } ntJSLwt7PJWQN4kA9w6N3Q
/*
 * $Id: MushGameData.h,v 1.5 2006/06/01 15:39:21 southa Exp $
 * $Log: MushGameData.h,v $
 * Revision 1.5  2006/06/01 15:39:21  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/08/01 13:09:58  southa
 * Collision messaging
 *
 * Revision 1.3  2005/06/29 09:07:56  southa
 * MushGame camera work
 *
 * Revision 1.2  2005/06/21 15:57:47  southa
 * MushGame work
 *
 * Revision 1.1  2005/06/21 13:10:51  southa
 * MushGame work
 *
 */

#include "MushGameStandard.h"

class MushGameSaveData;
class MushGameVolatileData;

//:generate virtual standard ostream xml1
class MushGameData : public MushcoreVirtualObject
{
public:
    enum
    {
        kCharCollision = 'c',
        kCharPlayer = 'p',
        kCharJob = 'j'
    };
    
    enum tGameResult
    {
        kGameResultInvalid,
        kGameResultNone,
        kGameResultDead,
        kGameResultLost,
        kGameResultWon
    };
    
    MushGameData(const std::string& inName="");
    virtual ~MushGameData() {}
    virtual void GroupingNameSet(const std::string& inName);

private:
    MushcoreDataRef<MushGameSaveData> m_saveDataRef; //:readwrite :wref
    MushcoreDataRef<MushGameVolatileData> m_volatileDataRef; //:readwrite :wref
//%classPrototypes {
public:
    const MushcoreDataRef<MushGameSaveData>& SaveDataRef(void) const { return m_saveDataRef; }
    void SaveDataRefSet(const MushcoreDataRef<MushGameSaveData>& inValue) { m_saveDataRef=inValue; }
    // Writable reference for m_saveDataRef
    MushcoreDataRef<MushGameSaveData>& SaveDataRefWRef(void) { return m_saveDataRef; }
    const MushcoreDataRef<MushGameVolatileData>& VolatileDataRef(void) const { return m_volatileDataRef; }
    void VolatileDataRefSet(const MushcoreDataRef<MushGameVolatileData>& inValue) { m_volatileDataRef=inValue; }
    // Writable reference for m_volatileDataRef
    MushcoreDataRef<MushGameVolatileData>& VolatileDataRefWRef(void) { return m_volatileDataRef; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } QBUFDRUVWiHT0subXKI7zA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameData& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } amQQI1cmoPOho/k0IA5ToA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
