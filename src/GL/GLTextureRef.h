#ifndef GLTEXTUREREF_H
#define GLTEXTUREREF_H
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
 * $Id: GLTextureRef.h,v 1.4 2002/06/27 12:36:05 southa Exp $
 * $Log: GLTextureRef.h,v $
 * Revision 1.4  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.3  2002/06/04 20:29:43  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
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
#endif
