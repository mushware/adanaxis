//%includeGuardStart {
#ifndef GLSTANDARD_H
#define GLSTANDARD_H
//%includeGuardStart } 52yady1NYSEbLWZGeNtMgw
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLStandard.h
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
//%Header } myEvJ5AvqY0aHqD9lNyvzA
/*
 * $Id: GLStandard.h,v 1.30 2006/06/29 10:12:33 southa Exp $
 * $Log: GLStandard.h,v $
 * Revision 1.30  2006/06/29 10:12:33  southa
 * 64 bit compatibility fixes
 *
 * Revision 1.29  2006/06/23 00:35:04  southa
 * win32 build fixes
 *
 * Revision 1.28  2006/06/22 19:07:29  southa
 * Build fixes
 *
 * Revision 1.27  2006/06/01 20:12:58  southa
 * Initial texture caching
 *
 * Revision 1.26  2006/06/01 15:38:52  southa
 * DrawArray verification and fixes
 *
 * Revision 1.25  2005/05/27 19:25:24  southa
 * win32 build fixes
 *
 * Revision 1.24  2005/05/26 00:46:40  southa
 * Made buildable on win32
 *
 * Revision 1.23  2005/05/19 13:02:00  southa
 * Mac release work
 *
 * Revision 1.22  2004/10/31 23:34:06  southa
 * Hypercube rendering test
 *
 * Revision 1.21  2004/09/27 22:42:08  southa
 * MSVC compilation fixes
 *
 * Revision 1.20  2004/03/07 12:05:56  southa
 * Rendering work
 *
 * Revision 1.19  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.18  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.17  2003/10/04 12:22:58  southa
 * File renaming
 *
 * Revision 1.16  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.15  2003/08/21 23:08:29  southa
 * Fixed file headers
 *
 * Revision 1.14  2003/01/13 14:31:55  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.13  2003/01/12 17:32:50  southa
 * Mushcore work
 *
 * Revision 1.12  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
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
 * Pickleable InfernalContract
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

#if defined(HAVE_CONFIG_H)  && !defined(MUSHWARE_CONFIG_H)
#define MUSHWARE_CONFIG_H 1
#include "config.h"
#endif

#if defined(HAVE_WINDOWS_H) || defined (_MSC_VER)
#define NOMINMAX
#include <windows.h>
#define HAVE_GLENUM_IS_UNSIGNED_INT 1
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
#elif defined(HAVE_OPENGL_GLEXTL_H)
#include <OpenGL/glext.h>
#elif defined(HAVE_GL_GLEXTL_H)
#include <GL/glext.h>
#else
#include "SDL_opengl.h"
#endif

#endif

#include "mushMushcore.h"

#include <cmath>

#define GLTESTING(a) a

#define TEXTESTING 0
#if TEXTESTING
#define IFTEXTESTING(a) a
#else
#define IFTEXTESTING(a)
#endif

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
