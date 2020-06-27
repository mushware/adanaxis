//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaJob.cpp
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
//%Header } KYH4vf1lDdLTt3w0l3X3dQ

#include "MediaJob.h"


MediaJob::MediaJob(std::string& name) :
    m_name(name)
{}


MediaJob::~MediaJob()
{}

void MediaJob::Run()
{
    MushcoreLog::Sgl().ErrorLog() << "Run method for job " << m_name << " not overriden" << std::endl;
}

//%outOfLineFunctions {

const char *MediaJob::AutoName(void) const
{
    return "MediaJob";
}

MushcoreVirtualObject *MediaJob::AutoClone(void) const
{
    return new MediaJob(*this);
}

MushcoreVirtualObject *MediaJob::AutoCreate(void) const
{
    return new MediaJob;
}

MushcoreVirtualObject *MediaJob::AutoVirtualFactory(void)
{
    return new MediaJob;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MediaJob", MediaJob::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MediaJob::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "name=" << m_name << ", ";
    ioOut << "error=" << m_error;
    ioOut << "]";
}
bool
MediaJob::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "name")
    {
        ioIn >> m_name;
    }
    else if (inTagStr == "error")
    {
        ioIn >> m_error;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MediaJob::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("name");
    ioOut << m_name;
    ioOut.TagSet("error");
    ioOut << m_error;
}
//%outOfLineFunctions } 4Jbdq4q1EaEHL3bDD7te5w
