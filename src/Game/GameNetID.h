/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"
#include "mushMedia.h"

#include "GameDefClient.h"

class GameNetID : public MediaNetID
{
public:
    explicit GameNetID(const string& inStr);
    explicit GameNetID(MediaNetData& ioData);
    virtual ~GameNetID();
    virtual MediaNetID *Clone(void) const;
    virtual void Pack(MediaNetData& ioData) const;
    virtual void Unpack(MediaNetData& ioData);
    virtual void Print(ostream& ioOut) const;

    void NameSuffixAdd(const string& inStr);
    const CoreDataRef<GameDefClient>& DataRefGet(void) const { return m_clientRef; }
    
private:
    CoreDataRef<GameDefClient> m_clientRef;
};

