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
 * $Id: GLTexture.cpp,v 1.24 2002/12/20 13:17:36 southa Exp $
 * $Log: GLTexture.cpp,v $
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
 * CoreXML and game map
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

using namespace Mushware;
using namespace std;

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
GLTexture::AddTextureDef(GLTextureDef& inDef, tSize inWhere)
{
    if (m_textureDefs.size() < inWhere+1)
    {
        m_textureDefs.resize(inWhere+1);
    }
    m_textureDefs[inWhere] = inDef;
}

bool
GLTexture::TextureDefValid(tSize inWhere) const
{
    if (inWhere >= m_textureDefs.size()) return false;
    return m_textureDefs[inWhere].Valid();
}

void
GLTexture::BindTexture(void) const
{
    COREASSERT(!m_bound);
    glGenTextures(1, &m_bindingName);
    glBindTexture(GL_TEXTURE_2D, m_bindingName);
    GLState::TextureParamsReset();
    if (1)
    {
        GLint err=gluBuild2DMipmaps(GL_TEXTURE_2D, // target
                                    4,             // components
                                    Width(),       // width
                                    Height(),      // height
                                    PixelFormat(), // format
                                    PixelType(),   // type
                                    DataPtr()      // pointer to data
                                    );
        if (err != 0) cerr << "Error building mipmaps: " << gluErrorString(err) << endl;
    }
    else
    {
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
