#ifndef GLSTRING_H
#define GLSTRING_H
/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GLString.h,v 1.5 2002/08/27 08:56:20 southa Exp $
 * $Log: GLString.h,v $
 * Revision 1.5  2002/08/27 08:56:20  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/19 22:18:36  southa
 * Display of time differences
 *
 * Revision 1.3  2002/08/13 18:29:04  southa
 * Tidied GameDialogue code
 *
 * Revision 1.2  2002/08/09 17:09:02  southa
 * GameDialogue added
 *
 * Revision 1.1  2002/08/08 13:39:09  southa
 * Text rendering
 *
 */

#include "mushCore.h"

#include "GLRenderable.h"
#include "GLFontRef.h"

class GLString : public GLRenderable
{
public:
    GLString() {}
    GLString(const string& inValue, const GLFontRef& inFont, tVal inAlign);
    void AlignmentSet(tVal inAlign) { m_alignment=inAlign; }
    void TextSet(const string& inStr) { m_value=inStr; }
    virtual void Render(void) const;
    virtual GLRenderable *Clone(void) const { return new GLString(*this); }

private:
    GLFontRef m_fontRef;
    string m_value;
    tVal m_alignment;
};
#endif
