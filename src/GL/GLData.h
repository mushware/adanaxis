/*
 * $Id: GLData.h,v 1.6 2002/03/21 22:07:54 southa Exp $
 * $Log: GLData.h,v $
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
#include "GLTexture.h"

class GLData
{
public:
    ~GLData();
    static GLData& Instance(void) {return *((m_instance==NULL)?m_instance=new GLData:m_instance);}
    TextureRef AddTexture(const GLTexture& inTexture);
    GLTexture& GetTexture(const TextureRef& inRef);
    
private:
    vector<GLTexture *> m_textures;

    static GLData *m_instance;
};
