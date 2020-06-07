//%includeGuardStart {
#ifndef MUSHGLSTANDARD_H
#define MUSHGLSTANDARD_H
//%includeGuardStart } 530hg+5QgQr4Ah8xWJUplg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLStandard.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } 90oRy1maQWnypU6Mcy9v2w
/*
 * $Id: MushGLStandard.h,v 1.18 2006/09/07 10:02:37 southa Exp $
 * $Log: MushGLStandard.h,v $
 * Revision 1.18  2006/09/07 10:02:37  southa
 * Shader interface
 *
 * Revision 1.17  2006/06/29 10:12:34  southa
 * 64 bit compatibility fixes
 *
 * Revision 1.16  2006/06/23 00:35:05  southa
 * win32 build fixes
 *
 * Revision 1.15  2006/06/22 19:07:31  southa
 * Build fixes
 *
 * Revision 1.14  2006/06/16 12:11:03  southa
 * Ruby subclasses
 *
 * Revision 1.13  2006/06/01 20:12:59  southa
 * Initial texture caching
 *
 * Revision 1.12  2006/06/01 15:39:18  southa
 * DrawArray verification and fixes
 *
 * Revision 1.11  2005/09/06 12:15:35  southa
 * Texture and rendering work
 *
 * Revision 1.10  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 * Revision 1.9  2005/05/27 19:25:24  southa
 * win32 build fixes
 *
 * Revision 1.8  2005/05/27 12:48:37  southa
 * Registration box tweaks
 *
 * Revision 1.7  2005/05/26 00:46:40  southa
 * Made buildable on win32
 *
 * Revision 1.6  2005/05/19 13:02:09  southa
 * Mac release work
 *
 * Revision 1.5  2005/01/29 18:27:31  southa
 * Vertex buffer stuff
 *
 * Revision 1.4  2004/10/31 23:34:06  southa
 * Hypercube rendering test
 *
 * Revision 1.3  2004/09/27 22:42:09  southa
 * MSVC compilation fixes
 *
 * Revision 1.2  2004/09/20 21:50:47  southa
 * Added GLV
 *
 * Revision 1.1  2004/03/07 12:05:56  southa
 * Rendering work
 *
 */

#if defined(HAVE_CONFIG_H)  && !defined(MUSHWARE_CONFIG_H)
#define MUSHWARE_CONFIG_H 1
#include "config.h"
#endif

#if defined(HAVE_WINDOWS_H) || defined (_MSC_VER)
#define NOMINMAX
#include <windows.h>
#endif

#ifdef _MSC_VER
#undef HAVE_SDL_OPENGL_H
#define HAVE_SDL_OPENGL_H 1
#endif

#if defined(__APPLE__) || defined(MACOSX)
#undef HAVE_OPENGL_GL_H
#undef HAVE_OPENGL_GLU_H
#undef HAVE_SDL_SDL_OPENGL_H
#define HAVE_OPENGL_GL_H 1
#define HAVE_OPENGL_GLU_H 1
#define HAVE_SDL_SDL_OPENGL_H 1
#endif

#ifdef HAVE_GL_GL_H
#include <GL/gl.h>
#elif defined(HAVE_OPENGL_GL_H)
#include <OpenGL/gl.h>
#else
#include "GL/gl.h"
#endif

#ifdef HAVE_GL_GLU_H
#include <GL/glu.h>
#elif defined(HAVE_OPENGL_GLU_H)
#include <OpenGL/glu.h>
#else
#include "GL/glu.h"
#endif

#ifndef GL_GLEXT_VERSION

#if defined(HAVE_SDL_SDL_OPENGL_H)
#include <SDL/SDL_opengl.h>
#elif defined(HAVE_SDL_OPENGL_H)
#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>
#elif defined(HAVE_OPENGL_GLEXTL_H)
#include <OpenGL/glext.h>
#elif defined(HAVE_GL_GLEXTL_H)
#include <GL/glext.h>
#else
#include "SDL_opengl.h"
#include "SDL_opengl_glext.h"
#endif

#endif

#ifndef GL_VERSION_1_5
#include <stddef.h>
#include <memory.h>

#define GL_ARRAY_BUFFER            0x8892
#define GL_ELEMENT_ARRAY_BUFFER    0x8893
#define GL_READ_ONLY               0x88B8
#define GL_WRITE_ONLY              0x88B9
#define GL_READ_WRITE              0x88BA
#define GL_BUFFER_ACCESS           0x88BB
#define GL_BUFFER_MAPPED           0x88BC
#define GL_BUFFER_MAP_POINTER      0x88BD
#define GL_STREAM_DRAW             0x88E0
#define GL_STREAM_READ             0x88E1
#define GL_STREAM_COPY             0x88E2
#define GL_STATIC_DRAW             0x88E4
#define GL_STATIC_READ             0x88E5
#define GL_STATIC_COPY             0x88E6
#define GL_DYNAMIC_DRAW            0x88E8
#define GL_DYNAMIC_READ            0x88E9
#define GL_DYNAMIC_COPY            0x88EA
#define GL_SAMPLES_PASSED          0x8914

typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;
#endif

#include "API/mushMushcore.h"
#include "API/mushMushcoreIO.h"
#include "API/mushMushcoreSTL.h"
#include "API/mushMushMesh.h"
 
#include <cmath>

namespace Mushware
{
     typedef GLfloat tGLVal;
     typedef MushMeshVector<Mushware::tGLVal, 2> t2GLVal;
     typedef MushMeshVector<Mushware::tGLVal, 3> t3GLVal;
     typedef MushMeshVector<Mushware::tGLVal, 4> t4GLVal;
     typedef t2GLVal tGLTexCoord;
     typedef GLhandleARB GLHandle;
     typedef GLcharARB GLChar;
     extern const GLHandle kGLHandleNull;
}

#define MUSHGL_VALTYPE GL_FLOAT

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
