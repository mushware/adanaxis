/*
 * $Id: GLTexture.cpp,v 1.12 2002/06/02 15:18:52 southa Exp $
 * $Log: GLTexture.cpp,v $
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
GLTexture::AddTextureDef(TextureDef& inDef, tSize inWhere)
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
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glTexImage2D(
	GL_TEXTURE_2D, // target
	0, // level
	GL_RGBA, // internal format
	Width(), // width
	Height(), // height
	0, //border
	PixelFormat(), // format
	PixelType(), // type
	DataPtr() // pointer to data
	);
    m_bound=true;
}

