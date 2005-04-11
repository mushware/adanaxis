//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameCode.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } XFL+DWouGhuYPyYSkOTTtA
/*
 * $Id$
 * $Log$
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

const char *GameCode::AutoNameGet(void) const
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
        ioIn >> *this;
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
//%outOfLineFunctions } OsizbnSU6jHYE6zq+hyZLw
