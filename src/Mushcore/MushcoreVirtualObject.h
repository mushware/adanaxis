//%includeGuardStart {
#ifndef MUSHCOREVIRTUALOBJECT_H
#define MUSHCOREVIRTUALOBJECT_H
//%includeGuardStart } A9fCmryMnprUYlvNkdoI2g
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreVirtualObject.h
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
//%Header } 1UPISQXVxwKPvRM5ihxf+g
/*
 * $Id: MushcoreVirtualObject.h,v 1.9 2006/06/01 15:39:48 southa Exp $
 * $Log: MushcoreVirtualObject.h,v $
 * Revision 1.9  2006/06/01 15:39:48  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/06/20 14:30:38  southa
 * Adanaxis work
 *
 * Revision 1.7  2005/06/14 13:25:34  southa
 * Adanaxis work
 *
 * Revision 1.6  2005/05/19 13:02:17  southa
 * Mac release work
 *
 * Revision 1.5  2005/04/19 19:23:14  southa
 * Save and load config
 *
 * Revision 1.4  2005/03/25 19:13:50  southa
 * GameDialogue work
 *
 * Revision 1.3  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
 * Revision 1.2  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/02 23:33:38  southa
 * XML polymorphic objects
 *
 */

#include "MushcoreStandard.h"

#include "MushcoreObject.h"

class MushcoreXMLIStream;
class MushcoreXMLOStream;

// General base class for objects with virtual functions

class MushcoreVirtualObject
{
public:
    virtual ~MushcoreVirtualObject() {}
    virtual const char *AutoName(void) const = 0;
    virtual MushcoreVirtualObject *AutoClone(void) const = 0;
    virtual MushcoreVirtualObject *AutoCreate(void) const = 0;

    virtual void AutoPrint(std::ostream& ioOut) const = 0;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr) = 0;
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const = 0;

    virtual void AutoInputPrologue(MushcoreXMLIStream& ioIn);
    virtual void AutoInputEpilogue(MushcoreXMLIStream& ioIn);   
    virtual void AutoOutputPrologue(MushcoreXMLOStream& ioOut) const;
    virtual void AutoOutputEpilogue(MushcoreXMLOStream& ioOut) const;   

    virtual void AutoStreamLoad(std::istream& ioStream);
    virtual void AutoFileLoad(const std::string& inName);
    virtual bool AutoFileIfExistsLoad(const std::string& inName);
    virtual void AutoStreamSave(std::ostream& ioStream) const;
    virtual void AutoFileSave(const std::string& inName) const;
};

inline std::ostream&
operator<<(std::ostream& ioOut, const MushcoreVirtualObject& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
