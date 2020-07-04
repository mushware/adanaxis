//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLControl.cpp
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
//%Header } Ny67KJ3krq3tAtuTD0dzLA
/*
 * $Id: MushGLControl.cpp,v 1.5 2006/06/01 15:39:17 southa Exp $
 * $Log: MushGLControl.cpp,v $
 * Revision 1.5  2006/06/01 15:39:17  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.3  2005/06/20 14:30:35  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/16 17:25:39  southa
 * Client/server work
 *
 * Revision 1.1  2005/06/13 17:35:37  southa
 * Adanaxis creation
 *
 */

#include "MushGLControl.h"

#include "mushMushcoreIO.h"


//%outOfLineFunctions {

const char *MushGLControl::AutoName(void) const
{
    return "MushGLControl";
}

MushcoreVirtualObject *MushGLControl::AutoClone(void) const
{
    return new MushGLControl(*this);
}

MushcoreVirtualObject *MushGLControl::AutoCreate(void) const
{
    return new MushGLControl;
}

MushcoreVirtualObject *MushGLControl::AutoVirtualFactory(void)
{
    return new MushGLControl;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLControl", MushGLControl::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLControl::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "timestamp=" << m_timestamp << ", ";
    ioOut << "keys=" << m_keys << ", ";
    ioOut << "axes=" << m_axes;
    ioOut << "]";
}
bool
MushGLControl::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "timestamp")
    {
        ioIn >> m_timestamp;
    }
    else if (inTagStr == "keys")
    {
        ioIn >> m_keys;
    }
    else if (inTagStr == "axes")
    {
        ioIn >> m_axes;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLControl::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("timestamp");
    ioOut << m_timestamp;
    ioOut.TagSet("keys");
    ioOut << m_keys;
    ioOut.TagSet("axes");
    ioOut << m_axes;
}
//%outOfLineFunctions } Ldo4MEjmsEEXQ6mtx/v8Dg
