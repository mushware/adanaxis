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
 * $Id: GLFont.h,v 1.7 2002/12/29 20:30:52 southa Exp $
 * $Log: GLFont.h,v $
 * Revision 1.7  2002/12/29 20:30:52  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.6  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
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
    GLFont::GLFont(const std::string& inName);

    void RenderCharacter(Mushware::U32 inChar) const;
    void RenderString(const std::string& inStr, Mushware::tVal inAlign=-1.0) const;
    Mushware::tVal StringLengthGet(const std::string& inStr) const;
    void ShapeSet(Mushware::U32 inXNum, Mushware::U32 inYNum);
    void SizeSet(Mushware::tVal inXNum, Mushware::tVal inYNum);
        
    static void Install(void);
    static MushcoreScalar LoadFontMap(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);

private:
    const std::string m_name;
    const GLTextureRef m_texRef;
    Mushware::U32 m_xMapSize;
    Mushware::U32 m_yMapSize;
    Mushware::tVal m_xUsedSize;
    Mushware::tVal m_yUsedSize;
    Mushware::U32 m_xNum; // Must be integer types
    Mushware::U32 m_yNum;
};
#endif
