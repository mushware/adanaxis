/*
 * $Id: GLString.cpp,v 1.1 2002/08/08 13:39:09 southa Exp $
 * $Log: GLString.cpp,v $
 * Revision 1.1  2002/08/08 13:39:09  southa
 * Text rendering
 *
 */

#include "GLString.h"
#include "GLFont.h"
#include "GLUtils.h"

GLString::GLString(const string& inValue, const GLFontRef& inFont, tVal inAlign):
    m_fontRef(inFont),
    m_value(inValue),
    m_alignment(inAlign)
{
}

void
GLString::Render(void) const
{
    tVal size=m_fontRef.SizeGet();
    GLUtils::PushMatrix();
    GLUtils::Scale(size, size, 1);
    m_fontRef.FontGet()->RenderString(m_value, m_alignment);
    GLUtils::PopMatrix();
}
