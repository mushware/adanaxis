//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTextureProc.cpp
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
//%Header } yeXGnep1s2Nq0rSrBquM9w
/*
 * $Id: GLTextureProc.cpp,v 1.1 2005/02/13 22:44:06 southa Exp $
 * $Log: GLTextureProc.cpp,v $
 * Revision 1.1  2005/02/13 22:44:06  southa
 * Tesseract stuff
 *
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
