//%includeGuardStart {
#ifndef GLKEYS_H
#define GLKEYS_H
//%includeGuardStart } LC6xyJ9N6H9Nez2kAwQpmg
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLKeys.h
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
//%Header } JULuY8zijzl3gSY8zJcPUA
/*
 * $Id: GLKeys.h,v 1.18 2006/06/01 15:38:51 southa Exp $
 * $Log: GLKeys.h,v $
 * Revision 1.18  2006/06/01 15:38:51  southa
 * DrawArray verification and fixes
 *
 * Revision 1.17  2005/07/08 12:07:07  southa
 * MushGaem control work
 *
 * Revision 1.16  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.15  2005/05/19 13:01:59  southa
 * Mac release work
 *
 * Revision 1.14  2005/03/13 00:34:45  southa
 * Build fixes, key support and stereo
 *
 * Revision 1.13  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.12  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.11  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.10  2003/08/21 23:08:22  southa
 * Fixed file headers
 *
 * Revision 1.9  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.8  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/10/22 20:42:00  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.3  2002/07/02 18:36:56  southa
 * Selection in designer, mouse buttons
 *
 * Revision 1.2  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/31 15:18:16  southa
 * Keyboard reading
 *
 */

#include "mushMushcore.h"

//:generate standard ostream xml1
class GLKeys : public MushcoreVirtualObject
{
public:
    enum tKeyValue
    {
        // Special keys start at 0x100
        kKeyF1=0x100,
        kKeyF2,
        kKeyF3,
        kKeyF4,
        kKeyF5,
        kKeyF6,
        kKeyF7,
        kKeyF8,
        kKeyF9,
        kKeyF10,
        kKeyF11,
        kKeyF12,
        kKeyLeft,
        kKeyUp,
        kKeyRight,
        kKeyDown,
        kKeyPageUp,
        kKeyPageDown,
        kKeyHome,
        kKeyEnd,
        kKeyInsert,
        kKeyMouse1,
        kKeyMouse2,
        kKeyMouse3,
        kKeyMouse4,
        kKeyMouse5,
        kKeyCommand,
        kNumberOfKeys
    };
    GLKeys() {}
    GLKeys(Mushware::U32 inKeyValue): m_keyValue(inKeyValue) {}
    GLKeys(tKeyValue inKeyValue): m_keyValue(static_cast<Mushware::U32>(inKeyValue)) {}
    Mushware::U32 Value(void) const { return m_keyValue; }
    Mushware::U32 ValueGet(void) const { return Value(); }
    
private:
    Mushware::U32 m_keyValue; //:readwrite
    
//%classPrototypes {
public:
    const Mushware::U32& KeyValue(void) const { return m_keyValue; }
    void KeyValueSet(const Mushware::U32& inValue) { m_keyValue=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } ml2boRUrSoeXDYErW7d29g
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const GLKeys& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } cqUQB5uB5mxzaAvZqqSgvQ

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
