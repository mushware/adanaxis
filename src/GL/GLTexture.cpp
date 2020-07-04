//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTexture.cpp
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
//%Header } V58jb+G28X+tQy4rPpK5wg
/*
 * $Id: GLTexture.cpp,v 1.37 2006/06/01 15:38:53 southa Exp $
 * $Log: GLTexture.cpp,v $
 * Revision 1.37  2006/06/01 15:38:53  southa
 * DrawArray verification and fixes
 *
 * Revision 1.36  2005/05/27 19:25:24  southa
 * win32 build fixes
 *
 * Revision 1.35  2005/05/19 13:02:00  southa
 * Mac release work
 *
 * Revision 1.34  2005/04/10 00:09:22  southa
 * Registration
 *
 * Revision 1.33  2005/02/13 22:44:06  southa
 * Tesseract stuff
 *
 * Revision 1.32  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.31  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.30  2003/08/21 23:08:30  southa
 * Fixed file headers
 *
 * Revision 1.29  2003/02/05 16:19:45  southa
 * Build fixes
 *
 * Revision 1.28  2003/01/13 14:31:55  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.27  2003/01/12 17:32:51  southa
 * Mushcore work
 *
 * Revision 1.26  2003/01/09 14:56:58  southa
 * Created Mushcore
 *
 * Revision 1.25  2002/12/29 20:59:53  southa
 * More build fixes
 *
 * Revision 1.24  2002/12/20 13:17:36  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.23  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.22  2002/10/15 14:02:29  southa
 * Mode changes
 *
 * Revision 1.21  2002/10/12 15:25:09  southa
 * Facet renderer
 *
 * Revision 1.20  2002/08/27 08:56:20  southa
 * Source conditioning
 *
 * Revision 1.19  2002/08/24 14:37:27  southa
 * Use gluBuild2DMipmaps for more robust texture generation
 *
 * Revision 1.18  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.17  2002/07/19 16:25:21  southa
 * Texture tweaks
 *
 * Revision 1.16  2002/07/19 15:44:39  southa
 * Graphic optimisations
 *
 * Revision 1.15  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.14  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.13  2002/06/02 20:37:39  southa
 * Set texture filtering
 *
 * Revision 1.12  2002/06/02 15:18:52  southa
 * Texture bitmap renderer
 *
 * Revision 1.11  2002/05/28 16:37:39  southa
 * Texture references and decomposer
 *
 * Revision 1.10  2002/05/24 18:10:43  southa
 * MushcoreXML and game map
 *
 * Revision 1.9  2002/05/10 16:41:43  southa
 * Changed .hp files to .h
 *
 * Revision 1.8  2002/02/26 17:01:38  southa
 * Completed Sprite loader
 *
 * Revision 1.7  2002/02/25 23:05:14  southa
 * Subclassed GLTexture
 *
 * Revision 1.6  2002/02/24 22:49:33  southa
 * Got working under cygwin
 *
 * Revision 1.5  2002/02/23 20:05:15  southa
 * Added libraries and test files
 *
 * Revision 1.4  2002/02/23 17:54:45  southa
 * Added GIF loader and GL tests
 *
 * Revision 1.3  2002/02/20 22:57:57  southa
 * Loading GIF data, texture memory handling
 *
 * Revision 1.2  2002/02/18 22:43:11  southa
 * First stage GIF loader
 *
 * Revision 1.1  2002/02/18 22:03:50  southa
 * Initial texture loading
 *
 */

#include "GLTexture.h"
#include "GLState.h"
#include "GLUtils.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(GLTexture);

GLTexture::~GLTexture()
{
    if (m_bound)
    {
        glDeleteTextures(1, &m_bindingName);
    }
}

ostream&
GLTexture::ostreamPrint(ostream& inOut) const
{
    inOut << "source " << FiletypeName() << " '" << FilenameGet() << "'";
    inOut << " images=" << NumberOf() << " ";
    for (U32 i=0; i<NumberOf(); ++i)
    {
        if (Valid(i))
        {
            inOut << "[image " << i << ":";
            inOut << " width=" << Width(i);
            inOut << " height=" << Height(i);
            inOut << " pixelFormat=" << PixelFormat(i);
            inOut << " pixelType=" << PixelType(i);
            inOut << " needsAlpha=" << NeedsAlpha(i);
            inOut << " dataPtr=" << DataPtr(i) << "] ";
        }
        else
        {
            inOut << "[Not valid] ";
        }
    }
    return inOut;
}

void
GLTexture::AddTextureDef(GLTextureDef& inDef, U32 inWhere)
{
    if (m_textureDefs.size() < inWhere+1)
    {
        m_textureDefs.resize(inWhere+1);
    }
    m_textureDefs[inWhere] = inDef;
}

bool
GLTexture::TextureDefValid(U32 inWhere) const
{
    if (inWhere >= m_textureDefs.size()) return false;
    return m_textureDefs[inWhere].Valid();
}

void
GLTexture::BindTexture(void) const
{
    MUSHCOREASSERT(!m_bound);
    glGenTextures(1, &m_bindingName);
    glBindTexture(GL_TEXTURE_2D, m_bindingName);
    GLState::TextureParamsReset();
    if (GLState::UseMipMap())
    {
#ifdef GL_VERSION_1_4
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
        
        glTexImage2D(GL_TEXTURE_2D, // target
                     0,             // level
                     GL_RGBA,       // internal format
                     Width(),       // width
                     Height(),      // height
                     0,             // border
                     PixelFormat(), // format
                     PixelType(),   // type
                     DataPtr()      // pointer to data
                     );   
#else
        GLint err=gluBuild2DMipmaps(GL_TEXTURE_2D, // target
                                    4,             // components
                                    Width(),       // width
                                    Height(),      // height
                                    PixelFormat(), // format
                                    PixelType(),   // type
                                    DataPtr()      // pointer to data
                                    );
        if (err != 0) cerr << "Error building mipmaps: " << gluErrorString(err) << endl;
#endif
    }
    else
    {
#ifdef GL_VERSION_1_4
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);
#endif

        glTexImage2D(GL_TEXTURE_2D, // target
                     0,             // level
                     GL_RGBA,       // internal format
                     Width(),       // width
                     Height(),      // height
                     0,             // border
                     PixelFormat(), // format
                     PixelType(),   // type
                     DataPtr()      // pointer to data
                     );
    }
    m_bound=true;
}

void
GLTexture::Decache(void)
{
    if (m_bound)
    {
        glDeleteTextures(1, &m_bindingName);
        m_bound=false;
    }
}
