//%includeGuardStart {
#ifndef GLSTRING_H
#define GLSTRING_H
//%includeGuardStart } 9oW5IIFGWEzpYLY9Ura2cA
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLString.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } XagZxWZIAf6/N5/5LJQ3aw
/*
 * $Id: GLString.h,v 1.12 2003/10/04 15:32:08 southa Exp $
 * $Log: GLString.h,v $
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

#include "Mushcore.h"

#include "GLFontRef.h"
#include "GLRenderable.h"

class GLString : public GLRenderable
{
public:
    GLString() {}
    GLString(const std::string& inValue, const GLFontRef& inFont, Mushware::tVal inAlign);
    void AlignmentSet(Mushware::tVal inAlign) { m_alignment=inAlign; }
    void TextSet(const std::string& inStr) { m_value=inStr; }
    virtual void Render(void) const;
    virtual GLRenderable *Clone(void) const { return new GLString(*this); }

private:
    GLFontRef m_fontRef;
    std::string m_value;
    Mushware::tVal m_alignment;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
