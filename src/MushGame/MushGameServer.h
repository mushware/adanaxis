//%includeGuardStart {
#ifndef MUSHGAMESERVER_H
#define MUSHGAMESERVER_H
//%includeGuardStart } /8O1HzUXaK1cJonENvb/UA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameServer.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } okZwqrFoOPduCmtBZnptBQ
/*
 * $Id: MushGameServer.h,v 1.2 2005/06/16 17:25:39 southa Exp $
 * $Log: MushGameServer.h,v $
 * Revision 1.2  2005/06/16 17:25:39  southa
 * Client/server work
 *
 * Revision 1.1  2005/06/16 10:49:00  southa
 * Client/server work
 *
 */

#include "MushGameStandard.h"

#include "MushGameMailbox.h"
#include "MushGameMessage.h"

#include "MushGameSaveData.h"

//:generate virtual standard ostream xml1
class MushGameServer : public MushcoreVirtualObject
{
public:
    MushGameServer();
    virtual ~MushGameServer() {}
    virtual void MessageConsume(MushGameMailbox& outReplyBox, const MushGameMessage& inMessage);
    virtual void JoinRequestConsume(MushGameMailbox& outReplyBox, const MushGameMessage& inMessage);

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
