#ifndef GAMENETID_H
#define GAMENETID_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GameNetID.h,v 1.3 2002/12/20 13:17:41 southa Exp $
 * $Log: GameNetID.h,v $
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

#include "mushCore.h"
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
    const CoreDataRef<GameDefClient>& DataRefGet(void) const { return m_clientRef; }
    
private:
    CoreDataRef<GameDefClient> m_clientRef;
};

#endif
