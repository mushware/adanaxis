/*
 * $Id: GLTextureSpr.h,v 1.1 2002/02/26 17:01:39 southa Exp $
 * $Log: GLTextureSpr.h,v $
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
        U8 red;
        U8 green;
        U8 blue;
        U8 alpha;
    };

    static void GeneratePalette(void);

    static Palette *m_palette;
    const char *FiletypeName(void) const;
};

class GLSpriteModeRO
{
public:
    GLSpriteModeRO(U32 inMode):m_mode(inMode) {}
    U32 Value(void) const {return m_mode;}
    bool Valid(void) const {return (m_mode==13 || m_mode==21);}
    bool PixelDouble(void) const {return (m_mode==13);}
    U32 BitsPerPixel(void) const {return 8;}
private:
    U32 m_mode;
    
};
