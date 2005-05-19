//%includeGuardStart {
#ifndef GLTEXTUREPROC_H
#define GLTEXTUREPROC_H
//%includeGuardStart } h07cy255ooQoRIKB503C5Q
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTextureProc.h
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } R9VYvYQhq/zckwVdMTtiXQ
/*
 * $Id: GLTextureProc.h,v 1.1 2005/02/13 22:44:07 southa Exp $
 * $Log: GLTextureProc.h,v $
 * Revision 1.1  2005/02/13 22:44:07  southa
 * Tesseract stuff
 *
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
