//%includeGuardStart {
#ifndef MUSHCOREVIRTUALOBJECT_H
#define MUSHCOREVIRTUALOBJECT_H
//%includeGuardStart } A9fCmryMnprUYlvNkdoI2g
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreVirtualObject.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } A5JUCROnCrKysqG6sd4RBA
/*
 * $Id: MushcoreVirtualObject.h,v 1.7 2005/06/14 13:25:34 southa Exp $
 * $Log: MushcoreVirtualObject.h,v $
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
