//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameKeyDef.cpp
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
//%Header } AAFPoKj92NajwgMlDDmlgg
/*
 * $Id: MushGameKeyDef.cpp,v 1.4 2006/11/02 12:23:22 southa Exp $
 * $Log: MushGameKeyDef.cpp,v $
 * Revision 1.4  2006/11/02 12:23:22  southa
 * Weapon selection
 *
 * Revision 1.3  2006/07/12 11:22:42  southa
 * Advanced control menu
 *
 * Revision 1.2  2006/06/01 15:39:22  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/11 16:37:46  southa
 * Uplink control work
 *
 */

#include "MushGameKeyDef.h"

MushGameKeyDef::MushGameKeyDef() :
    m_state(false),
    m_stateHasChanged(true)
{
}

Mushware::S32
MushGameKeyDef::KeyValue(Mushware::U32 inIndex) const
{
    MushcoreUtil::DebugBoundsCheck(inIndex, m_keyValues.size());
    return m_keyValues[inIndex];
}

void
MushGameKeyDef::KeyValueSet(Mushware::S32 inValue, Mushware::U32 inIndex)
{
    MushcoreUtil::DebugBoundsCheck(inIndex, m_keyValues.size());
    m_keyValues[inIndex] = inValue;
}

void
MushGameKeyDef::Reset(void)
{
    m_state = false;
    m_stateHasChanged = true;
}

//%outOfLineFunctions {

const char *MushGameKeyDef::AutoName(void) const
{
    return "MushGameKeyDef";
}

MushcoreVirtualObject *MushGameKeyDef::AutoClone(void) const
{
    return new MushGameKeyDef(*this);
}

MushcoreVirtualObject *MushGameKeyDef::AutoCreate(void) const
{
    return new MushGameKeyDef;
}

MushcoreVirtualObject *MushGameKeyDef::AutoVirtualFactory(void)
{
    return new MushGameKeyDef;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameKeyDef", MushGameKeyDef::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameKeyDef::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "keyValues=" << m_keyValues << ", ";
    ioOut << "state=" << m_state << ", ";
    ioOut << "stateHasChanged=" << m_stateHasChanged << ", ";
    ioOut << "keyName=" << m_keyName;
    ioOut << "]";
}
bool
MushGameKeyDef::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "keyValues")
    {
        ioIn >> m_keyValues;
    }
    else if (inTagStr == "state")
    {
        ioIn >> m_state;
    }
    else if (inTagStr == "stateHasChanged")
    {
        ioIn >> m_stateHasChanged;
    }
    else if (inTagStr == "keyName")
    {
        ioIn >> m_keyName;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameKeyDef::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("keyValues");
    ioOut << m_keyValues;
    ioOut.TagSet("state");
    ioOut << m_state;
    ioOut.TagSet("stateHasChanged");
    ioOut << m_stateHasChanged;
    ioOut.TagSet("keyName");
    ioOut << m_keyName;
}
//%outOfLineFunctions } RwRFuqCxsZeyR1KSmwjwfw
