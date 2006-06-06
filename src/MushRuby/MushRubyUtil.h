//%includeGuardStart {
#ifndef MUSHRUBYUTIL_H
#define MUSHRUBYUTIL_H
//%includeGuardStart } jBAo8cJeJ0/8vlN9kxlgfA
//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyUtil.h
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
//%Header } ZnwDjEM1+TPkZ9HrL5mg7A
/*
 * $Id: MushRubyUtil.h,v 1.3 2006/06/06 10:29:51 southa Exp $
 * $Log: MushRubyUtil.h,v $
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


#include "MushRubyStandard.h"

#include "MushRubyValue.h"

class MushRubyUtil
{
public:
	static Mushware::tRubyID Intern(const std::string& inName);
    static void ValueConvert(std::string& outString, Mushware::tRubyValue inValue);
    static void ValueConvert(Mushware::tVal& outVal, Mushware::tRubyValue inValue);
    static Mushware::tRubyValue ParamPop(Mushware::tRubyArgC& ioArgC, Mushware::tRubyValue *& ioArgV);
    static void IVGet(Mushware::tVal& outVal, const std::string& inName, Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue Class(const std::string& inName);
    static Mushware::tRubyValue ClassDefine(const std::string& inName);
    static void MethodDefine(Mushware::tRubyValue inKlass, const std::string& inName,
                             Mushware::tfpRubyMethod infpMethod);
    static void SingletonMethodDefine(Mushware::tRubyValue inKlass, const std::string& inName,
                             Mushware::tfpRubyMethod infpMethod);
	static void HashConvert(Mushware::tRubyHash& outHash, const MushRubyValue& inHash);
	static void Raise(const std::string& inStr);
	
private:
	static Mushware::tRubyValue HashHandler(Mushware::tRubyValue inArray, Mushware::tRubyValue inArg);

	// Static variable - not thread safe
	static Mushware::tRubyHash *m_pHash;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
