//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageJoinConfirm.cpp
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
//%Header } zHE0vDKmKQ3PRcp9DmN12A
/*
 *  MushGameMessageJoinConfirm.cpp
 *  project
 *
 *  Created by Andy Southgate on 20/06/2005.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include "MushGameMessageJoinConfirm.h"

//%outOfLineFunctions {

const char *MushGameMessageJoinConfirm::AutoName(void) const
{
    return "MushGameMessageJoinConfirm";
}

MushcoreVirtualObject *MushGameMessageJoinConfirm::AutoClone(void) const
{
    return new MushGameMessageJoinConfirm(*this);
}

MushcoreVirtualObject *MushGameMessageJoinConfirm::AutoCreate(void) const
{
    return new MushGameMessageJoinConfirm;
}

MushcoreVirtualObject *MushGameMessageJoinConfirm::AutoVirtualFactory(void)
{
    return new MushGameMessageJoinConfirm;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMessageJoinConfirm", MushGameMessageJoinConfirm::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMessageJoinConfirm::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameMessage::AutoPrint(ioOut);
    ioOut << "newPlayerID=" << m_newPlayerID << ", ";
    ioOut << "hostName=" << m_hostName << ", ";
    ioOut << "playerName=" << m_playerName << ", ";
    ioOut << "hostPackageID=" << m_hostPackageID;
    ioOut << "]";
}
bool
MushGameMessageJoinConfirm::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "newPlayerID")
    {
        ioIn >> m_newPlayerID;
    }
    else if (inTagStr == "hostName")
    {
        ioIn >> m_hostName;
    }
    else if (inTagStr == "playerName")
    {
        ioIn >> m_playerName;
    }
    else if (inTagStr == "hostPackageID")
    {
        ioIn >> m_hostPackageID;
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
MushGameMessageJoinConfirm::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameMessage::AutoXMLPrint(ioOut);
    ioOut.TagSet("newPlayerID");
    ioOut << m_newPlayerID;
    ioOut.TagSet("hostName");
    ioOut << m_hostName;
    ioOut.TagSet("playerName");
    ioOut << m_playerName;
    ioOut.TagSet("hostPackageID");
    ioOut << m_hostPackageID;
}
//%outOfLineFunctions } MWdtyx2FRae+oGz4cO5JBg
