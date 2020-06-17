//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioSDLChannelDef.cpp
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
//%Header } BhYy7hH6ahHmGh6X7Vx0Ow
/*
 * $Id: MediaAudioSDLChannelDef.cpp,v 1.1 2006/12/11 13:28:23 southa Exp $
 * $Log: MediaAudioSDLChannelDef.cpp,v $
 * Revision 1.1  2006/12/11 13:28:23  southa
 * Snapshot
 *
 */

#include "MediaAudioSDLChannelDef.h"

MediaAudioSDLChannelDef::MediaAudioSDLChannelDef() :
    MediaAudioChannelDef(),
    m_pActiveSample(NULL)
{
    
}
//%outOfLineFunctions {

const char *MediaAudioSDLChannelDef::AutoName(void) const
{
    return "MediaAudioSDLChannelDef";
}

MushcoreVirtualObject *MediaAudioSDLChannelDef::AutoClone(void) const
{
    return new MediaAudioSDLChannelDef(*this);
}

MushcoreVirtualObject *MediaAudioSDLChannelDef::AutoCreate(void) const
{
    return new MediaAudioSDLChannelDef;
}

MushcoreVirtualObject *MediaAudioSDLChannelDef::AutoVirtualFactory(void)
{
    return new MediaAudioSDLChannelDef;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MediaAudioSDLChannelDef", MediaAudioSDLChannelDef::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MediaAudioSDLChannelDef::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MediaAudioChannelDef::AutoPrint(ioOut);
    ioOut << "]";
}
bool
MediaAudioSDLChannelDef::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MediaAudioChannelDef::AutoXMLDataProcess(ioIn, inTagStr))
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
MediaAudioSDLChannelDef::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MediaAudioChannelDef::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } BvG1dqCw2MCjARW2B6LiPw
