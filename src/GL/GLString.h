/*
 * $Id: GLString.h,v 1.3 2002/08/13 18:29:04 southa Exp $
 * $Log: GLString.h,v $
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
