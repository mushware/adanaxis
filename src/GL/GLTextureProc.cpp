//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTextureProc.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } teg57Bwan8Ks0y8STAPUVw
/*
 * $Id: GLTextureTIFF.cpp,v 1.18 2004/01/02 21:13:06 southa Exp $
 * $Log: GLTextureTIFF.cpp,v $
 */

#include "GLTextureProc.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

GLTextureProc::GLTextureProc(const MushGLPixelSource& inSource)
{
    t2U32 size(256,256);
    U32 u32Size = size.X()*size.Y();
    
    // TextureDef takes ownership of the block
    GLTextureDef def(new U32[u32Size]);
    
    def.WidthSet(size.X());
    def.HeightSet(size.Y());
    def.PixelFormatSet(GL_RGBA);
    def.PixelTypeSet(GL_UNSIGNED_BYTE);
    
    inSource.BufferFill(def.DataPtr(), size);
    
    AddTextureDef(def);
}

const char *
GLTextureProc::FiletypeName(void) const
{
    return "Proc";
}
