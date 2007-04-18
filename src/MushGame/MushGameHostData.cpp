//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameHostData.cpp
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
//%Header } HZYX7CeyI1MilMYEfYZiqw
/*
 * $Id: MushGameHostData.cpp,v 1.3 2006/06/01 15:39:21 southa Exp $
 * $Log: MushGameHostData.cpp,v $
 * Revision 1.3  2006/06/01 15:39:21  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.1  2005/06/21 15:57:47  southa
 * MushGame work
 *
 */

#include "MushGameHostData.h"

MUSHCORE_DATA_INSTANCE(MushGameHostData);

MushGameHostData::MushGameHostData(const std::string& inName) :
    m_saveDataRef(inName),
    m_volatileDataRef(inName)
{
}
//%outOfLineFunctions {

const char *MushGameHostData::AutoName(void) const
{
    return "MushGameHostData";
}

MushcoreVirtualObject *MushGameHostData::AutoClone(void) const
{
    return new MushGameHostData(*this);
}

MushcoreVirtualObject *MushGameHostData::AutoCreate(void) const
{
    return new MushGameHostData;
}

MushcoreVirtualObject *MushGameHostData::AutoVirtualFactory(void)
{
    return new MushGameHostData;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameHostData", MushGameHostData::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameHostData::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "saveDataRef=" << m_saveDataRef << ", ";
    ioOut << "volatileDataRef=" << m_volatileDataRef;
    ioOut << "]";
}
bool
MushGameHostData::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushGameHostData::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("saveDataRef");
    ioOut << m_saveDataRef;
    ioOut.TagSet("volatileDataRef");
    ioOut << m_volatileDataRef;
}
//%outOfLineFunctions } QSkyIHK3sNqw8Yo0MD9MiQ
