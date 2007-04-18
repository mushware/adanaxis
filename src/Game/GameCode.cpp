//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameCode.cpp
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } rQMIcBjw+dYoPmnvbWhKwg
/*
 * $Id: GameCode.cpp,v 1.6 2006/06/01 15:38:56 southa Exp $
 * $Log: GameCode.cpp,v $
 * Revision 1.6  2006/06/01 15:38:56  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.4  2005/06/20 14:30:34  southa
 * Adanaxis work
 *
 * Revision 1.3  2005/06/16 17:25:38  southa
 * Client/server work
 *
 * Revision 1.2  2005/05/19 13:02:01  southa
 * Mac release work
 *
 * Revision 1.1  2005/04/11 23:31:41  southa
 * Startup and registration screen
 *
 */

#include "GameCode.h"

using namespace Mushware;

MUSHCORE_DATA_INSTANCE(GameCode);

std::string
GameCode::Code(void) const
{
    std::string retStr(m_code);
    if (m_crypt.length() != m_code.length())
    {
        retStr = "";
    }
    else
    {
        for (U32 i=0; i<m_code.length(); ++i)
        {
            retStr[i] -= 'A'-'0';
            retStr[i] ^= (m_crypt[i] - '0');
        }
    }
    return retStr;
}

void
GameCode::CodeSet(const std::string& inStr)
{
    m_code.resize(inStr.length());
    m_crypt.resize(inStr.length());
    for (U32 i=0; i<inStr.length(); ++i)
    {
        m_code[i] = inStr[i];
        m_crypt[i] = MushcoreUtil::RandomU32('0', '9');
        m_code[i] ^= (m_crypt[i] - '0');
        m_code[i] += 'A'-'0';
    }
}
//%outOfLineFunctions {

const char *GameCode::AutoName(void) const
{
    return "GameCode";
}

MushcoreVirtualObject *GameCode::AutoClone(void) const
{
    return new GameCode(*this);
}

MushcoreVirtualObject *GameCode::AutoCreate(void) const
{
    return new GameCode;
}

MushcoreVirtualObject *GameCode::AutoVirtualFactory(void)
{
    return new GameCode;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("GameCode", GameCode::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
bool
GameCode::AutoEquals(const GameCode& inObj) const
{
    return 1
        && (m_code == inObj.m_code)
        && (m_crypt == inObj.m_crypt)
    ;
}
void
GameCode::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "code=" << m_code << ", ";
    ioOut << "crypt=" << m_crypt;
    ioOut << "]";
}
bool
GameCode::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "code")
    {
        ioIn >> m_code;
    }
    else if (inTagStr == "crypt")
    {
        ioIn >> m_crypt;
    }
    else 
    {
        return false;
    }
    return true;
}
void
GameCode::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("code");
    ioOut << m_code;
    ioOut.TagSet("crypt");
    ioOut << m_crypt;
}
//%outOfLineFunctions } 4ehmdPjlyT0y+nCcw4hqng
