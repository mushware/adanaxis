/*
 * $Id: GLTextureRef.h,v 1.1 2002/05/28 16:37:39 southa Exp $
 * $Log: GLTextureRef.h,v $
 * Revision 1.1  2002/05/28 16:37:39  southa
 * Texture references and decomposer
 *
 */

#include "mushCore.h"

class GLTexture;

class GLTextureRef
{
public:
    GLTextureRef(): m_texPtr(NULL) {}
    GLTextureRef(const string& inName): m_texPtr(NULL), m_name(inName) {}
    void NameSet(const string& inName) {m_name=inName;m_texPtr=NULL;}
    GLTexture *TextureGet(void);
    bool Exists(void);
    
private:
    void GetReference(void);

    GLTexture *m_texPtr;
    string m_name;
};
