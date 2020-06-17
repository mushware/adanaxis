//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameSaveData.cpp
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
//%Header } J/OfDhpelc/HdTyQ1DIB9g
/*
 * $Id: MushGameSaveData.cpp,v 1.15 2006/10/17 15:28:03 southa Exp $
 * $Log: MushGameSaveData.cpp,v $
 * Revision 1.15  2006/10/17 15:28:03  southa
 * Player collisions
 *
 * Revision 1.14  2006/07/31 11:01:38  southa
 * Music and dialogues
 *
 * Revision 1.13  2006/06/01 15:39:27  southa
 * DrawArray verification and fixes
 *
 * Revision 1.12  2005/07/29 14:59:49  southa
 * Maptor access
 *
 * Revision 1.11  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 * Revision 1.10  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.9  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 * Revision 1.8  2005/06/24 10:30:13  southa
 * MushGame camera work
 *
 * Revision 1.7  2005/06/23 17:25:25  southa
 * MushGame link work
 *
 * Revision 1.6  2005/06/23 13:56:58  southa
 * MushGame link work
 *
 * Revision 1.5  2005/06/22 20:01:59  southa
 * MushGame link work
 *
 * Revision 1.4  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.3  2005/06/21 13:10:52  southa
 * MushGame work
 *
 * Revision 1.2  2005/06/20 14:30:36  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 17:25:39  southa
 * Client/server work
 *
 */

#include "MushGameSaveData.h"

MUSHCORE_DATA_INSTANCE(MushGameSaveData);

MushGameSaveData::MushGameSaveData()
{
}

//%outOfLineFunctions {

const char *MushGameSaveData::AutoName(void) const
{
    return "MushGameSaveData";
}

MushcoreVirtualObject *MushGameSaveData::AutoClone(void) const
{
    throw MushcoreRequestFail("Cannot clone 'MushGameSaveData'");;
}

MushcoreVirtualObject *MushGameSaveData::AutoCreate(void) const
{
    return new MushGameSaveData;
}

MushcoreVirtualObject *MushGameSaveData::AutoVirtualFactory(void)
{
    return new MushGameSaveData;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameSaveData", MushGameSaveData::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameSaveData::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "clientName=" << m_clientName << ", ";
    ioOut << "playersList=" << m_playersList << ", ";
    ioOut << "jobList=" << m_jobList << ", ";
    ioOut << "cameras=" << m_cameras << ", ";
    ioOut << "toServerMailbox=" << m_toServerMailbox << ", ";
    ioOut << "clientRef=" << m_clientRef << ", ";
    ioOut << "serverAddrRef=" << m_serverAddrRef << ", ";
    ioOut << "renderRef=" << m_renderRef << ", ";
    ioOut << "controlMailboxName=" << m_controlMailboxName << ", ";
    ioOut << "dialogues=" << m_dialogues;
    ioOut << "]";
}
bool
MushGameSaveData::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "clientName")
    {
        ioIn >> m_clientName;
    }
    else if (inTagStr == "playersList")
    {
        ioIn >> m_playersList;
    }
    else if (inTagStr == "jobList")
    {
        ioIn >> m_jobList;
    }
    else if (inTagStr == "cameras")
    {
        ioIn >> m_cameras;
    }
    else if (inTagStr == "toServerMailbox")
    {
        ioIn >> m_toServerMailbox;
    }
    else if (inTagStr == "clientRef")
    {
        ioIn >> m_clientRef;
    }
    else if (inTagStr == "serverAddrRef")
    {
        ioIn >> m_serverAddrRef;
    }
    else if (inTagStr == "renderRef")
    {
        ioIn >> m_renderRef;
    }
    else if (inTagStr == "controlMailboxName")
    {
        ioIn >> m_controlMailboxName;
    }
    else if (inTagStr == "dialogues")
    {
        ioIn >> m_dialogues;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameSaveData::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("clientName");
    ioOut << m_clientName;
    ioOut.TagSet("playersList");
    ioOut << m_playersList;
    ioOut.TagSet("jobList");
    ioOut << m_jobList;
    ioOut.TagSet("cameras");
    ioOut << m_cameras;
    ioOut.TagSet("toServerMailbox");
    ioOut << m_toServerMailbox;
    ioOut.TagSet("clientRef");
    ioOut << m_clientRef;
    ioOut.TagSet("serverAddrRef");
    ioOut << m_serverAddrRef;
    ioOut.TagSet("renderRef");
    ioOut << m_renderRef;
    ioOut.TagSet("controlMailboxName");
    ioOut << m_controlMailboxName;
    ioOut.TagSet("dialogues");
    ioOut << m_dialogues;
}
//%outOfLineFunctions } gvgx3m7fGl1so9nTpvv9LA
