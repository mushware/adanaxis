/*
 * $Id: GLFont.h,v 1.1 2002/08/08 13:39:09 southa Exp $
 * $Log: GLFont.h,v $
 * Revision 1.1  2002/08/08 13:39:09  southa
 * Text rendering
 *
 */

#include "mushCore.h"

#include "GLTextureRef.h"

class GLFont
{
public:
    GLFont::GLFont(const string& inName);

    void RenderCharacter(U32 inChar) const;
    void RenderString(const string& inStr) const;
    void ShapeSet(U32 inXNum, U32 inYNum);
    void SizeSet(tVal inXNum, tVal inYNum);
        
    static void Install(void);
    static CoreScalar LoadFontMap(CoreCommand& ioCommand, CoreEnv& ioEnv);

private:
    const string m_name;
    const GLTextureRef m_texRef;
    U32 m_xMapSize;
    U32 m_yMapSize;
    tVal m_xUsedSize;
    tVal m_yUsedSize;
    U32 m_xNum; // Must be integer types
    U32 m_yNum;
};