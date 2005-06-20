//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameDigest.cpp
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
//%Header } DEIbaed/fMvMVvkt6iWKMg
/*
 * $Id: MushGameDigest.cpp,v 1.1 2005/06/16 10:48:59 southa Exp $
 * $Log: MushGameDigest.cpp,v $
 * Revision 1.1  2005/06/16 10:48:59  southa
 * Client/server work
 *
 */

#include "MushGameDigest.h"

MushGameDigest::MushGameDigest()
{
}
//%outOfLineFunctions {

const char *MushGameDigest::AutoName(void) const
{
    return "MushGameDigest";
}

MushcoreVirtualObject *MushGameDigest::AutoClone(void) const
{
    return new MushGameDigest(*this);
}

MushcoreVirtualObject *MushGameDigest::AutoCreate(void) const
{
    return new MushGameDigest;
}

MushcoreVirtualObject *MushGameDigest::AutoVirtualFactory(void)
{
    return new MushGameDigest;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameDigest", MushGameDigest::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameDigest::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "digestID=" << m_digestID << ", ";
    ioOut << "content=" << m_content;
    ioOut << "]";
}
bool
MushGameDigest::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "digestID")
    {
        ioIn >> m_digestID;
    }
    else if (inTagStr == "content")
    {
        ioIn >> m_content;
    }
    else
    {
        return false;
    }
    return true;
}
void
MushGameDigest::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("digestID");
    ioOut << m_digestID;
    ioOut.TagSet("content");
    ioOut << m_content;
}
//%outOfLineFunctions } hoqKVoZXptIRU4P2f53peA
