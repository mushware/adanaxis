/*
 * $Id$
 * $Log$
 */

#include "GLString.h"
#include "GLFont.h"

GLString::GLString(const string& inFont, const string& inValue):
    m_fontRef(inFont),
    m_value(inValue)
{
}

void
GLString::Render(void) const
{
    m_fontRef.FontGet()->RenderString(m_value);
}
