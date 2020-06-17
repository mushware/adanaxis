//%includeGuardStart {
#ifndef GLRENDERABLE_H
#define GLRENDERABLE_H
//%includeGuardStart } pJbPZlQpqi1UWUnA/ssrzg
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLRenderable.h
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
//%Header } CmsYeONKAA6pMLvWDGwJ3A
/*
 * $Id: GLRenderable.h,v 1.14 2006/06/01 15:38:52 southa Exp $
 * $Log: GLRenderable.h,v $
 * Revision 1.14  2006/06/01 15:38:52  southa
 * DrawArray verification and fixes
 *
 * Revision 1.13  2005/05/19 13:01:59  southa
 * Mac release work
 *
 * Revision 1.12  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.11  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.10  2003/10/04 15:32:08  southa
 * Module split
 *
 * Revision 1.9  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:08:27  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.6  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/27 08:56:20  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/09 17:09:02  southa
 * InfernalDialogue added
 *
 * Revision 1.2  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/18 11:40:34  southa
 * Overplotting and movement
 *
 */

#include "mushMushcore.h"

class GLRenderable
{
public:
    virtual ~GLRenderable() {}
    virtual void Render(void) const = 0;
    virtual GLRenderable *Clone(void) const = 0;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
