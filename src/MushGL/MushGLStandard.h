//%includeGuardStart {
#ifndef MUSHGLSTANDARD_H
#define MUSHGLSTANDARD_H
//%includeGuardStart } 530hg+5QgQr4Ah8xWJUplg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLStandard.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } JAwZoKzI2b5H44hJsgMLvA
/*
 * $Id: MushGLStandard.h,v 1.4 2004/10/31 23:34:06 southa Exp $
 * $Log: MushGLStandard.h,v $
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
 
#if defined(HAVE_WINDOWS_H) || defined (_MSC_VER)
#include <windows.h>
#endif

#if defined(__APPLE__) || defined(MACOSX)
#define HAVE_OPENGL_GL_H
#define HAVE_OPENGL_GLU_H
#define HAVE_OPENGL_GLEXT_H
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


#ifdef HAVE_GLEXT_H
#include <glext.h>
#elif defined(HAVE_GL_GLEXT_H)
#include <GL/glext.h>
#elif defined(HAVE_OPENGL_GLEXT_H)
#include <OpenGL/glext.h>
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

#include "mushMushcore.h"
#include "mushMushMesh.h"
 
#include <cmath>

namespace Mushware
{
     typedef GLfloat tGLVal;
     typedef MushMeshVector<Mushware::tGLVal, 2> t2GLVal;
     typedef MushMeshVector<Mushware::tGLVal, 3> t3GLVal;
     typedef MushMeshVector<Mushware::tGLVal, 4> t4GLVal;
}

#define MUSHGL_VALTYPE GL_FLOAT
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
