#ifndef GLTEXTURE_H
#define GLTEXTURE_H
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
 * $Id: GLTexture.h,v 1.6 2002/07/02 15:48:29 southa Exp $
 * $Log: GLTexture.h,v $
 * Revision 1.6  2002/07/02 15:48:29  southa
 * Floor map designer
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

#include "mushCore.h"
#include "GLStandard.h"

class GLTexture
{
public:
    GLTexture(): m_bound(false) {}
    virtual ~GLTexture();
    virtual GLTexture *Clone(void) const = 0;
    virtual GLsizei Width(U32 inRef=0) const {return TextureDefGet(inRef).Width();}
    virtual GLsizei Height(U32 inRef=0) const {return TextureDefGet(inRef).Height();}
    virtual GLenum PixelFormat(U32 inRef=0) const {return TextureDefGet(inRef).PixelFormat();}
    virtual GLenum PixelType(U32 inRef=0) const {return TextureDefGet(inRef).PixelType();}
    virtual U32 *DataPtr(U32 inRef=0) const {return TextureDefGet(inRef).DataPtr();}
    virtual bool Valid(U32 inRef=0) const {return (inRef<NumberOf())?TextureDefGet(inRef).Valid():false;}
    virtual tSize NumberOf(void) const {return m_textureDefs.size();}
    virtual ostream& ostreamPrint(ostream& inOut) const;
    const string& FilenameGet(void) const {return m_inFilename;}

    GLuint BindingNameGet(U32 inRef=0) const {if (m_bound) return m_bindingName; BindTexture(); return m_bindingName;}
    void BindTexture(void) const;
    
protected:
    class TextureDef
    {
    public:
        TextureDef(): m_dataPtr(NULL) {}
        TextureDef(U32 *inDataPtr): m_dataPtr(inDataPtr) {}
        ~TextureDef() {if (m_autoMonkey.FreeInDestructor(m_dataPtr)) delete[]m_dataPtr;}
        void WidthSet(GLsizei inWidth) {m_width=inWidth;}
        void HeightSet(GLsizei inHeight) {m_height=inHeight;}
        void PixelFormatSet(GLenum inPixelFormat) {m_pixelFormat=inPixelFormat;}
        void PixelTypeSet(GLenum inPixelType) {m_pixelType=inPixelType;}
        bool Valid(void) const {return (m_dataPtr != NULL);}
        GLsizei Width(void) const {return m_width;}
        GLsizei Height(void) const {return m_height;}
        GLenum PixelFormat(void) const {return m_pixelFormat;}
        GLenum PixelType(void) const {return m_pixelType;}
        U32 *DataPtr(void) const {return m_dataPtr;}
        
    private:
        GLsizei m_width;
        GLsizei m_height;
        GLenum m_pixelFormat;
        GLenum m_pixelType;
        U32 *m_dataPtr;
        CoreAutoMonkey m_autoMonkey;
    };

    virtual const char *FiletypeName(void) const = 0;
    void FilenameSet(const string& inFilename) {m_inFilename=inFilename;}
    void AddTextureDef(TextureDef& inDef) {m_textureDefs.push_back(inDef);}
    void AddTextureDef(TextureDef& inDef, tSize inWhere);
    bool TextureDefValid(tSize inWhere) const;
    const TextureDef& TextureDefGet(tSize inIndex) const {if (inIndex>m_textureDefs.size()) throw "Texture def index out of range"; return m_textureDefs[inIndex];}
    
private:
    vector<TextureDef> m_textureDefs;
    string m_inFilename;
    mutable bool m_bound;
    mutable GLuint m_bindingName;
};

inline ostream& operator<<(ostream &inOut, const GLTexture& inTex)
{
    return inTex.ostreamPrint(inOut);
}

#endif
