//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameNetID.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 4bpr91c1ceJF34qEJv4Vyg
/*
 * $Id: GameNetID.cpp,v 1.6 2003/08/21 23:08:49 southa Exp $
 * $Log: GameNetID.cpp,v $
 * Revision 1.6  2003/08/21 23:08:49  southa
 * Fixed file headers
 *
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

