//%includeGuardStart {
#ifndef MUSHRUBYEMPTYOBJ_H
#define MUSHRUBYEMPTYOBJ_H
//%includeGuardStart } zQHXFDrs9jympgLCSjOCDg
//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyEmptyObj.h
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
//%Header } mvF5Pw53hD9vNwfW81pWtg
/*
 * $Id$
 * $Log$
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
