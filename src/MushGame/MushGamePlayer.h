//%includeGuardStart {
#ifndef MUSHGAMEPLAYER_H
#define MUSHGAMEPLAYER_H
//%includeGuardStart } foHvGbTEB8G6XgqJu9SuYA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGamePlayer.h
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
//%Header } oGbXkYO013mPUX90XE1YJg
/*
 * $Id: MushGamePlayer.h,v 1.4 2005/06/24 10:30:13 southa Exp $
 * $Log: MushGamePlayer.h,v $
 * Revision 1.4  2005/06/24 10:30:13  southa
 * MushGame camera work
 *
 * Revision 1.3  2005/06/23 17:25:25  southa
 * MushGame link work
 *
 * Revision 1.2  2005/06/20 14:30:36  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 17:25:39  southa
 * Client/server work
 *
 */

#include "MushGameStandard.h"

#include "MushGameMailbox.h"
#include "MushGameMessage.h"
#include "MushGamePiece.h"

#include "API/mushMushMesh.h"

//:xml1base MushGamePiece
//:generate virtual standard ostream xml1
class MushGamePlayer : public MushGamePiece
{
public:
    explicit MushGamePlayer(std::string inID = "");
    virtual ~MushGamePlayer() {}
    virtual void MessageConsume(MushGameMailbox& outReplyBox, const MushGameMessage& inMessage);
    
private:
    std::string m_id; //:readwrite
    std::string m_playerName; //:readwrite
    
//%classPrototypes {
public:
    const std::string& Id(void) const { return m_id; }
    void IdSet(const std::string& inValue) { m_id=inValue; }
    const std::string& PlayerName(void) const { return m_playerName; }
    void PlayerNameSet(const std::string& inValue) { m_playerName=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } gvkiiHri0IKJ//RIXIKreQ
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGamePlayer& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } qNoomoiXq6eGt3pwxj2Fmw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
