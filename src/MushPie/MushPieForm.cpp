//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieForm.cpp
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
//%Header } G0YyIoYBjjgiS8BGV8UsCA
/*
 * $Id: MushPieForm.cpp,v 1.8 2006/06/01 15:39:36 southa Exp $
 * $Log: MushPieForm.cpp,v $
 * Revision 1.8  2006/06/01 15:39:36  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.6  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.5  2005/06/16 17:25:39  southa
 * Client/server work
 *
 * Revision 1.4  2005/05/19 13:02:12  southa
 * Mac release work
 *
 * Revision 1.3  2005/02/10 12:34:12  southa
 * Template fixes
 *
 * Revision 1.2  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
 * Revision 1.1  2004/01/06 10:08:51  southa
 * MushcoreData and MushPieForm work
 *
 */

#include "MushPieForm.h"

#include "MushPieSignal.h"
#include "MushPieSTL.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MushPieForm::tData); // Data instance

void
MushPieForm::SignalHandle(const MushPieSignal& inSignal)
{
    ostringstream message;
    message << "Unhandled signal " << inSignal;
    throw MushcoreRequestFail(message.str());
}

void
MushPieForm::WriteableSignalHandle(MushPieSignal& inSignal)
{
    ostringstream message;
    message << "Unhandled signal " << inSignal;
    throw MushcoreRequestFail(message.str());
}

//%outOfLineFunctions {

const char *MushPieForm::AutoName(void) const
{
    return "MushPieForm";
}

MushcoreVirtualObject *MushPieForm::AutoClone(void) const
{
    return new MushPieForm(*this);
}

MushcoreVirtualObject *MushPieForm::AutoCreate(void) const
{
    return new MushPieForm;
}

MushcoreVirtualObject *MushPieForm::AutoVirtualFactory(void)
{
    return new MushPieForm;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushPieForm", MushPieForm::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushPieForm::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushPieForm::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushPieForm::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } g1wsfIKpSBNkWevX7X7gVA
