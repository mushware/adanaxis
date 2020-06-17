//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisData.cpp
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
//%Header } SRMEOGygB75rxakZU18VsQ
/*
 * $Id: AdanaxisData.cpp,v 1.6 2007/04/18 09:22:00 southa Exp $
 * $Log: AdanaxisData.cpp,v $
 * Revision 1.6  2007/04/18 09:22:00  southa
 * Header and level fixes
 *
 * Revision 1.5  2007/04/16 08:41:07  southa
 * Level and header mods
 *
 * Revision 1.4  2007/03/16 19:50:44  southa
 * Damage indicators
 *
 * Revision 1.3  2006/08/01 17:21:23  southa
 * River demo
 *
 * Revision 1.2  2006/06/01 15:38:47  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/08/01 13:09:57  southa
 * Collision messaging
 *
 */

#include "AdanaxisData.h"

AdanaxisData::AdanaxisData(const std::string& inName) :
    MushGameData(inName)
{
}
//%outOfLineFunctions {

const char *AdanaxisData::AutoName(void) const
{
    return "AdanaxisData";
}

MushcoreVirtualObject *AdanaxisData::AutoClone(void) const
{
    return new AdanaxisData(*this);
}

MushcoreVirtualObject *AdanaxisData::AutoCreate(void) const
{
    return new AdanaxisData;
}

MushcoreVirtualObject *AdanaxisData::AutoVirtualFactory(void)
{
    return new AdanaxisData;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisData", AdanaxisData::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisData::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameData::AutoPrint(ioOut);
    ioOut << "]";
}
bool
AdanaxisData::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MushGameData::AutoXMLDataProcess(ioIn, inTagStr))
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
AdanaxisData::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameData::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } 03vLNy6OhwIL6GKqF4s06w
