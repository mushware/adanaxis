//%includeGuardStart {
#ifndef MUSHRUBYEMPTYOBJ_H
#define MUSHRUBYEMPTYOBJ_H
//%includeGuardStart } zQHXFDrs9jympgLCSjOCDg
//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyEmptyObj.h
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
//%Header } uacXyKqx3nl4njpH0xdBXg
/*
 * $Id: MushRubyEmptyObj.h,v 1.1 2006/06/16 12:11:05 southa Exp $
 * $Log: MushRubyEmptyObj.h,v $
 * Revision 1.1  2006/06/16 12:11:05  southa
 * Ruby subclasses
 *
 */

#include "MushRubyStandard.h"
#include "MushRubyUtil.h"

template <Mushware::U32 D>
class MushRubyEmptyObj
{
public:
	static Mushware::tRubyValue NewInstance(void) { return MushRubyUtil::ClassNewInstance(EmptyKlass()); }
	static bool IsInstanceOf(Mushware::tRubyValue inValue);
	static bool IsInstanceOf(MushRubyValue inValue) { return IsInstanceOf(inValue.Value()); }
	static bool IsInstalled(void) { return (m_rubyKlass != Mushware::kRubyQnil); }
	static Mushware::tRubyValue Klass(void);
	static void RubyInstall(void); // Override this
	
protected:
	static Mushware::tRubyValue EmptyKlass(void) { return m_rubyKlass; }
	static void EmptyInstall(const std::string &inName);
	static void EmptyInstallSubclass(const std::string &inName, Mushware::tRubyValue inSuperclass);
	
private:	
	static Mushware::tRubyValue m_rubyKlass;	
};

#define MUSHRUBYEMPTYOBJ_INSTANCE(D) \
template <> Mushware::tRubyValue MushRubyEmptyObj<D>::m_rubyKlass = Mushware::kRubyQnil

#define MUSHRUBYEMPTYOBJ_INSTALL(D) \
template <> \
inline void \
MushRubyEmptyObj<D>::RubyInstall

template <Mushware::U32 D>
inline Mushware::tRubyValue
MushRubyEmptyObj<D>::Klass(void)
{
	if (m_rubyKlass == Mushware::kRubyQnil)
	{
		RubyInstall();	
	}
	if (m_rubyKlass == Mushware::kRubyQnil)
	{
		throw MushcoreLogicFail("RubyInstall function not provided for ruby object");
	}
	return m_rubyKlass;
}

template <Mushware::U32 D>
inline void
MushRubyEmptyObj<D>::RubyInstall(void)
{
	std::ostringstream message;
	message << "RubyInstall function not overriden for MushRubyEmptyObj<" << D << ">";
	throw MushcoreLogicFail(message.str());
}

template <Mushware::U32 D>
inline bool
MushRubyEmptyObj<D>::IsInstanceOf(Mushware::tRubyValue inValue)
{
	return MushRubyUtil::IsInstanceOf(inValue, m_rubyKlass);
}

template <Mushware::U32 D>
inline void
MushRubyEmptyObj<D>::EmptyInstall(const std::string &inName)
{
	if (m_rubyKlass == Mushware::kRubyQnil)
	{
		m_rubyKlass = MushRubyUtil::ClassDefine(inName);
	}
}

template <Mushware::U32 D>
inline void
MushRubyEmptyObj<D>::EmptyInstallSubclass(const std::string &inName, Mushware::tRubyValue inSuperclass)
{
	if (m_rubyKlass == Mushware::kRubyQnil)
	{
		m_rubyKlass = MushRubyUtil::SubclassDefine(inName, inSuperclass);
	}
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
