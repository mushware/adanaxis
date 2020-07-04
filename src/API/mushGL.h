//%includeGuardStart {
// Edited to avoid clash with MushGL/MushGL.h
#ifndef API_MUSHGL_H
#define API_MUSHGL_H
//%includeGuardStart } sZMkMkP9fHs6SjzxXh/O8Q
//%Header {
/*****************************************************************************
 *
 * File: src/API/mushGL.h
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
//%Header } +0+WMPZASyYTqHj6iSkWQw
/*
 * $Id: mushGL.h,v 1.30 2006/06/01 15:38:44 southa Exp $
 * $Log: mushGL.h,v $
 * Revision 1.30  2006/06/01 15:38:44  southa
 * DrawArray verification and fixes
 *
 * Revision 1.29  2005/05/19 13:01:56  southa
 * Mac release work
 *
 * Revision 1.28  2005/02/13 22:44:06  southa
 * Tesseract stuff
 *
 * Revision 1.27  2005/02/10 12:33:55  southa
 * Template fixes
 *
 * Revision 1.26  2004/09/27 22:42:08  southa
 * MSVC compilation fixes
 *
 * Revision 1.25  2004/03/07 12:05:56  southa
 * Rendering work
 *
 * Revision 1.24  2004/01/10 20:29:33  southa
 * Form and rendering work
 *
 * Revision 1.23  2004/01/02 21:13:04  southa
 * Source conditioning
 *
 * Revision 1.22  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.21  2003/08/21 23:08:16  southa
 * Fixed file headers
 *
 * Revision 1.20  2002/12/20 13:17:30  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.19  2002/11/18 11:31:13  southa
 * Return to game mode
 *
 * Revision 1.18  2002/10/22 20:41:56  southa
 * Source conditioning
 *
 * Revision 1.17  2002/10/14 18:13:17  southa
 * GLModeDef work
 *
 * Revision 1.16  2002/10/12 15:24:57  southa
 * Facet renderer
 *
 * Revision 1.15  2002/10/12 11:22:20  southa
 * GraphicModel work
 *
 * Revision 1.14  2002/10/06 22:09:58  southa
 * Initial lighting test
 *
 * Revision 1.13  2002/08/27 08:56:15  southa
 * Source conditioning
 *
 * Revision 1.12  2002/08/08 13:39:09  southa
 * Text rendering
 *
 * Revision 1.11  2002/08/07 13:36:43  southa
 * Conditioned source
 *
 * Revision 1.10  2002/07/18 11:40:34  southa
 * Overplotting and movement
 *
 * Revision 1.9  2002/07/16 17:48:07  southa
 * Collision and optimisation work
 *
 * Revision 1.8  2002/07/06 18:04:14  southa
 * More designer work
 *
 * Revision 1.7  2002/07/02 18:36:56  southa
 * Selection in designer, mouse buttons
 *
 * Revision 1.6  2002/07/02 15:48:29  southa
 * Floor std::map designer
 *
 * Revision 1.5  2002/06/27 12:36:01  southa
 * Build process fixes
 *
 * Revision 1.4  2002/06/20 15:50:29  southa
 * Subclassed GLAppHandler
 *
 * Revision 1.3  2002/05/28 16:37:36  southa
 * Texture references and decomposer
 *
 * Revision 1.2  2002/05/10 22:38:23  southa
 * Checkpoint
 *
 * Revision 1.1  2002/05/10 16:39:34  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/05/08 16:31:23  southa
 * Created API directory
 *
 */

#include "GL/GLAppHandler.h"
#include "GL/GLAppSignal.h"
#include "GL/GLArray.h"
#include "GL/GLColour.h"
#include "GL/GLData.h"
#include "GL/GLLightDef.h"
#include "GL/GLLights.h"
#include "GL/GLLine.h"
#include "GL/GLModeDef.h"
#include "GL/GLPoint.h"
#include "GL/GLQuad.h"
#include "GL/GLRectangle.h"
#include "GL/GLRender.h"
#include "GL/GLRenderable.h"
#include "GL/GLStandard.h"
#include "GL/GLString.h"
#include "GL/GLTexture.h"
#include "GL/GLTextureProc.h"
#include "GL/GLTextureRef.h"
#include "GL/GLUtils.h"
#include "GL/GLXMLOperators.h"
#include "GL/SDLAppHandler.h"

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
