//%includeGuardStart {
#ifndef GLSTRING_H
#define GLSTRING_H
//%includeGuardStart } 9oW5IIFGWEzpYLY9Ura2cA
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLString.h
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
//%Header } Ue7yL6++NC86cJ2R4GiwPA
/*
 * $Id: GLString.h,v 1.18 2006/06/01 15:38:53 southa Exp $
 * $Log: GLString.h,v $
 * Revision 1.18  2006/06/01 15:38:53  southa
 * DrawArray verification and fixes
 *
 * Revision 1.17  2005/06/20 14:30:33  southa
 * Adanaxis work
 *
 * Revision 1.16  2005/05/19 13:02:00  southa
 * Mac release work
 *
 * Revision 1.15  2005/03/25 19:13:48  southa
 * GameDialogue work
 *
 * Revision 1.14  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.13  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.12  2003/10/04 15:32:08  southa
 * Module split
 *
 * Revision 1.11  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.10  2003/08/21 23:08:29  southa
 * Fixed file headers
 *
 * Revision 1.9  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.8  2002/12/29 20:30:52  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.7  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/27 08:56:20  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/19 22:18:36  southa
 * Display of time differences
 *
 * Revision 1.3  2002/08/13 18:29:04  southa
 * Tidied InfernalDialogue code
 *
 * Revision 1.2  2002/08/09 17:09:02  southa
 * InfernalDialogue added
 *
 * Revision 1.1  2002/08/08 13:39:09  southa
 * Text rendering
 *
 */

#include "mushMushcore.h"

#include "GLFontRef.h"
#include "GLRenderable.h"

//:generate virtual basic standard ostream xml1
class GLString : public GLRenderable, public MushcoreVirtualObject
{
public:
    GLString() : m_alignment(0) {}
    GLString(const std::string& inValue, const GLFontRef& inFont, Mushware::tVal inAlign);
    void AlignmentSet(Mushware::tVal inAlign) { m_alignment=inAlign; }
    void TextSet(const std::string& inStr) { m_value=inStr; }
    virtual void Render(void) const;
    virtual GLRenderable *Clone(void) const { return new GLString(*this); }

private:
    GLFontRef m_fontRef;
    std::string m_value;
    Mushware::tVal m_alignment;
    
//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual bool AutoEquals(const GLString& inObj) const;
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } ZEMcDmpGy7XyML1w84ffyQ
};
//%inlineHeader {

inline bool
operator==(const GLString& inA, const GLString& inB)
{
    return inA.AutoEquals(inB);
}

inline bool
operator!=(const GLString& inA, const GLString& inB)
{
    return !inA.AutoEquals(inB);
}
inline std::ostream&
operator<<(std::ostream& ioOut, const GLString& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } zaG+hNv8VXBeyZ4toQsZKA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
