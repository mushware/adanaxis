//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameRender.cpp
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
//%Header } YQC/4RdLp822TGbwb26/MA
/*
 * $Id: MushGameRender.cpp,v 1.5 2007/02/08 17:55:15 southa Exp $
 * $Log: MushGameRender.cpp,v $
 * Revision 1.5  2007/02/08 17:55:15  southa
 * Common routines in space generation
 *
 * Revision 1.4  2006/07/20 12:22:22  southa
 * Precache display
 *
 * Revision 1.3  2006/06/01 15:39:26  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.1  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 */

#include "MushGameRender.h"

MUSHCORE_DATA_INSTANCE(MushGameRender);

void
MushGameRender::PrecacheRender(MushGameLogic& ioLogic, const MushGameCamera& inCamera)
{
    // No operation
}

void
MushGameRender::FrameRender(MushGameLogic& ioLogic, const MushGameCamera& inCamera)
{
    // No operation
}

//%outOfLineFunctions {

const char *MushGameRender::AutoName(void) const
{
    return "MushGameRender";
}

MushcoreVirtualObject *MushGameRender::AutoClone(void) const
{
    return new MushGameRender(*this);
}

MushcoreVirtualObject *MushGameRender::AutoCreate(void) const
{
    return new MushGameRender;
}

MushcoreVirtualObject *MushGameRender::AutoVirtualFactory(void)
{
    return new MushGameRender;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameRender", MushGameRender::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameRender::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "groupingName=" << m_groupingName;
    ioOut << "]";
}
bool
MushGameRender::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "groupingName")
    {
        ioIn >> m_groupingName;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameRender::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("groupingName");
    ioOut << m_groupingName;
}
//%outOfLineFunctions } S4xWtMTmFOzf3j9ZFnCXDw
