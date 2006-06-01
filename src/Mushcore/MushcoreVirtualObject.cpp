//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreVirtualObject.cpp
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } VvwJX/VCs5nL1O4p94ACvg
/*
 * $Id: MushcoreVirtualObject.cpp,v 1.6 2005/06/14 13:25:34 southa Exp $
 * $Log: MushcoreVirtualObject.cpp,v $
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
