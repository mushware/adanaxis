/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GameNetID.cpp,v 1.5 2003/01/13 14:31:59 southa Exp $
 * $Log: GameNetID.cpp,v $
 * Revision 1.5  2003/01/13 14:31:59  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.4  2002/12/29 20:59:56  southa
 * More build fixes
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

#include "GameNetID.h"

#include "GameSTL.h"

using namespace Mushware;
using namespace std;

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

