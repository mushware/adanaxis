//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameData.cpp
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
//%Header } k1EW++6eYkDpYVjWIHOFHw
/*
 * $Id: MushGameData.cpp,v 1.4 2007/03/08 11:00:29 southa Exp $
 * $Log: MushGameData.cpp,v $
 * Revision 1.4  2007/03/08 11:00:29  southa
 * Level epilogue
 *
 * Revision 1.3  2006/06/01 15:39:21  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.1  2005/06/21 13:10:51  southa
 * MushGame work
 *
 */

#include "MushGameData.h"

MUSHCORE_DATA_INSTANCE(MushGameData);

MushGameData::MushGameData(const std::string& inName) :
    m_saveDataRef(inName),
    m_volatileDataRef(inName)
{
}

void
MushGameData::GroupingNameSet(const std::string& inName)
{
    m_saveDataRef.NameSet(inName);
    m_volatileDataRef.NameSet(inName);
}

//%outOfLineFunctions {

const char *MushGameData::AutoName(void) const
{
    return "MushGameData";
}

MushcoreVirtualObject *MushGameData::AutoClone(void) const
{
    return new MushGameData(*this);
}

MushcoreVirtualObject *MushGameData::AutoCreate(void) const
{
    return new MushGameData;
}

MushcoreVirtualObject *MushGameData::AutoVirtualFactory(void)
{
    return new MushGameData;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameData", MushGameData::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameData::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "saveDataRef=" << m_saveDataRef << ", ";
    ioOut << "volatileDataRef=" << m_volatileDataRef;
    ioOut << "]";
}
bool
MushGameData::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "saveDataRef")
    {
        ioIn >> m_saveDataRef;
    }
    else if (inTagStr == "volatileDataRef")
    {
        ioIn >> m_volatileDataRef;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameData::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("saveDataRef");
    ioOut << m_saveDataRef;
    ioOut.TagSet("volatileDataRef");
    ioOut << m_volatileDataRef;
}
//%outOfLineFunctions } Cj5ZxkDEZH6fAvfD7hFszA
