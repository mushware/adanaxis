//%includeGuardStart {
#ifndef GAMENETID_H
#define GAMENETID_H
//%includeGuardStart } HZhOxdY04PoP3S2uOYAY2A
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameNetID.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } vzoQZGcmMzMJMgoZfNuZDA
/*
 * $Id: GameNetID.h,v 1.7 2003/08/21 23:08:50 southa Exp $
 * $Log: GameNetID.h,v $
 * Revision 1.7  2003/08/21 23:08:50  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.5  2003/01/09 14:57:02  southa
 * Created Mushcore
 *
 * Revision 1.4  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.3  2002/12/20 13:17:41  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/12 14:00:39  southa
 * Created Mustl
 *
 * Revision 1.1  2002/12/09 23:59:58  southa
 * Network control
 *
 */

#include "Mushcore.h"
#include "mushMedia.h"

#include "GameDefClient.h"

class GameNetID : public MustlID
{
public:
    explicit GameNetID(const std::string& inStr);
    explicit GameNetID(MustlData& ioData);
    virtual ~GameNetID();
    virtual MustlID *Clone(void) const;
    virtual void Pack(MustlData& ioData) const;
    virtual void Unpack(MustlData& ioData);
    virtual void Print(std::ostream& ioOut) const;

    void NameSuffixAdd(const std::string& inStr);
    const MushcoreDataRef<GameDefClient>& DataRefGet(void) const { return m_clientRef; }
    
private:
    MushcoreDataRef<GameDefClient> m_clientRef;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
