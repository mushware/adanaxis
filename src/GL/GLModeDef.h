//%includeGuardStart {
#ifndef GLMODEDEF_H
#define GLMODEDEF_H
//%includeGuardStart } HpyOkMHY3tVLkWwkBhP8FQ
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLModeDef.h
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
//%Header } Rz2L7OMoKXcq+Y5XU4qSww

/*
 * $Id: GLModeDef.h,v 1.13 2006/07/27 13:51:35 southa Exp $
 * $Log: GLModeDef.h,v $
 * Revision 1.13  2006/07/27 13:51:35  southa
 * Menu and control fixes
 *
 * Revision 1.12  2006/06/01 15:38:51  southa
 * DrawArray verification and fixes
 *
 * Revision 1.11  2005/05/19 13:01:59  southa
 * Mac release work
 *
 * Revision 1.10  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.9  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.8  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:08:24  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.5  2002/12/29 20:30:52  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.4  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/10/22 20:42:00  southa
 * Source conditioning
 *
 * Revision 1.2  2002/10/15 14:02:29  southa
 * Mode changes
 *
 * Revision 1.1  2002/10/14 18:13:17  southa
 * GLModeDef work
 *
 */

#include "mushMushcore.h"

//:generate virtual standard basic ostream xml1
class GLModeDef : public MushcoreVirtualObject
{
public:
    GLModeDef();
    
    GLModeDef(Mushware::U32 inWidth, Mushware::U32 inHeight, bool inFullScreen) :
        m_width(inWidth),
        m_height(inHeight),
        m_fullScreen(inFullScreen)
    {}

private:
    Mushware::U32 m_width; //:readwrite
    Mushware::U32 m_height; //:readwrite
    bool m_fullScreen; //:readwrite
//%classPrototypes {
public:
    const Mushware::U32& Width(void) const { return m_width; }
    void WidthSet(const Mushware::U32& inValue) { m_width=inValue; }
    const Mushware::U32& Height(void) const { return m_height; }
    void HeightSet(const Mushware::U32& inValue) { m_height=inValue; }
    const bool& FullScreen(void) const { return m_fullScreen; }
    void FullScreenSet(const bool& inValue) { m_fullScreen=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual bool AutoEquals(const GLModeDef& inObj) const;
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } CdiEbwOj7MC2hdm6OXtB+w
};
//%inlineHeader {

inline bool
operator==(const GLModeDef& inA, const GLModeDef& inB)
{
    return inA.AutoEquals(inB);
}

inline bool
operator!=(const GLModeDef& inA, const GLModeDef& inB)
{
    return !inA.AutoEquals(inB);
}
inline std::ostream&
operator<<(std::ostream& ioOut, const GLModeDef& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } R04B0vPw0dYE31MBJCGMww

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
