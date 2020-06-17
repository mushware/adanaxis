//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionListEntry.cpp
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
//%Header } cKwCE/EqIKWJARs504fQFA
/*
 * $Id: MushCollisionListEntry.cpp,v 1.2 2006/06/01 15:39:15 southa Exp $
 * $Log: MushCollisionListEntry.cpp,v $
 * Revision 1.2  2006/06/01 15:39:15  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/27 18:09:59  southa
 * Collision checking
 *
 */

#include "MushCollisionListEntry.h"

using namespace Mushware;
using namespace std;




//%outOfLineFunctions {

const char *MushCollisionListEntry::AutoName(void) const
{
    return "MushCollisionListEntry";
}

MushcoreVirtualObject *MushCollisionListEntry::AutoClone(void) const
{
    return new MushCollisionListEntry(*this);
}

MushcoreVirtualObject *MushCollisionListEntry::AutoCreate(void) const
{
    return new MushCollisionListEntry;
}

MushcoreVirtualObject *MushCollisionListEntry::AutoVirtualFactory(void)
{
    return new MushCollisionListEntry;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushCollisionListEntry", MushCollisionListEntry::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushCollisionListEntry::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushCollisionListEntry::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushCollisionListEntry::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } 32mjahm/s5hwm1EUGHDWRA
