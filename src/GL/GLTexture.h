#ifndef GLTEXTURE_H
#define GLTEXTURE_H
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
 * $Id: GLTexture.h,v 1.12 2002/10/22 20:42:01 southa Exp $
 * $Log: GLTexture.h,v $
 * Revision 1.12  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.11  2002/10/15 14:02:29  southa
 * Mode changes
 *
 * Revision 1.10  2002/08/27 08:56:20  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.8  2002/07/19 15:44:39  southa
 * Graphic optimisations
 *
 * Revision 1.7  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.6  2002/07/02 15:48:29  southa
 * Floor std::map designer
 *
 * Revision 1.5  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.4  2002/06/02 15:18:52  southa
 * Texture bitmap renderer
 *
 * Revision 1.3  2002/05/28 16:37:39  southa
 * Texture references and decomposer
 *
 * Revision 1.2  2002/05/24 18:10:43  southa
 * CoreXML and game map
 *
 * Revision 1.1  2002/05/10 16:40:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.11  2002/05/09 17:08:07  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.10  2002/05/08 16:31:21  southa
 * Created API directory
 *
 * Revision 1.9  2002/03/21 22:07:54  southa
 * Initial wrangle application handler
 *
 * Revision 1.8  2002/02/26 17:01:38  southa
 * Completed Sprite loader
 *
 * Revision 1.7  2002/02/25 23:05:14  southa
 * Subclassed GLTexture
 *
 * Revision 1.6  2002/02/23 23:58:45  southa
 * Made buildable for cygwin
 *
 * Revision 1.5  2002/02/23 17:54:45  southa
 * Added GIF loader and GL tests
 *
 * Revision 1.4  2002/02/23 11:43:36  southa
 * Added AutoMonkey
 *
 * Revision 1.3  2002/02/20 22:57:57  southa
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
#include "GLTextureDef.h"
#include "mushCore.h"

class GLTexture
{
public:
    GLTexture(): m_bound(false) {}
    virtual ~GLTexture();
    virtual GLTexture *Clone(void) const = 0;
    virtual GLsizei Width(Mushware::U32 inRef=0) const {return TextureDefGet(inRef).Width();}
    virtual GLsizei Height(Mushware::U32 inRef=0) const {return TextureDefGet(inRef).Height();}
    virtual GLenum PixelFormat(Mushware::U32 inRef=0) const {return TextureDefGet(inRef).PixelFormat();}
    virtual GLenum PixelType(Mushware::U32 inRef=0) const {return TextureDefGet(inRef).PixelType();}
    virtual bool NeedsAlpha(Mushware::U32 inRef=0) const {return TextureDefGet(inRef).NeedsAlpha();}
    virtual Mushware::U32 *DataPtr(Mushware::U32 inRef=0) const {return TextureDefGet(inRef).DataPtr();}
    virtual bool Valid(Mushware::U32 inRef=0) const {return (inRef<NumberOf())?TextureDefGet(inRef).Valid():false;}
    virtual Mushware::U32 NumberOf(void) const {return m_textureDefs.size();}
    virtual std::ostream& ostreamPrint(std::ostream& inOut) const;
    const string& FilenameGet(void) const {return m_inFilename;}

    GLuint BindingNameGet(Mushware::U32 inRef=0) const {if (m_bound) return m_bindingName; BindTexture(); return m_bindingName;}
    void BindTexture(void) const;
    void Decache(void);
    
protected:
    virtual const char *FiletypeName(void) const = 0;
    void FilenameSet(const string& inFilename) {m_inFilename=inFilename;}
    void AddTextureDef(GLTextureDef& inDef) {m_textureDefs.push_back(inDef);}
    void AddTextureDef(GLTextureDef& inDef, Mushware::U32 inWhere);
    bool TextureDefValid(Mushware::U32 inWhere) const;
    const GLTextureDef& TextureDefGet(Mushware::U32 inIndex) const {if (inIndex>m_textureDefs.size()) throw "Texture def index out of range"; return m_textureDefs[inIndex];}
    
private:
    std::vector<GLTextureDef> m_textureDefs;
    string m_inFilename;
    mutable bool m_bound;
    mutable GLuint m_bindingName;
};

inline std::ostream& operator<<(std::ostream &inOut, const GLTexture& inTex)
{
    return inTex.ostreamPrint(inOut);
}

#endif
