#ifndef GLSTANDARD_H
#define GLSTANDARD_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GLStandard.h,v 1.11 2003/01/09 14:56:58 southa Exp $
 * $Log: GLStandard.h,v $
 * Revision 1.11  2003/01/09 14:56:58  southa
 * Created Mushcore
 *
 * Revision 1.10  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/27 08:56:20  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.6  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.5  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.4  2002/05/30 16:20:53  southa
 * Pickleable GameContract
 *
 * Revision 1.3  2002/05/28 16:37:39  southa
 * Texture references and decomposer
 *
 * Revision 1.2  2002/05/24 18:10:43  southa
 * MushcoreXML and game map
 *
 * Revision 1.1  2002/05/10 16:41:43  southa
 * Changed .hp files to .h
 *
 * Revision 1.9  2002/05/08 16:31:21  southa
 * Created API directory
 *
 * Revision 1.8  2002/02/25 23:05:14  southa
 * Subclassed GLTexture
 *
 * Revision 1.7  2002/02/24 23:40:53  southa
 * Tweaked for MacOS X
 *
 * Revision 1.6  2002/02/24 22:49:33  southa
 * Got working under cygwin
 *
 * Revision 1.5  2002/02/23 23:58:45  southa
 * Made buildable for cygwin
 *
 * Revision 1.4  2002/02/23 11:43:36  southa
 * Added AutoMonkey
 *
 * Revision 1.3  2002/02/18 22:43:53  southa
 * First stage GIF loader
 *
 * Revision 1.2  2002/02/18 22:04:37  southa
 * Initial texture loading
 *
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
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


#include "Mushcore.h"

#define GLTESTING(a) a
#endif
