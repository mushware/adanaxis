//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionList.cpp
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
//%Header } IJqYc4iS5L+0JOXTFZozCg
/*
 * $Id: MushCollisionList.cpp,v 1.2 2006/06/01 15:39:15 southa Exp $
 * $Log: MushCollisionList.cpp,v $
 * Revision 1.2  2006/06/01 15:39:15  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/27 18:09:59  southa
 * Collision checking
 *
 */

#include "MushCollisionList.h"

using namespace Mushware;
using namespace std;

//%outOfLineFunctions {

const char *MushCollisionList::AutoName(void) const
{
    return "MushCollisionList";
}

MushcoreVirtualObject *MushCollisionList::AutoClone(void) const
{
    return new MushCollisionList(*this);
}

MushcoreVirtualObject *MushCollisionList::AutoCreate(void) const
{
    return new MushCollisionList;
}

MushcoreVirtualObject *MushCollisionList::AutoVirtualFactory(void)
{
    return new MushCollisionList;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushCollisionList", MushCollisionList::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushCollisionList::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "list=" << m_list;
    ioOut << "]";
}
bool
MushCollisionList::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "list")
    {
        ioIn >> m_list;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushCollisionList::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("list");
    ioOut << m_list;
}
//%outOfLineFunctions } kpG6fz4MD7vUeDKuOM3xLQ
