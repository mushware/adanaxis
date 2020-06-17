//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameJob.cpp
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
//%Header } BfFNt84b5gOppJ8gTQ6lAg
/*
 * $Id: MushGameJob.cpp,v 1.7 2006/06/01 15:39:22 southa Exp $
 * $Log: MushGameJob.cpp,v $
 * Revision 1.7  2006/06/01 15:39:22  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.5  2005/06/23 17:25:25  southa
 * MushGame link work
 *
 * Revision 1.4  2005/06/23 13:56:58  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/22 20:01:58  southa
 * MushGame link work
 *
 * Revision 1.2  2005/06/21 15:57:47  southa
 * MushGame work
 *
 * Revision 1.1  2005/06/21 13:10:51  southa
 * MushGame work
 *
 */

#include "MushGameJob.h"

#include "MushGameSaveData.h"

MushGameJob::MushGameJob(const std::string& inID) :
    m_shouldWake(false),
    m_complete(false),
    m_wakeTime(0),
    m_id(inID)
{
}

void
MushGameJob::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    throw MushcoreDataFail(std::string("Unhandled message type ")+inMessage.AutoName()+" in "+AutoName());
}

//%outOfLineFunctions {

const char *MushGameJob::AutoName(void) const
{
    return "MushGameJob";
}

MushcoreVirtualObject *MushGameJob::AutoClone(void) const
{
    return new MushGameJob(*this);
}

MushcoreVirtualObject *MushGameJob::AutoCreate(void) const
{
    return new MushGameJob;
}

MushcoreVirtualObject *MushGameJob::AutoVirtualFactory(void)
{
    return new MushGameJob;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameJob", MushGameJob::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameJob::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "shouldWake=" << m_shouldWake << ", ";
    ioOut << "complete=" << m_complete << ", ";
    ioOut << "wakeTime=" << m_wakeTime << ", ";
    ioOut << "id=" << m_id;
    ioOut << "]";
}
bool
MushGameJob::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "shouldWake")
    {
        ioIn >> m_shouldWake;
    }
    else if (inTagStr == "complete")
    {
        ioIn >> m_complete;
    }
    else if (inTagStr == "wakeTime")
    {
        ioIn >> m_wakeTime;
    }
    else if (inTagStr == "id")
    {
        ioIn >> m_id;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameJob::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("shouldWake");
    ioOut << m_shouldWake;
    ioOut.TagSet("complete");
    ioOut << m_complete;
    ioOut.TagSet("wakeTime");
    ioOut << m_wakeTime;
    ioOut.TagSet("id");
    ioOut << m_id;
}
//%outOfLineFunctions } d8SCAKb4/EEakq925tuONQ
