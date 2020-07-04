//%includeGuardStart {
#ifndef MUSHGAMEDATA_H
#define MUSHGAMEDATA_H
//%includeGuardStart } J0x3N00IB49vTygTs4E50g
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameData.h
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
//%Header } jyMOXLjmbonlBdRcUz1+vA
/*
 * $Id: MushGameData.h,v 1.7 2007/03/09 11:29:13 southa Exp $
 * $Log: MushGameData.h,v $
 * Revision 1.7  2007/03/09 11:29:13  southa
 * Game end actions
 *
 * Revision 1.6  2007/03/08 11:00:29  southa
 * Level epilogue
 *
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
    
    // These values should agree with those in MushGame.rb
    enum tGameResult
    {
        kGameResultInvalid=0,
        kGameResultNone=1,
        kGameResultDead=2,
        kGameResultLost=3,
        kGameResultWon=4
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
