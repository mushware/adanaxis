//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisClient.cpp
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
//%Header } Z6pzDf9i5WZHR66aSCo4HQ
/*
 * $Id: AdanaxisClient.cpp,v 1.6 2007/04/18 09:21:59 southa Exp $
 * $Log: AdanaxisClient.cpp,v $
 * Revision 1.6  2007/04/18 09:21:59  southa
 * Header and level fixes
 *
 * Revision 1.5  2006/08/01 17:21:22  southa
 * River demo
 *
 * Revision 1.4  2006/06/01 15:38:46  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/02 00:42:36  southa
 * Conditioning tweaks
 *
 * Revision 1.2  2005/06/20 14:30:33  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 10:49:57  southa
 * Client/server work
 *
 */

#include "AdanaxisClient.h"

//%outOfLineFunctions {

const char *AdanaxisClient::AutoName(void) const
{
    return "AdanaxisClient";
}

MushcoreVirtualObject *AdanaxisClient::AutoClone(void) const
{
    return new AdanaxisClient(*this);
}

MushcoreVirtualObject *AdanaxisClient::AutoCreate(void) const
{
    return new AdanaxisClient;
}

MushcoreVirtualObject *AdanaxisClient::AutoVirtualFactory(void)
{
    return new AdanaxisClient;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisClient", AdanaxisClient::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisClient::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameClient::AutoPrint(ioOut);
    ioOut << "]";
}
bool
AdanaxisClient::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MushGameClient::AutoXMLDataProcess(ioIn, inTagStr))
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
AdanaxisClient::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameClient::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } MKiksVc34iPApeuBpWYHVQ
