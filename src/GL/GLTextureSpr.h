#ifndef GLTEXTURESPR_H
#define GLTEXTURESPR_H
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
 * $Id: GLTextureSpr.h,v 1.6 2002/10/22 20:42:01 southa Exp $
 * $Log: GLTextureSpr.h,v $
 * Revision 1.6  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/27 08:56:21  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:48  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/10 16:40:39  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/02/26 17:01:39  southa
 * Completed Sprite loader
 *
 */

#include "GLTexture.h"

class GLTextureSpr : public GLTexture
{
public:
    GLTextureSpr(const string& inFilename);
    GLTextureSpr *Clone(void) const {return new GLTextureSpr(*this);}

protected:

private:
    struct Palette
    {
        Mushware::U8 red;
        Mushware::U8 green;
        Mushware::U8 blue;
        Mushware::U8 alpha;
    };

    static void GeneratePalette(void);

    static Palette *m_palette;
    const char *FiletypeName(void) const;
};

class GLSpriteModeRO
{
public:
    GLSpriteModeRO(Mushware::U32 inMode):m_mode(inMode) {}
    Mushware::U32 Value(void) const {return m_mode;}
    bool Valid(void) const {return (m_mode==13 || m_mode==21);}
    bool PixelDouble(void) const {return (m_mode==13);}
    Mushware::U32 BitsPerPixel(void) const {return 8;}
private:
    Mushware::U32 m_mode;
    
};
#endif
