/*
 * $Id: GLTextureRef.h,v 1.2 2002/06/04 17:02:24 southa Exp $
 * $Log: GLTextureRef.h,v $
 * Revision 1.2  2002/06/04 17:02:24  southa
 * More work
 *
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
    GLTextureRef(const string& inName): m_name(inName), m_texPtr(NULL) {}
    void NameSet(const string& inName) {m_name=inName;m_texPtr=NULL;}
    const string& NameGet(void) const {return m_name;}
    GLTexture *TextureGet(void) const;
    bool Exists(void) const;
    
private:
    void GetReference(void) const;

    string m_name;
    mutable GLTexture *m_texPtr;
};
