/*
 * $Id: GLStandard.h,v 1.1 2002/05/10 16:41:43 southa Exp $
 * $Log: GLStandard.h,v $
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

#include "mushCore.h"

typedef tSize TextureRef;

#define GLTESTING(a) a
