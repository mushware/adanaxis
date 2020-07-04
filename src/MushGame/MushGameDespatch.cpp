//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameDespatch.cpp
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
//%Header } SQsWkCHZwHB6toKO3l6O5Q
/*
 * $Id: MushGameDespatch.cpp,v 1.3 2006/06/01 15:39:21 southa Exp $
 * $Log: MushGameDespatch.cpp,v $
 * Revision 1.3  2006/06/01 15:39:21  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.1  2005/06/20 16:14:30  southa
 * Adanaxis work
 *
 */

#include "MushGameDespatch.h"

//%outOfLineFunctions {

const char *MushGameDespatch::AutoName(void) const
{
    return "MushGameDespatch";
}

MushcoreVirtualObject *MushGameDespatch::AutoClone(void) const
{
    return new MushGameDespatch(*this);
}

MushcoreVirtualObject *MushGameDespatch::AutoCreate(void) const
{
    return new MushGameDespatch;
}

MushcoreVirtualObject *MushGameDespatch::AutoVirtualFactory(void)
{
    return new MushGameDespatch;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameDespatch", MushGameDespatch::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameDespatch::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushGameDespatch::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameDespatch::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } kfbxuxA1GBQa6vMsU9Ds6w
