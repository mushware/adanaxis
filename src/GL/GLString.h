#ifndef GLSTRING_H
#define GLSTRING_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GLString.h,v 1.7 2002/12/20 13:17:35 southa Exp $
 * $Log: GLString.h,v $
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
#endif
