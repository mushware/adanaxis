//%includeGuardStart {
#ifndef GLTEXTURESPR_H
#define GLTEXTURESPR_H
//%includeGuardStart } xgWGc2akrEc8dYAXHAPsdA
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTextureSpr.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 6ipleIzXlhRTQvoATU4KNw
/*
 * $Id: GLTextureSpr.h,v 1.10 2003/09/17 19:40:30 southa Exp $
 * $Log: GLTextureSpr.h,v $
 * Revision 1.10  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.9  2003/08/21 23:08:32  southa
 * Fixed file headers
 *
 * Revision 1.8  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.7  2002/12/20 13:17:36  southa
 * Namespace changes, licence changes and source conditioning
 *
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
    GLTextureSpr(const std::string& inFilename);
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
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
