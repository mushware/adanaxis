//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameEvents.cpp
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
//%Header } tojhUq9YW9mReE8/PMiT0w
/*
 * $Id: MushGameEvents.cpp,v 1.1 2006/10/17 11:05:55 southa Exp $
 * $Log: MushGameEvents.cpp,v $
 * Revision 1.1  2006/10/17 11:05:55  southa
 * Expiry events
 *
 */

#include "MushGameEvents.h"

#include "MushGameIntern.h"

MUSHCORE_SINGLETON_INSTANCE(MushGameEvents);

using namespace Mushware;
using namespace std;

MushRubyValue
MushGameEvents::EventExpiryMake(void)
{
    MushRubyValue retVal( MushRubyUtil::ClassNewInstance(MushGameIntern::Sgl().MushEventExpiry()) );
    
    return retVal;
}
//%outOfLineFunctions {

const char *MushGameEvents::AutoName(void) const
{
    return "MushGameEvents";
}

MushcoreVirtualObject *MushGameEvents::AutoClone(void) const
{
    return new MushGameEvents(*this);
}

MushcoreVirtualObject *MushGameEvents::AutoCreate(void) const
{
    return new MushGameEvents;
}

MushcoreVirtualObject *MushGameEvents::AutoVirtualFactory(void)
{
    return new MushGameEvents;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameEvents", MushGameEvents::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameEvents::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushGameEvents::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushGameEvents::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } cdnbnKCheY/ZFXSPd87odg
