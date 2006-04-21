//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyUtil.cpp
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
//%Header } gSaMBKSS/9FVf/ypP8x5kA
/*
 * $Id$
 * $Log$
 */

#include "MushRubyUtil.h"

#include "MushRubyFail.h"
#include "MushRubyRuby.h"

using namespace Mushware;
using namespace std;

void
MushRubyUtil::IVGet(Mushware::tVal& outVal, const std::string& inName, Mushware::tRubyValue inSelf)
{
    tRubyValue rubyValue = rb_iv_get(inSelf, inName.c_str());
    outVal = NUM2DBL(rubyValue);
}

Mushware::tRubyValue
MushRubyUtil::ParamPop(Mushware::tRubyArgC& ioArgC, Mushware::tRubyValue *& ioArgV)
{
    if (ioArgC < 1)
    {
        throw MushRubyFail("Not enough arguments");
    }
    
    tRubyValue retVal = *ioArgV;
    ++ioArgC;
    ++ioArgV;
    
    return retVal;
}

void
MushRubyUtil::ValueConvert(std::string& outString, Mushware::tRubyValue inValue)
{
    tRubyValue stringValue = StringValue(inValue);
    
    outString = std::string(RSTRING(stringValue)->ptr, RSTRING(stringValue)->ptr + RSTRING(stringValue)->len);
}

void
MushRubyUtil::ValueConvert(Mushware::tVal& outVal, Mushware::tRubyValue inValue)
{
    outVal = NUM2DBL(inValue);
}

Mushware::tRubyValue
MushRubyUtil::ClassDefine(const std::string& inName)
{
    tRubyValue klass = rb_define_class(inName.c_str(), rb_cObject);
    return klass;
}

void
MushRubyUtil::MethodDefine(Mushware::tRubyValue inKlass, const std::string& inName,
                         tfpRubyMethod infpMethod)
{
    rb_define_method(inKlass, inName.c_str(), RUBY_METHOD_FUNC(infpMethod), -1);
}
