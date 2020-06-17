//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePiece.cpp
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
//%Header } 64wJzahYDI4kxxMjCK1bcA
/*
 * $Id: MushPiePiece.cpp,v 1.14 2006/06/01 15:39:36 southa Exp $
 * $Log: MushPiePiece.cpp,v $
 * Revision 1.14  2006/06/01 15:39:36  southa
 * DrawArray verification and fixes
 *
 * Revision 1.13  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.12  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.11  2005/06/16 17:25:39  southa
 * Client/server work
 *
 * Revision 1.10  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.9  2005/02/10 12:34:13  southa
 * Template fixes
 *
 * Revision 1.8  2004/09/27 22:42:09  southa
 * MSVC compilation fixes
 *
 * Revision 1.7  2004/01/06 10:08:51  southa
 * MushcoreData and MushPieForm work
 *
 * Revision 1.6  2004/01/06 00:34:56  southa
 * MushPie testing
 *
 * Revision 1.5  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 * Revision 1.4  2004/01/04 14:36:37  southa
 * Handle 'inline' in source conditioner
 *
 * Revision 1.3  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 * Revision 1.2  2004/01/02 17:31:48  southa
 * MushPie work and XML fixes
 *
 * Revision 1.1  2004/01/02 11:57:47  southa
 * Created
 *
 */

#include "MushPiePiece.h"

using namespace Mushware;

void
operator>>(MushcoreXMLIStream& ioIn, MushPiePiece::tSleepState& outObj)
{
    U32 value;
    ioIn >> value;
    outObj = static_cast<MushPiePiece::tSleepState>(value);
}

//%outOfLineFunctions {

const char *MushPiePiece::AutoName(void) const
{
    return "MushPiePiece";
}

MushcoreVirtualObject *MushPiePiece::AutoClone(void) const
{
    return new MushPiePiece(*this);
}

MushcoreVirtualObject *MushPiePiece::AutoCreate(void) const
{
    return new MushPiePiece;
}

MushcoreVirtualObject *MushPiePiece::AutoVirtualFactory(void)
{
    return new MushPiePiece;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushPiePiece", MushPiePiece::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
bool
MushPiePiece::AutoEquals(const MushPiePiece& inObj) const
{
    return 1
        && (m_sleepState == inObj.m_sleepState)
        && (m_formRef == inObj.m_formRef)
    ;
}
void
MushPiePiece::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "sleepState=" << m_sleepState << ", ";
    ioOut << "formRef=" << m_formRef;
    ioOut << "]";
}
bool
MushPiePiece::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "sleepState")
    {
        ioIn >> m_sleepState;
    }
    else if (inTagStr == "formRef")
    {
        ioIn >> m_formRef;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushPiePiece::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("sleepState");
    ioOut << m_sleepState;
    ioOut.TagSet("formRef");
    ioOut << m_formRef;
}
//%outOfLineFunctions } hZq8x7Ci/G3KAyC1Z5rB/Q
