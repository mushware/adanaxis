/*
 * $Id: GLString.h,v 1.1 2002/08/08 13:39:09 southa Exp $
 * $Log: GLString.h,v $
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
    GLString(const string& inValue, const GLFontRef& inFont, tVal inAlign);
    void AlignmentSet(tVal inAlign) { m_alignment=inAlign; }
    virtual void Render(void) const;
    virtual GLRenderable *Clone(void) const { return new GLString(*this); }

private:
    GLFontRef m_fontRef;
    string m_value;
    tVal m_alignment;
};
