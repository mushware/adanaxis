#ifndef GLFONT_H
#define GLFONT_H
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
 * $Id: GLFont.h,v 1.5 2002/10/22 20:42:00 southa Exp $
 * $Log: GLFont.h,v $
 * Revision 1.5  2002/10/22 20:42:00  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/09 17:09:02  southa
 * GameDialogue added
 *
 * Revision 1.2  2002/08/08 18:20:29  southa
 * Plot on screen of dimension 1.0
 *
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

    void RenderCharacter(Mushware::U32 inChar) const;
    void RenderString(const string& inStr, Mushware::tVal inAlign=-1.0) const;
    Mushware::tVal StringLengthGet(const string& inStr) const;
    void ShapeSet(Mushware::U32 inXNum, Mushware::U32 inYNum);
    void SizeSet(Mushware::tVal inXNum, Mushware::tVal inYNum);
        
    static void Install(void);
    static CoreScalar LoadFontMap(CoreCommand& ioCommand, CoreEnv& ioEnv);

private:
    const string m_name;
    const GLTextureRef m_texRef;
    Mushware::U32 m_xMapSize;
    Mushware::U32 m_yMapSize;
    Mushware::tVal m_xUsedSize;
    Mushware::tVal m_yUsedSize;
    Mushware::U32 m_xNum; // Must be integer types
    Mushware::U32 m_yNum;
};
#endif
