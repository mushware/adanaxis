#ifndef GLDATA_H
#define GLDATA_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/



/*
 * $Id: GLData.h,v 1.5 2002/08/07 13:36:46 southa Exp $
 * $Log: GLData.h,v $
 * Revision 1.5  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/28 16:37:39  southa
 * Texture references and decomposer
 *
 * Revision 1.1  2002/05/10 16:41:43  southa
 * Changed .hp files to .h
 *
 * Revision 1.6  2002/03/21 22:07:54  southa
 * Initial wrangle application handler
 *
 * Revision 1.5  2002/02/25 23:05:14  southa
 * Subclassed GLTexture
 *
 * Revision 1.4  2002/02/23 17:54:45  southa
 * Added GIF loader and GL tests
 *
 * Revision 1.3  2002/02/20 22:57:56  southa
 * Loading GIF data, texture memory handling
 *
 * Revision 1.2  2002/02/18 22:43:53  southa
 * First stage GIF loader
 *
 * Revision 1.1  2002/02/18 22:04:37  southa
 * Initial texture loading
 *
 */

#include "GLStandard.h"

class GLTexture;
class GLFont;

class GLData
{
public:
    ~GLData();
    static GLData& Instance(void) {return *((m_instance==NULL)?m_instance=new GLData:m_instance);}
    void TextureAdd(const string& inName, const GLTexture& inTexture);
    GLTexture *TextureFind(const string& inName);
    GLFont *FontGive(const string& inName, GLFont *inFont);
    GLFont *FontGet(const string& inName) const;
    void DumpTextures(ostream& inOut);
    
private:
    map<string, GLTexture *> m_textures;
    map<string, GLFont *> m_fonts;
    static GLData *m_instance;
};
#endif
