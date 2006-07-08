//%includeGuardStart {
#ifndef MUSHGLRUBYFONT_H
#define MUSHGLRUBYFONT_H
//%includeGuardStart } 1GMUTvU/NnOZUKRVoEDxkQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLRubyFont.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } 73do2LMm7sjCSuxgk8yjpQ
/*
 * $Id: MushGLRubyFont.h,v 1.1 2006/07/02 21:08:55 southa Exp $
 * $Log: MushGLRubyFont.h,v $
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
private:
};

MUSHRUBYDATAOBJ_INSTALL(MushGLFont)(void)
{
	DataObjInstall("MushGLFont");
    MushRubyUtil::MethodDefineOneParam(Klass(), "mRender", MushGLRubyFont::Render);
    MushRubyUtil::MethodDefineThreeParams(Klass(), "mRenderAt", MushGLRubyFont::RenderAt);
    MushRubyUtil::MethodDefineFourParams(Klass(), "mRenderAtSize", MushGLRubyFont::RenderAtSize);
    MushRubyUtil::MethodDefineOneParam(Klass(), "colour=", MushGLRubyFont::ColourEquals);
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
