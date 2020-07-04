//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameLogicLocal.cpp
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
//%Header } uFNeJf5RitxFyyYsI+2cJg
/*
 * $Id: MushGameLogicLocal.cpp,v 1.10 2006/10/17 15:28:02 southa Exp $
 * $Log: MushGameLogicLocal.cpp,v $
 * Revision 1.10  2006/10/17 15:28:02  southa
 * Player collisions
 *
 * Revision 1.9  2006/10/02 17:25:05  southa
 * Object lookup and target selection
 *
 * Revision 1.8  2006/06/01 15:39:23  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.6  2005/06/30 16:29:25  southa
 * Adanaxis work
 *
 * Revision 1.5  2005/06/23 17:25:25  southa
 * MushGame link work
 *
 * Revision 1.4  2005/06/23 13:56:58  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/22 20:01:59  southa
 * MushGame link work
 *
 * Revision 1.2  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.1  2005/06/21 13:10:51  southa
 * MushGame work
 *
 */

#include "MushGameLogicLocal.h"

#include "MushGameJobPlayerCreate.h"
#include "MushGameUtil.h"

MushGameLogicLocal::MushGameLogicLocal()
{
}

void
MushGameLogicLocal::SinglePlayerCheck(void)
{
    if (SaveData().PlayersList().size() < 1)
    {
        std::string jobName = "localplayercreate";
        if (!SaveData().JobList().Exists(jobName))
        {
            MushGameJobPlayerCreate *pCreate = new MushGameJobPlayerCreate("j:"+jobName);
            SaveData().JobListWRef().Give(jobName, pCreate);
        }
    }
}

void
MushGameLogicLocal::PerFrameProcessing(void)
{
    SinglePlayerCheck();
    MushGameLogic::PerFrameProcessing();
}

void
MushGameLogicLocal::JobMessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    throw MushcoreDataFail(std::string("Discarding message of type '")+inMessage.AutoName()+"' with Job ID");
}

//%outOfLineFunctions {

const char *MushGameLogicLocal::AutoName(void) const
{
    return "MushGameLogicLocal";
}

MushcoreVirtualObject *MushGameLogicLocal::AutoClone(void) const
{
    return new MushGameLogicLocal(*this);
}

MushcoreVirtualObject *MushGameLogicLocal::AutoCreate(void) const
{
    return new MushGameLogicLocal;
}

MushcoreVirtualObject *MushGameLogicLocal::AutoVirtualFactory(void)
{
    return new MushGameLogicLocal;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameLogicLocal", MushGameLogicLocal::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameLogicLocal::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameLogic::AutoPrint(ioOut);
    ioOut << "]";
}
bool
MushGameLogicLocal::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MushGameLogic::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameLogicLocal::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameLogic::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } 96dDf3dow9nkQEE6n/tInA
