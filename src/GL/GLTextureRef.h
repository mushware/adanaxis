/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class GLTexture;

class GLTextureRef
{
public:
    GLTextureRef(): m_texPtr(NULL) {}
    GLTextureRef(const string& inName): m_texPtr(NULL), m_name(inName) {}
    GLTexture *TextureGet(void);
    bool Exists(void);
    
private:
    void GetReference(void);

    GLTexture *m_texPtr;
    string m_name;
};
