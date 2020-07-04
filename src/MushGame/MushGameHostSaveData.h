//%includeGuardStart {
#ifndef MUSHGAMEHOSTSAVEDATA_H
#define MUSHGAMEHOSTSAVEDATA_H
//%includeGuardStart } j9WC99Joapgyyf6ZJO818A
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameHostSaveData.h
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
//%Header } DbFL8QdeOTOvwimpLaZiuw
/*
 * $Id: MushGameHostSaveData.h,v 1.9 2006/10/17 15:28:02 southa Exp $
 * $Log: MushGameHostSaveData.h,v $
 * Revision 1.9  2006/10/17 15:28:02  southa
 * Player collisions
 *
 * Revision 1.8  2006/10/02 17:25:05  southa
 * Object lookup and target selection
 *
 * Revision 1.7  2006/06/01 15:39:22  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/07/29 14:59:49  southa
 * Maptor access
 *
 * Revision 1.5  2005/06/23 17:25:25  southa
 * MushGame link work
 *
 * Revision 1.4  2005/06/23 13:56:58  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/23 11:58:28  southa
 * MushGame link work
 *
 * Revision 1.2  2005/06/22 20:01:58  southa
 * MushGame link work
 *
 * Revision 1.1  2005/06/21 15:57:47  southa
 * MushGame work
 *
 */

#include "MushGameStandard.h"

#include "MushGameAddress.h"
#include "MushGameJob.h"
#include "MushGamePiecePlayer.h"

//:generate virtual standard ostream xml1 nocopy
class MushGameHostSaveData : public MushcoreVirtualObject
{
public:
    typedef std::vector< MushcoreDataRef<MushGameAddress> > tClientAddrRefs;
    
    MushGameHostSaveData();
    virtual ~MushGameHostSaveData() {}
    virtual void GroupingNameSet(const std::string& inName) {}
    
private:
    std::string m_serverName; //:readwrite
    MushcoreMaptor<MushGamePiecePlayer> m_hostPlayersList; //:read :wref
    Mushware::U32 m_nextPlayerNum; //:readwrite :wref
    Mushware::U32 m_maxPlayersAllowed; //:readwrite
    MushcoreData<MushGameJob> m_jobList; //:read :wref
    tClientAddrRefs m_clientAddrRefs; //:readwrite :wref

//%classPrototypes {
public:
    const std::string& ServerName(void) const { return m_serverName; }
    void ServerNameSet(const std::string& inValue) { m_serverName=inValue; }
    const MushcoreMaptor<MushGamePiecePlayer>& HostPlayersList(void) const { return m_hostPlayersList; }
    // Writable reference for m_hostPlayersList
    MushcoreMaptor<MushGamePiecePlayer>& HostPlayersListWRef(void) { return m_hostPlayersList; }
    const Mushware::U32& NextPlayerNum(void) const { return m_nextPlayerNum; }
    void NextPlayerNumSet(const Mushware::U32& inValue) { m_nextPlayerNum=inValue; }
    // Writable reference for m_nextPlayerNum
    Mushware::U32& NextPlayerNumWRef(void) { return m_nextPlayerNum; }
    const Mushware::U32& MaxPlayersAllowed(void) const { return m_maxPlayersAllowed; }
    void MaxPlayersAllowedSet(const Mushware::U32& inValue) { m_maxPlayersAllowed=inValue; }
    const MushcoreData<MushGameJob>& JobList(void) const { return m_jobList; }
    // Writable reference for m_jobList
    MushcoreData<MushGameJob>& JobListWRef(void) { return m_jobList; }
    const tClientAddrRefs& ClientAddrRefs(void) const { return m_clientAddrRefs; }
    void ClientAddrRefsSet(const tClientAddrRefs& inValue) { m_clientAddrRefs=inValue; }
    // Writable reference for m_clientAddrRefs
    tClientAddrRefs& ClientAddrRefsWRef(void) { return m_clientAddrRefs; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } T/iPy9H3zttlLc0uss+bdQ
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameHostSaveData& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } B6IOtWAQqmeuE/0ZprefTQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
