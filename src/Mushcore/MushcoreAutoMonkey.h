//%includeGuardStart {
#ifndef MUSHCOREAUTOMONKEY_H
#define MUSHCOREAUTOMONKEY_H
//%includeGuardStart } 7kJ6RZCh9NH2JfHT3G29Fg
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreAutoMonkey.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } 9lBXu9pWRLf41827iqmIew
/*
 * $Id: MushcoreAutoMonkey.h,v 1.10 2006/10/16 14:36:51 southa Exp $
 * $Log: MushcoreAutoMonkey.h,v $
 * Revision 1.10  2006/10/16 14:36:51  southa
 * Deco handling
 *
 * Revision 1.9  2006/06/01 15:39:41  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/05/19 13:02:14  southa
 * Mac release work
 *
 * Revision 1.7  2004/01/02 21:13:12  southa
 * Source conditioning
 *
 * Revision 1.6  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.5  2003/08/21 23:09:04  southa
 * Fixed file headers
 *
 * Revision 1.4  2003/01/17 13:30:40  southa
 * Source conditioning and build fixes
 *
 * Revision 1.3  2003/01/12 17:32:58  southa
 * Mushcore work
 *
 * Revision 1.2  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:05  southa
 * Created Mushcore
 *
 * Revision 1.6  2002/12/20 13:17:31  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/10/22 20:41:57  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/27 08:56:15  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/07 13:36:44  southa
 * Conditioned source
 *
 * Revision 1.2  2002/07/06 18:04:14  southa
 * More designer work
 *
 * Revision 1.1  2002/07/02 09:12:53  southa
 * Name changed to MushcoreAutoMonkey
 *
 * Revision 1.2  2002/06/27 12:36:02  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.3  2002/02/26 17:01:40  southa
 * Completed Sprite loader
 *
 * Revision 1.2  2002/02/23 17:54:45  southa
 * Added GIF loader and GL tests
 *
 * Revision 1.1  2002/02/23 11:43:34  southa
 * Added MushcoreAutoMonkey
 *
 */

#include "MushcoreStandard.h"

/* Use like this to delete data when the last copy of MyClass referencing the
 * data is deleted.  This makes a class holding a pointer to private data safe
 * to place in STL containers without copying the data.  Use delete[] for array
 * data.
 *
 * class MyClass
 * {
 * public:
 *     MyClass(): m_dataPtr(NULL) {}
 *     MyClass(void *inDataPtr): m_dataPtr(inDataPtr) {}
 *     ~MyClass() { if (m_autoMonkey.FreeInDestructor(m_dataPtr)) delete m_dataPtr;}
 * 
 * private:
 *     void *m_dataPtr;
 *     MushcoreAutoMonkey m_autoMonkey;
 * };
 */

#include "MushcoreVirtualObject.h"

class MushcoreXMLIStream;
class MushcoreXMLOStream;

//:generate virtual ostream standard xml1
class MushcoreAutoMonkey : public MushcoreVirtualObject
{
public:
    MushcoreAutoMonkey(): m_refCtrPtr(new Mushware::U32(1)) {}
    ~MushcoreAutoMonkey();
    MushcoreAutoMonkey(const MushcoreAutoMonkey& inMonkey);
    bool FreeInDestructor(void *inDataPtr) const;
    bool FreeInDestructor(void) const;

    Mushware::U32 ReferenceCountGet(void) const {return *m_refCtrPtr;} // For testing
    MushcoreAutoMonkey& operator=(const MushcoreAutoMonkey&);
    
private:
    void Swap(MushcoreAutoMonkey& inMonkey);
    Mushware::U32 *m_refCtrPtr;
//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushcoreAutoMonkey& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } DjYpOXMqzNerIuqJGcVIIA

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
