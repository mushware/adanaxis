/*
 * $Id: GLTexture.cpp,v 1.6 2002/02/24 22:49:33 southa Exp $
 * $Log: GLTexture.cpp,v $
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

#include "GLTexture.hp"

ostream&
GLTexture::ostreamPrint(ostream& inOut) const
{
    inOut << "source " << FiletypeName() << " '" << Filename() << "'";
    inOut << " images=" << m_textureDefs.size();
    for (TextureRef i=0; i<m_textureDefs.size(); ++i)
    {
        inOut << "[image " << i << ":";
        inOut << " width=" << Width(i);
        inOut << " height=" << Height(i);
        inOut << " pixelFormat=" << PixelFormat(i);
        inOut << " pixelType=" << PixelType(i);
        inOut << " dataPtr=" << DataPtr(i) << "] ";
    }
    return inOut;
}

