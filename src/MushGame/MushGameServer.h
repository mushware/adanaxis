//%includeGuardStart {
#ifndef MUSHGAMESERVER_H
#define MUSHGAMESERVER_H
//%includeGuardStart } /8O1HzUXaK1cJonENvb/UA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameServer.h
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
//%Header } OnihspdzP+QwmL29ifucbw
/*
 * $Id: MushGameServer.h,v 1.5 2006/06/01 15:39:27 southa Exp $
 * $Log: MushGameServer.h,v $
 * Revision 1.5  2006/06/01 15:39:27  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.3  2005/06/20 14:30:36  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/16 17:25:39  southa
 * Client/server work
 *
 * Revision 1.1  2005/06/16 10:49:00  southa
 * Client/server work
 *
 */

#include "MushGameStandard.h"

#include "MushGameMessage.h"
#include "MushGameReceiver.h"
#include "MushGameSaveData.h"

class MushGameLogic;

//:generate virtual standard ostream xml1
class MushGameServer : public MushGameReceiver, public MushcoreVirtualObject
{
public:
    MushGameServer();
    virtual ~MushGameServer() {}
    virtual void GroupingNameSet(const std::string& inName) { m_saveDataRef.NameSet(inName); }
    
    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);
    virtual void JoinRequestConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);

protected:
    virtual MushGameSaveData& SaveData(void) { return m_saveDataRef.WRef(); }
    
private:
    MushcoreDataRef<MushGameSaveData> m_saveDataRef; //:readwrite
    
//%classPrototypes {
public:
    const MushcoreDataRef<MushGameSaveData>& SaveDataRef(void) const { return m_saveDataRef; }
    void SaveDataRefSet(const MushcoreDataRef<MushGameSaveData>& inValue) { m_saveDataRef=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } ubL5/BGsHDA7qLRa70BiHg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameServer& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } wnCNdjxn4Bego5Zc0gqicA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
