//%Header {
/*****************************************************************************
 *
 * File: src/MustlGame/MustlGameID.cpp
 *
 * Copyright Andy Southgate 2002-2004
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } BJ1HyubBOO2he8vzsyhCsA
/*
 * $Id: MustlGameID.cpp,v 1.2 2003/10/06 22:42:04 southa Exp $
 * $Log: MustlGameID.cpp,v $
 * Revision 1.2  2003/10/06 22:42:04  southa
 * Include fixes
 *
 * Revision 1.1  2003/10/06 22:22:38  southa
 * Moved from Game to MustlGame
 *
 * Revision 1.7  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
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

#include "MustlGameID.h"

#include "MustlGameSTL.h"

using namespace Mushware;
using namespace std;

MustlGameID::MustlGameID(const string& inStr) :
    m_clientRef(inStr)
{
}

MustlGameID::MustlGameID(MustlData& ioData)
{
    Unpack(ioData);
}

MustlGameID::~MustlGameID()
{
}

MustlID *
MustlGameID::Clone(void) const
{
    return new MustlGameID(*this);
}

void
MustlGameID::Pack(MustlData& ioData) const
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
MustlGameID::Unpack(MustlData& ioData)
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
MustlGameID::Print(ostream& ioOut) const
{
    ioOut << m_clientRef.NameGet();
}

void
MustlGameID::NameSuffixAdd(const string& inStr)
{
    m_clientRef.NameSet(m_clientRef.NameGet() + inStr);
}

