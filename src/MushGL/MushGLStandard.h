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
 * $Id$
 * $Log$
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#define HAVE_GLUT_GLUT_H
#endif
 
#if HAVE_WINDOWS_H
#include <windows.h>
#endif
 
#ifdef HAVE_GL_GLUT_H
#include <GL/glut.h>
#endif
 
#ifdef HAVE_GLUT_GLUT_H
#include <GLUT/glut.h>
#endif
 
#ifdef HAVE_OPENGL_GL_H
#include <OpenGL/gl.h>
#endif
 
#ifdef HAVE_OPENGL_GLU_H
#include <OpenGL/glu.h>
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
