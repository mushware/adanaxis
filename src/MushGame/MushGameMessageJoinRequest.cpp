//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageJoinRequest.cpp
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
//%Header } NHp27xyU2gS7VPpALJb2Iw
/*
 *  MushGameMessageJoinRequest.cpp
 *  project
 *
 *  Created by Andy Southgate on 20/06/2005.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include "MushGameMessageJoinRequest.h"

//%outOfLineFunctions {

const char *MushGameMessageJoinRequest::AutoName(void) const
{
    return "MushGameMessageJoinRequest";
}

MushcoreVirtualObject *MushGameMessageJoinRequest::AutoClone(void) const
{
    return new MushGameMessageJoinRequest(*this);
}

MushcoreVirtualObject *MushGameMessageJoinRequest::AutoCreate(void) const
{
    return new MushGameMessageJoinRequest;
}

MushcoreVirtualObject *MushGameMessageJoinRequest::AutoVirtualFactory(void)
{
    return new MushGameMessageJoinRequest;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMessageJoinRequest", MushGameMessageJoinRequest::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMessageJoinRequest::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameMessage::AutoPrint(ioOut);
    ioOut << "clientName=" << m_clientName << ", ";
    ioOut << "playerName=" << m_playerName << ", ";
    ioOut << "packageID=" << m_packageID;
    ioOut << "]";
}
bool
MushGameMessageJoinRequest::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
    else if (inTagStr == "playerName")
    {
        ioIn >> m_playerName;
    }
    else if (inTagStr == "packageID")
    {
        ioIn >> m_packageID;
    }
    else if (MushGameMessage::AutoXMLDataProcess(ioIn, inTagStr))
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
MushGameMessageJoinRequest::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameMessage::AutoXMLPrint(ioOut);
    ioOut.TagSet("clientName");
    ioOut << m_clientName;
    ioOut.TagSet("playerName");
    ioOut << m_playerName;
    ioOut.TagSet("packageID");
    ioOut << m_packageID;
}
//%outOfLineFunctions } zur/wek2UdmVisJBbJLGtQ
