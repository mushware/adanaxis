//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreVirtualObject.cpp
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
//%Header } 8wMwhy7cpVENZ38UgX26Uw
/*
 * $Id: MushcoreVirtualObject.cpp,v 1.7 2006/06/01 15:39:48 southa Exp $
 * $Log: MushcoreVirtualObject.cpp,v $
 * Revision 1.7  2006/06/01 15:39:48  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/06/14 13:25:34  southa
 * Adanaxis work
 *
 * Revision 1.5  2005/05/19 13:02:17  southa
 * Mac release work
 *
 * Revision 1.4  2005/04/19 19:23:14  southa
 * Save and load config
 *
 * Revision 1.3  2005/03/25 19:13:50  southa
 * GameDialogue work
 *
 * Revision 1.2  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/02 23:33:38  southa
 * XML polymorphic objects
 *
 */

#include "MushcoreVirtualObject.h"

#include "MushcoreFail.h"
#include "MushcoreSTL.h"
#include "MushcoreUtil.h"
#include "MushcoreXMLIStream.h"
#include "MushcoreXMLOStream.h"

void
MushcoreVirtualObject::AutoInputPrologue(MushcoreXMLIStream& ioIn)
{
    // Do nothing in default prologue
}

void
MushcoreVirtualObject::AutoInputEpilogue(MushcoreXMLIStream& ioIn)
{
    // Do nothing in default epilogue
}

void
MushcoreVirtualObject::AutoOutputPrologue(MushcoreXMLOStream& ioOut) const
{
    // Do nothing in default prologue
}

void
MushcoreVirtualObject::AutoOutputEpilogue(MushcoreXMLOStream& ioOut) const
{
    // Do nothing in default epilogue
}

void
MushcoreVirtualObject::AutoStreamLoad(std::istream& ioStream)
{
    MushcoreXMLIStream xmlIn(ioStream);
    xmlIn >> *this;
}

void
MushcoreVirtualObject::AutoFileLoad(const std::string& inName)
{
    std::ifstream fileStream(MushcoreUtil::TranslateFilename(inName).c_str());
    if (!fileStream)
    {
        throw(MushcoreFileFail(inName, "Could not open file"));
    }
    AutoStreamLoad(fileStream);
}

bool
MushcoreVirtualObject::AutoFileIfExistsLoad(const std::string& inName)
{
    bool retVal = false;
    std::ifstream fileStream(MushcoreUtil::TranslateFilename(inName).c_str());
    if (fileStream)
    {
        AutoStreamLoad(fileStream);
        retVal = true;
    }
    return retVal;
}

void
MushcoreVirtualObject::AutoStreamSave(std::ostream& ioStream) const
{
    MushcoreXMLOStream xmlOut(ioStream);
    xmlOut << *this;
}

void
MushcoreVirtualObject::AutoFileSave(const std::string& inName) const
{
    std::ofstream fileStream(MushcoreUtil::TranslateFilename(inName).c_str());
    if (!fileStream)
    {
        throw(MushcoreFileFail(inName, "Could not write to file"));
    }
    AutoStreamSave(fileStream);
}
