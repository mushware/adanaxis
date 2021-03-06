//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageJoinDenied.cpp
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
//%Header } AjHft/0G8EQQiR11o6mvZg
/*
 * $Id: MushGameMessageJoinDenied.cpp,v 1.3 2006/06/01 15:39:24 southa Exp $
 * $Log: MushGameMessageJoinDenied.cpp,v $
 * Revision 1.3  2006/06/01 15:39:24  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.1  2005/06/20 14:30:36  southa
 * Adanaxis work
 *
 */

#include "MushGameMessageJoinDenied.h"

//%outOfLineFunctions {

const char *MushGameMessageJoinDenied::AutoName(void) const
{
    return "MushGameMessageJoinDenied";
}

MushcoreVirtualObject *MushGameMessageJoinDenied::AutoClone(void) const
{
    return new MushGameMessageJoinDenied(*this);
}

MushcoreVirtualObject *MushGameMessageJoinDenied::AutoCreate(void) const
{
    return new MushGameMessageJoinDenied;
}

MushcoreVirtualObject *MushGameMessageJoinDenied::AutoVirtualFactory(void)
{
    return new MushGameMessageJoinDenied;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMessageJoinDenied", MushGameMessageJoinDenied::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMessageJoinDenied::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameMessage::AutoPrint(ioOut);
    ioOut << "]";
}
bool
MushGameMessageJoinDenied::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
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
MushGameMessageJoinDenied::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameMessage::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } bPOzu0v61cZnsis9PgYiMw
