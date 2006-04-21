//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLFont.cpp
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
//%Header } Zq+IM0uOYEygMymunhBN6w
/*
 * $Id$
 * $Log$
 */

#include "MushGLFont.h"

#include "mushMushRuby.h"

using namespace Mushware;
using namespace std;

namespace
{
MushcoreInstaller Installer(MushGLFont::Install);
}

tRubyValue
MushGLFont::RubyRender(tRubyArgC inArgC, tRubyValue *inpArgV, tRubyValue inSelf)
{
    tVal fontSize = 0;
    
    MushRubyUtil::IVGet(fontSize, "@fontSize", inSelf);
    
    tVal xPos, yPos;
    std::string textString;
    
    tRubyArgC rubyArgC = inArgC;
    tRubyValue *pRubyArgV = inpArgV;
    
    MushRubyUtil::ValueConvert(xPos, MushRubyUtil::ParamPop(rubyArgC, pRubyArgV));
    MushRubyUtil::ValueConvert(yPos, MushRubyUtil::ParamPop(rubyArgC, pRubyArgV));
    MushRubyUtil::ValueConvert(textString, MushRubyUtil::ParamPop(rubyArgC, pRubyArgV));
    
    cout << "***Render called, fontSize=" << fontSize;
    cout << ", xPos=" << xPos << ", yPos=" << yPos;
    cout << ", textString='" << textString << "'" << endl;
    return 0;
}

void
MushGLFont::RubyInstall(void)
{
    tRubyValue klass = MushRubyUtil::ClassDefine("MushGLFont");
    MushRubyUtil::MethodDefine(klass, "cRender", RubyRender);
}

void
MushGLFont::Install(void)
{
    MushRubyInstall::Sgl().Add(RubyInstall);
}
