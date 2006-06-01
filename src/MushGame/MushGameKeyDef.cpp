//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameKeyDef.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } cC+qoCB7VQVSsmwgWq6ijQ
/*
 * $Id: MushGameKeyDef.cpp,v 1.1 2005/07/11 16:37:46 southa Exp $
 * $Log: MushGameKeyDef.cpp,v $
 * Revision 1.1  2005/07/11 16:37:46  southa
 * Uplink control work
 *
 */

#include "MushGameKeyDef.h"

MushGameKeyDef::MushGameKeyDef() :
    m_state(false),
    m_stateHasChanged(true)
{
}

//%outOfLineFunctions {

const char *MushGameKeyDef::AutoName(void) const
{
    return "MushGameKeyDef";
}

MushcoreVirtualObject *MushGameKeyDef::AutoClone(void) const
{
    return new MushGameKeyDef(*this);
}

MushcoreVirtualObject *MushGameKeyDef::AutoCreate(void) const
{
    return new MushGameKeyDef;
}

MushcoreVirtualObject *MushGameKeyDef::AutoVirtualFactory(void)
{
    return new MushGameKeyDef;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameKeyDef", MushGameKeyDef::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameKeyDef::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "keyValue=" << m_keyValue << ", ";
    ioOut << "state=" << m_state << ", ";
    ioOut << "stateHasChanged=" << m_stateHasChanged << ", ";
    ioOut << "keyName=" << m_keyName;
    ioOut << "]";
}
bool
MushGameKeyDef::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "keyValue")
    {
        ioIn >> m_keyValue;
    }
    else if (inTagStr == "state")
    {
        ioIn >> m_state;
    }
    else if (inTagStr == "stateHasChanged")
    {
        ioIn >> m_stateHasChanged;
    }
    else if (inTagStr == "keyName")
    {
        ioIn >> m_keyName;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameKeyDef::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("keyValue");
    ioOut << m_keyValue;
    ioOut.TagSet("state");
    ioOut << m_state;
    ioOut.TagSet("stateHasChanged");
    ioOut << m_stateHasChanged;
    ioOut.TagSet("keyName");
    ioOut << m_keyName;
}
//%outOfLineFunctions } Xw2tEfjCwGJryG243fyj0w
