//%includeGuardStart {
#ifndef GLTEXTURE_H
#define GLTEXTURE_H
//%includeGuardStart } Vklsdh1o2zaZOVz+l73KYw
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTexture.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } +0Kywp1jZmJt6cxHc4n6Lg
/*
 * $Id: GLTexture.h,v 1.23 2006/06/01 15:38:53 southa Exp $
 * $Log: GLTexture.h,v $
 * Revision 1.23  2006/06/01 15:38:53  southa
 * DrawArray verification and fixes
 *
 * Revision 1.22  2005/05/19 13:02:00  southa
 * Mac release work
 *
 * Revision 1.21  2005/02/13 22:44:06  southa
 * Tesseract stuff
 *
 * Revision 1.20  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.19  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.18  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.17  2003/08/21 23:08:30  southa
 * Fixed file headers
 *
 * Revision 1.16  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.15  2003/01/09 14:56:58  southa
 * Created Mushcore
 *
 * Revision 1.14  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.13  2002/12/20 13:17:36  southa
 * Namespace changes, licence changes and source conditioning
 *
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
 * MushcoreXML and game map
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
#include "mushMushcore.h"

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
    const std::string& FilenameGet(void) const {return m_inFilename;}

    GLuint BindingNameGet(Mushware::U32 inRef=0) const {if (m_bound) return m_bindingName; BindTexture(); return m_bindingName;}
    void BindTexture(void) const;
    void Decache(void);
    
protected:
    virtual const char *FiletypeName(void) const = 0;
    void FilenameSet(const std::string& inFilename) {m_inFilename=inFilename;}
    void AddTextureDef(GLTextureDef& inDef) {m_textureDefs.push_back(inDef);}
    void AddTextureDef(GLTextureDef& inDef, Mushware::U32 inWhere);
    bool TextureDefValid(Mushware::U32 inWhere) const;
    const GLTextureDef& TextureDefGet(Mushware::U32 inIndex) const {if (inIndex >= m_textureDefs.size()) throw "Texture def index out of range"; return m_textureDefs[inIndex];}
    
private:
    std::vector<GLTextureDef> m_textureDefs;
    std::string m_inFilename;
    mutable bool m_bound;
    mutable GLuint m_bindingName;
};

inline std::ostream& operator<<(std::ostream &inOut, const GLTexture& inTex)
{
    return inTex.ostreamPrint(inOut);
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
