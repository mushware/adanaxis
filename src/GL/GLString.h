/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

#include "GLRenderable.h"
#include "GLFontRef.h"

class GLString : public GLRenderable
{
public:
    GLString(const string& inFont, const string& inValue);
    virtual void Render(void) const;
    virtual GLRenderable *Clone(void) const { return new GLString(*this); }

private:
    const GLFontRef m_fontRef;
    string m_value;
};
