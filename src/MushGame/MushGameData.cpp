//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameData.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } 7xCyH/qdl8oz3o5xeADXJg
/*
 * $Id: MushGameData.cpp,v 1.1 2005/06/21 13:10:51 southa Exp $
 * $Log: MushGameData.cpp,v $
 * Revision 1.1  2005/06/21 13:10:51  southa
 * MushGame work
 *
 */

#include "MushGameData.h"

MUSHCORE_DATA_INSTANCE(MushGameData);

MushGameData::MushGameData(const std::string& inName) :
    m_saveDataRef(inName),
    m_volatileDataRef(inName)
{
}
//%outOfLineFunctions {

const char *MushGameData::AutoName(void) const
{
    return "MushGameData";
}

MushcoreVirtualObject *MushGameData::AutoClone(void) const
{
    return new MushGameData(*this);
}

MushcoreVirtualObject *MushGameData::AutoCreate(void) const
{
    return new MushGameData;
}

MushcoreVirtualObject *MushGameData::AutoVirtualFactory(void)
{
    return new MushGameData;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameData", MushGameData::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameData::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "saveDataRef=" << m_saveDataRef << ", ";
    ioOut << "volatileDataRef=" << m_volatileDataRef;
    ioOut << "]";
}
bool
MushGameData::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "saveDataRef")
    {
        ioIn >> m_saveDataRef;
    }
    else if (inTagStr == "volatileDataRef")
    {
        ioIn >> m_volatileDataRef;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameData::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("saveDataRef");
    ioOut << m_saveDataRef;
    ioOut.TagSet("volatileDataRef");
    ioOut << m_volatileDataRef;
}
//%outOfLineFunctions } Cj5ZxkDEZH6fAvfD7hFszA
