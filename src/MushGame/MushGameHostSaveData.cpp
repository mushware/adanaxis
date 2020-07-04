//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameHostSaveData.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } OSkJ31PaLKFT+H8BMt9J7A
/*
 * $Id: MushGameHostSaveData.cpp,v 1.8 2006/10/17 15:28:02 southa Exp $
 * $Log: MushGameHostSaveData.cpp,v $
 * Revision 1.8  2006/10/17 15:28:02  southa
 * Player collisions
 *
 * Revision 1.7  2006/06/01 15:39:22  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/07/29 14:59:49  southa
 * Maptor access
 *
 * Revision 1.5  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.4  2005/06/23 17:25:25  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/23 13:56:58  southa
 * MushGame link work
 *
 * Revision 1.2  2005/06/23 11:58:28  southa
 * MushGame link work
 *
 * Revision 1.1  2005/06/21 15:57:47  southa
 * MushGame work
 *
 */

#include "MushGameHostSaveData.h"

#include "MushGameJob.h"

MUSHCORE_DATA_INSTANCE(MushGameHostSaveData);

MushGameHostSaveData::MushGameHostSaveData() :
    m_nextPlayerNum(2),
    m_maxPlayersAllowed(4)
{
}

//%outOfLineFunctions {

const char *MushGameHostSaveData::AutoName(void) const
{
    return "MushGameHostSaveData";
}

MushcoreVirtualObject *MushGameHostSaveData::AutoClone(void) const
{
    throw MushcoreRequestFail("Cannot clone 'MushGameHostSaveData'");;
}

MushcoreVirtualObject *MushGameHostSaveData::AutoCreate(void) const
{
    return new MushGameHostSaveData;
}

MushcoreVirtualObject *MushGameHostSaveData::AutoVirtualFactory(void)
{
    return new MushGameHostSaveData;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameHostSaveData", MushGameHostSaveData::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameHostSaveData::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "serverName=" << m_serverName << ", ";
    ioOut << "hostPlayersList=" << m_hostPlayersList << ", ";
    ioOut << "nextPlayerNum=" << m_nextPlayerNum << ", ";
    ioOut << "maxPlayersAllowed=" << m_maxPlayersAllowed << ", ";
    ioOut << "jobList=" << m_jobList << ", ";
    ioOut << "clientAddrRefs=" << m_clientAddrRefs;
    ioOut << "]";
}
bool
MushGameHostSaveData::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "serverName")
    {
        ioIn >> m_serverName;
    }
    else if (inTagStr == "hostPlayersList")
    {
        ioIn >> m_hostPlayersList;
    }
    else if (inTagStr == "nextPlayerNum")
    {
        ioIn >> m_nextPlayerNum;
    }
    else if (inTagStr == "maxPlayersAllowed")
    {
        ioIn >> m_maxPlayersAllowed;
    }
    else if (inTagStr == "jobList")
    {
        ioIn >> m_jobList;
    }
    else if (inTagStr == "clientAddrRefs")
    {
        ioIn >> m_clientAddrRefs;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameHostSaveData::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("serverName");
    ioOut << m_serverName;
    ioOut.TagSet("hostPlayersList");
    ioOut << m_hostPlayersList;
    ioOut.TagSet("nextPlayerNum");
    ioOut << m_nextPlayerNum;
    ioOut.TagSet("maxPlayersAllowed");
    ioOut << m_maxPlayersAllowed;
    ioOut.TagSet("jobList");
    ioOut << m_jobList;
    ioOut.TagSet("clientAddrRefs");
    ioOut << m_clientAddrRefs;
}
//%outOfLineFunctions } mLCRAEb0oFeu6OBqcvN2bg
