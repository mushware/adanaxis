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
 * $Id: MushRubyUtil.cpp,v 1.3 2006/06/06 10:29:51 southa Exp $
 * $Log: MushRubyUtil.cpp,v $
 * Revision 1.3  2006/06/06 10:29:51  southa
 * Ruby texture definitions
 *
 * Revision 1.2  2006/06/05 16:54:44  southa
 * Ruby textures
 *
 * Revision 1.1  2006/04/21 00:10:43  southa
 * MushGLFont ruby module
 *
 */

#include "MushRubyUtil.h"

#include "MushRubyFail.h"
#include "MushRubyRuby.h"
#include "MushRubySTL.h"
#include "MushRubyValue.h"

using namespace Mushware;
using namespace std;

Mushware::tRubyHash *MushRubyUtil::m_pHash = NULL;

Mushware::tRubyID
MushRubyUtil::Intern(const std::string& inName)
{
	tRubyID retID = rb_intern(inName.c_str());
	
	if (retID == Qnil)
	{
		throw MushRubyFail("Unknown internal name '"+inName+"'");
	}
	
	return retID;
}

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

Mushware::tRubyValue
MushRubyUtil::Class(const std::string& inName)
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

void
MushRubyUtil::SingletonMethodDefine(Mushware::tRubyValue inKlass, const std::string& inName,
						   tfpRubyMethod infpMethod)
{
    rb_define_singleton_method(inKlass, inName.c_str(), RUBY_METHOD_FUNC(infpMethod), -1);
}

Mushware::tRubyValue
MushRubyUtil::HashHandler(Mushware::tRubyValue inArray, Mushware::tRubyValue inArg)
{
	MUSHCOREASSERT(m_pHash != NULL);
    MushRubyValue keyValue(rb_ary_entry(inArray, 0));
    MushRubyValue hashValue(rb_ary_entry(inArray, 1));
	(*m_pHash)[keyValue] = hashValue;
	return Qtrue;
}

void
MushRubyUtil::HashConvert(Mushware::tRubyHash& outHash, const MushRubyValue& inHash)
{
	m_pHash = &outHash;
	rb_iterate(rb_each, inHash.Value(), RUBY_METHOD_FUNC(HashHandler), Qnil);
	m_pHash = NULL;
}

void
MushRubyUtil::Raise(const std::string& inStr)
{
	rb_raise(rb_eException, "%s", inStr.c_str());
}
