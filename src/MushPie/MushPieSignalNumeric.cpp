//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieSignalNumeric.cpp
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
//%Header } s+fcS2zSfg4LCbCGdyPeTw
/*
 * $Id: MushPieSignalNumeric.cpp,v 1.7 2006/06/01 15:39:37 southa Exp $
 * $Log: MushPieSignalNumeric.cpp,v $
 * Revision 1.7  2006/06/01 15:39:37  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.5  2005/06/20 14:30:38  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/06/16 17:25:40  southa
 * Client/server work
 *
 * Revision 1.3  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.2  2005/02/10 12:34:16  southa
 * Template fixes
 *
 * Revision 1.1  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
 */

#include "MushPieSignalNumeric.h"

//%outOfLineFunctions {

const char *MushPieSignalNumeric::AutoName(void) const
{
    return "MushPieSignalNumeric";
}

MushcoreVirtualObject *MushPieSignalNumeric::AutoClone(void) const
{
    return new MushPieSignalNumeric(*this);
}

MushcoreVirtualObject *MushPieSignalNumeric::AutoCreate(void) const
{
    return new MushPieSignalNumeric;
}

MushcoreVirtualObject *MushPieSignalNumeric::AutoVirtualFactory(void)
{
    return new MushPieSignalNumeric;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushPieSignalNumeric", MushPieSignalNumeric::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushPieSignalNumeric::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "eventNumber=" << m_eventNumber;
    ioOut << "]";
}
bool
MushPieSignalNumeric::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "eventNumber")
    {
        ioIn >> m_eventNumber;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushPieSignalNumeric::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("eventNumber");
    ioOut << m_eventNumber;
}
//%outOfLineFunctions } mn7fRCOCQ024A/DkMGBwRQ
