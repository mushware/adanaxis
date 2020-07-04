//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLCamera.cpp
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
//%Header } BotGZi+zI7lyZ1vzoZk3KQ
/*
 * $Id: MushGLCamera.cpp,v 1.1 2006/07/24 18:46:48 southa Exp $
 * $Log: MushGLCamera.cpp,v $
 * Revision 1.1  2006/07/24 18:46:48  southa
 * Depth sorting
 *
 */

#include "MushGLCamera.h"

MushGLCamera::~MushGLCamera()
{
}
//%outOfLineFunctions {

const char *MushGLCamera::AutoName(void) const
{
    return "MushGLCamera";
}

MushcoreVirtualObject *MushGLCamera::AutoClone(void) const
{
    return new MushGLCamera(*this);
}

MushcoreVirtualObject *MushGLCamera::AutoCreate(void) const
{
    return new MushGLCamera;
}

MushcoreVirtualObject *MushGLCamera::AutoVirtualFactory(void)
{
    return new MushGLCamera;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLCamera", MushGLCamera::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLCamera::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "post=" << m_post << ", ";
    ioOut << "projection=" << m_projection;
    ioOut << "]";
}
bool
MushGLCamera::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "post")
    {
        ioIn >> m_post;
    }
    else if (inTagStr == "projection")
    {
        ioIn >> m_projection;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLCamera::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("post");
    ioOut << m_post;
    ioOut.TagSet("projection");
    ioOut << m_projection;
}
//%outOfLineFunctions } Tl3Bd5czjEMqcliSZkP7SA
