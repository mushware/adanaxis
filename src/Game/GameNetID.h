/*
 * $Id: GameNetID.h,v 1.1 2002/12/09 23:59:58 southa Exp $
 * $Log: GameNetID.h,v $
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
    explicit GameNetID(const string& inStr);
    explicit GameNetID(MustlData& ioData);
    virtual ~GameNetID();
    virtual MustlID *Clone(void) const;
    virtual void Pack(MustlData& ioData) const;
    virtual void Unpack(MustlData& ioData);
    virtual void Print(ostream& ioOut) const;

    void NameSuffixAdd(const string& inStr);
    const CoreDataRef<GameDefClient>& DataRefGet(void) const { return m_clientRef; }
    
private:
    CoreDataRef<GameDefClient> m_clientRef;
};

