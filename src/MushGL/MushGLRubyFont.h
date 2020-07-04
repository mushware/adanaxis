//%includeGuardStart {
#ifndef MUSHGLRUBYFONT_H
#define MUSHGLRUBYFONT_H
//%includeGuardStart } 1GMUTvU/NnOZUKRVoEDxkQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLRubyFont.h
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
//%Header } bb+a3UO2TaKnCNr7MgAq3w
/*
 * $Id: MushGLRubyFont.h,v 1.3 2006/10/17 20:43:01 southa Exp $
 * $Log: MushGLRubyFont.h,v $
 * Revision 1.3  2006/10/17 20:43:01  southa
 * Dashboard work
 *
 * Revision 1.2  2006/07/08 16:05:58  southa
 * Ruby menus and key handling
 *
 * Revision 1.1  2006/07/02 21:08:55  southa
 * Ruby menu work
 *
 */

#include "MushGLStandard.h"

#include "MushGLFont.h"

#include "API/mushMushRuby.h"

class MushGLRubyFont : public MushRubyDataObj<MushGLFont>
{
public:
    static Mushware::tRubyValue Render(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue RenderAt(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0,
                                         Mushware::tRubyValue inArg1, Mushware::tRubyValue inArg2);
    static Mushware::tRubyValue RenderAtSize(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0,
        Mushware::tRubyValue inArg1, Mushware::tRubyValue inArg2, Mushware::tRubyValue inArg3);
    static Mushware::tRubyValue ColourEquals(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue RenderSymbolAtSize(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0,
        Mushware::tRubyValue inArg1, Mushware::tRubyValue inArg2, Mushware::tRubyValue inArg3);
    
private:
};

MUSHRUBYDATAOBJ_INSTALL(MushGLFont)(void)
{
	DataObjInstall("MushGLFont");
    MushRubyUtil::MethodDefineOneParam(Klass(), "mRender", MushGLRubyFont::Render);
    MushRubyUtil::MethodDefineThreeParams(Klass(), "mRenderAt", MushGLRubyFont::RenderAt);
    MushRubyUtil::MethodDefineFourParams(Klass(), "mRenderAtSize", MushGLRubyFont::RenderAtSize);
    MushRubyUtil::MethodDefineFourParams(Klass(), "mRenderSymbolAtSize", MushGLRubyFont::RenderSymbolAtSize);
    MushRubyUtil::MethodDefineOneParam(Klass(), "colour=", MushGLRubyFont::ColourEquals);
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
