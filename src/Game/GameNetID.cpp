/*
 * $Id: GameNetID.cpp,v 1.1 2002/12/09 23:59:58 southa Exp $
 * $Log: GameNetID.cpp,v $
 * Revision 1.1  2002/12/09 23:59:58  southa
 * Network control
 *
 */

#include "GameNetID.h"

GameNetID::GameNetID(const string& inStr) :
    m_clientRef(inStr)
{
}

GameNetID::GameNetID(MustlData& ioData)
{
    Unpack(ioData);
}

GameNetID::~GameNetID()
{
}

MustlID *
GameNetID::Clone(void) const
{
    return new GameNetID(*this);
}

void
GameNetID::Pack(MustlData& ioData) const
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
GameNetID::Unpack(MustlData& ioData)
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

