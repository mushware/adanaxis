/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

#include "GLTextureRef.h"

class GLFont
{
public:
    GLFont::GLFont(const string& inName);

    void RenderCharacter(U32 inChar) const;
    void RenderString(const string& inStr) const;
    
    static void Install(void);
    static CoreScalar LoadFontMap(CoreCommand& ioCommand, CoreEnv& ioEnv);

private:
    const string m_name;
    const GLTextureRef m_texRef;
    U32 m_xstep;
    U32 m_ystep;
};