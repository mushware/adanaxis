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
 * $Id: MushGLStandard.h,v 1.3 2004/09/27 22:42:09 southa Exp $
 * $Log: MushGLStandard.h,v $
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
#endif

#ifdef HAVE_GL_GLEXT_H
#include <GL/glext.h>
#endif

#ifdef HAVE_OPENGL_GLEXT_H
#include <OpenGL/glext.h>
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
