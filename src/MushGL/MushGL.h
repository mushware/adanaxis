//%includeGuardStart {
#ifndef MUSHGL_H
#define MUSHGL_H
//%includeGuardStart } sZMkMkP9fHs6SjzxXh/O8Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGL.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } o5cuLcuspQyDjT/B7gRW8w
/*
 * $Id: MushGL.h,v 1.17 2006/09/07 16:38:50 southa Exp $
 * $Log: MushGL.h,v $
 * Revision 1.17  2006/09/07 16:38:50  southa
 * Vertex shader
 *
 * Revision 1.16  2006/07/24 18:46:48  southa
 * Depth sorting
 *
 * Revision 1.15  2006/06/30 15:05:32  southa
 * Texture and buffer purge
 *
 * Revision 1.14  2006/06/29 08:27:08  southa
 * X11 fixes
 *
 * Revision 1.13  2006/06/05 11:48:24  southa
 * Noise textures
 *
 * Revision 1.12  2006/06/01 15:39:16  southa
 * DrawArray verification and fixes
 *
 * Revision 1.11  2006/04/11 23:30:08  southa
 * Created MushRuby from ruby-1.8.4
 *
 * Revision 1.10  2005/09/05 12:54:30  southa
 * Solid rendering work
 *
 * Revision 1.9  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 * Revision 1.8  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 * Revision 1.7  2005/07/01 10:03:30  southa
 * Projection work
 *
 * Revision 1.6  2005/05/19 13:02:09  southa
 * Mac release work
 *
 * Revision 1.5  2005/02/13 22:44:07  southa
 * Tesseract stuff
 *
 * Revision 1.4  2005/02/01 13:40:37  southa
 * Rotating spheres and hypercube
 *
 * Revision 1.3  2005/01/29 14:06:12  southa
 * OpenGL buffers and extensions
 *
 * Revision 1.2  2004/09/20 21:50:47  southa
 * Added GLV
 *
 * Revision 1.1  2004/03/07 12:05:56  southa
 * Rendering work
 *
 */

#include "MushGLAppHandler.h"
#include "MushGLArrays.h"
#include "MushGLAttribs.h"
#include "MushGLBuffers.h"
#include "MushGLCacheControl.h"
#include "MushGLCamera.h"
#include "MushGLClaimer.h"
#include "MushGLControl.h"
#include "MushGLDraw.h"
#include "MushGLFont.h"
#include "MushGLJob.h"
#include "MushGLJobRender.h"
#include "MushGLMaterial.h"
#include "MushGLPixelSource.h"
// #include "MushGLPixelSourceTIFF.h"
#include "MushGLProjection.h"
#include "MushGLResolverPixelSource.h"
#include "MushGLStandard.h"
#include "MushGLState.h"
#include "MushGLTexture.h"
#include "MushGLUtil.h"
#include "MushGLTIFFUtil.h"
#include "MushGLV.h"
#include "MushGLVertexBuffer.h"
#include "MushGLWorkSpec.h"
#include "MushGLWorkspace.h"

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
