//%includeGuardStart {
#ifndef GLTEXTUREPROC_H
#define GLTEXTUREPROC_H
//%includeGuardStart } h07cy255ooQoRIKB503C5Q
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTextureProc.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } STWarMslvBQGreBRIFcL6w
/*
 * $Id: GLTextureTIFF.h,v 1.11 2004/01/02 21:13:06 southa Exp $
 * $Log: GLTextureTIFF.h,v $
 */

#include "GLTexture.h"

#include "mushMushGL.h"

class GLTextureProc : public GLTexture
{
public:
    GLTextureProc(const MushGLPixelSource& inSource);
    GLTextureProc *Clone(void) const {return new GLTextureProc(*this);}
    
protected:
        
private:
    const char *FiletypeName(void) const;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
