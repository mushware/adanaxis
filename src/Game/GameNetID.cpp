/*
 * $Id$
 * $Log$
 */

#include "GameNetID.h"

GameNetID::GameNetID(const string& inStr) :
    m_clientRef(inStr)
{
}

GameNetID::GameNetID(MediaNetData& ioData)
{
    Unpack(ioData);
}

GameNetID::~GameNetID()
{
}

MediaNetID *
GameNetID::Clone(void) const
{
    return new GameNetID(*this);
}

void
GameNetID::Pack(MediaNetData& ioData) const
{
    const string& clientName = m_clientRef.NameGet();
    
    U32 size=clientName.size();
    if (size > 255) size=255;
    ioData.BytePush(size);
    for (U32 i=0; i<size; ++i)
    {
        ioData.BytePush(clientName[i]);
    }
}

void
GameNetID::Unpack(MediaNetData& ioData)
{
    string clientName = "";
    U32 size=ioData.MessageBytePop();
    for (U32 i=0; i<size; ++i)
    {
        clientName += ioData.MessageBytePop();
    }
    m_clientRef.NameSet(clientName);
}

void
GameNetID::Print(ostream& ioOut) const
{
    ioOut << m_clientRef.NameGet();
}

void
GameNetID::NameSuffixAdd(const string& inStr)
{
    m_clientRef.NameSet(m_clientRef.NameGet() + inStr);
}

