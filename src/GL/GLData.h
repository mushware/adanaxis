//%includeGuardStart {
#ifndef GLDATA_H
#define GLDATA_H
//%includeGuardStart } or4rx57MjO/4TXUq6Jj4NA
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLData.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 5YXsATXmA74DZhOFKZ0UzQ
/*
 * $Id: GLData.h,v 1.17 2003/09/17 19:40:29 southa Exp $
 * $Log: GLData.h,v $
 * Revision 1.17  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.16  2003/08/21 23:08:20  southa
 * Fixed file headers
 *
 * Revision 1.15  2003/02/05 16:19:45  southa
 * Build fixes
 *
 * Revision 1.14  2003/01/20 10:45:23  southa
 * Singleton tidying
 *
 * Revision 1.13  2002/12/29 20:30:52  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.12  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.11  2002/10/22 20:42:00  southa
 * Source conditioning
 *
 * Revision 1.10  2002/10/15 14:02:29  southa
 * Mode changes
 *
 * Revision 1.9  2002/10/08 22:47:07  southa
 * Fixed initialisation bug
 *
 * Revision 1.8  2002/10/08 17:13:16  southa
 * Tiered maps
 *
 * Revision 1.7  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/08 13:39:09  southa
 * Text rendering
 *
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
class GLLights;

class GLData
{
public:
    GLData();
    ~GLData();
    static GLData& Sgl(void) {return *((m_instance==NULL)?m_instance=new GLData:m_instance);}
    void TextureAdd(const std::string& inName, const GLTexture& inTexture);
    GLTexture *TextureFind(const std::string& inName);
    GLFont *FontGive(const std::string& inName, GLFont *inFont);
    GLFont *FontGet(const std::string& inName) const;
    GLLights *LightsGet(void);
    void Decache(void);
    void DumpTextures(std::ostream& inOut);
    
private:
    std::map<std::string, GLTexture *> m_textures;
    std::map<std::string, GLFont *> m_fonts;
    GLLights *m_lights;
    static GLData *m_instance;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
