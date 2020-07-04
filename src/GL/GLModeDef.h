//%includeGuardStart {
#ifndef GLMODEDEF_H
#define GLMODEDEF_H
//%includeGuardStart } HpyOkMHY3tVLkWwkBhP8FQ
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLModeDef.h
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
//%Header } ouW1awerCpcjvnQ6Iw7TTA

/*
 * $Id: GLModeDef.h,v 1.14 2006/11/25 21:26:31 southa Exp $
 * $Log: GLModeDef.h,v $
 * Revision 1.14  2006/11/25 21:26:31  southa
 * Display mode definitions
 *
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
