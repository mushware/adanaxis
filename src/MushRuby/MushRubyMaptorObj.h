//%includeGuardStart {
#ifndef MUSHRUBYMAPTOROBJ_H
#define MUSHRUBYMAPTOROBJ_H
//%includeGuardStart } 42RBOxF3mBmiO2XA/1oDFQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyMaptorObj.h
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
//%Header } 9mcda8lQ7WxjuBRVzY0OGw
/*
 * $Id: MushRubyMaptorObj.h,v 1.3 2006/06/27 11:58:10 southa Exp $
 * $Log: MushRubyMaptorObj.h,v $
 * Revision 1.3  2006/06/27 11:58:10  southa
 * Warning fixes
 *
 * Revision 1.2  2006/06/26 17:03:14  southa
 * win32 installer tweaks
 *
 * Revision 1.1  2006/06/20 19:06:55  southa
 * Object creation
 *
 */


#include "MushRubyStandard.h"
#include "MushRubyUtil.h"

template <class T>
class MushRubyMaptorObj
{
public:
	typedef T tMaptorObjBase;
	typedef MushcoreMaptor<T> tMaptorObjData;
	typedef MushcoreMaptorRef<T> tMaptorObjRef;
	
	static const tMaptorObjBase& Ref(Mushware::tRubyValue inSelf);
	static tMaptorObjBase& WRef(Mushware::tRubyValue inSelf);
	static bool IsInstanceOf(Mushware::tRubyValue inValue);
	static bool IsInstanceOf(MushRubyValue inValue) { return IsInstanceOf(inValue.Value()); }
	static Mushware::tRubyValue Klass(void);
	static void RubyInstall(void) {} // Override this

protected:
	static tMaptorObjRef& MaptorObjRef(Mushware::tRubyValue inSelf);
	static tMaptorObjBase& MaptorObjBase(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue MaptorObjKlass(void) { return m_rubyKlass; }
	static Mushware::tRubyValue MaptorObjAllocate(Mushware::tRubyValue inKlass);		
	static Mushware::tRubyValue MaptorObjInitialize(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue MaptorObjInitializeCopy(Mushware::tRubyValue inCopy, Mushware::tRubyValue inOrig);
	static Mushware::tRubyValue MaptorObj_to_s(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue MaptorObj_to_xml(Mushware::tRubyValue inSelf);
	static void MaptorObjMethodsInstall(void);
	static void MaptorObjInstall(const std::string &inName);
	static void MaptorObjInstallSubclass(const std::string &inName, Mushware::tRubyValue inSuperclass);
	
	// Initialize must be overriden to permit object creation
	static Mushware::tRubyValue Initialize(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf);
	
private:
	static void MaptorObjFree(void *inPtr);			
	
	static Mushware::tRubyValue m_rubyKlass;	
};

#define MUSHRUBYMAPTOROBJ_INSTANCE(T) \
template <> Mushware::tRubyValue MushRubyMaptorObj<T>::m_rubyKlass = Mushware::kRubyQnil

#define MUSHRUBYMAPTOROBJ_INITIALIZE(T) \
template <> \
Mushware::tRubyValue \
MushRubyMaptorObj<T>::Initialize

template <class T>
inline void
MushRubyMaptorObj<T>::MaptorObjFree(void *inPtr)
{
	tMaptorObjRef *pRef = reinterpret_cast<tMaptorObjRef *>(inPtr);
	MUSHCOREASSERT(pRef != NULL);
	delete pRef;
}

template <class T>
inline Mushware::tRubyValue
MushRubyMaptorObj<T>::MaptorObjAllocate(Mushware::tRubyValue inKlass)
{
	return MushRubyUtil::DataWrapStruct(inKlass, 0, MaptorObjFree, new tMaptorObjRef);
}

template <class T>
inline typename MushRubyMaptorObj<T>::tMaptorObjRef&
MushRubyMaptorObj<T>::MaptorObjRef(Mushware::tRubyValue inSelf)
{
	tMaptorObjRef *pRetVal = reinterpret_cast<tMaptorObjRef *>(MushRubyUtil::DataGetStruct(inSelf));
	MUSHCOREASSERT(pRetVal != NULL);
	return *pRetVal;
}

template <class T>
inline typename MushRubyMaptorObj<T>::tMaptorObjBase&
MushRubyMaptorObj<T>::MaptorObjBase(Mushware::tRubyValue inSelf)
{
	return *MaptorObjRef(inSelf);
}

template <class T>
inline const typename MushRubyMaptorObj<T>::tMaptorObjBase&
MushRubyMaptorObj<T>::Ref(Mushware::tRubyValue inSelf)
{
	MushRubyUtil::RaiseUnlessInstanceOf(inSelf, m_rubyKlass);
	return MaptorObjBase(inSelf);
}

template <class T>
inline typename MushRubyMaptorObj<T>::tMaptorObjBase&
MushRubyMaptorObj<T>::WRef(Mushware::tRubyValue inSelf)
{
	MushRubyUtil::RaiseUnlessInstanceOf(inSelf, m_rubyKlass);
	return MaptorObjBase(inSelf);
}

template <class T>
inline bool
MushRubyMaptorObj<T>::IsInstanceOf(Mushware::tRubyValue inValue)
{
	return MushRubyUtil::IsInstanceOf(inValue, m_rubyKlass);
}

template <class T>
inline Mushware::tRubyValue
MushRubyMaptorObj<T>::Klass(void)
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

template <class T>
inline Mushware::tRubyValue
MushRubyMaptorObj<T>::Initialize(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	throw MushcoreLogicFail("MushRubyMaptorObj::Initialize must be overriden by derived class to permit object creation");
}

template <class T>
inline Mushware::tRubyValue
MushRubyMaptorObj<T>::MaptorObjInitialize(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	Mushware::tRubyValue retVal;
	try
	{
		retVal = Initialize(inArgC, inpArgV, inSelf);
	}
	catch (MushcoreFail& e)
	{
		MushRubyUtil::Raise(e.what());
        retVal = 0; // Prevent warning
	}
	return retVal;
}

template <class T>
inline Mushware::tRubyValue
MushRubyMaptorObj<T>::MaptorObjInitializeCopy(Mushware::tRubyValue inCopy, Mushware::tRubyValue inOrig)
{
	if (inCopy != inOrig)
	{
		if (MushRubyUtil::SameDataType(inCopy, inOrig))
		{
		    WRef(inCopy) = Ref(inOrig);
		}
		else
		{
			MushRubyUtil::Raise("Cannot copy from different type");
		}
	}
    return inCopy;
}

template <class T>
inline Mushware::tRubyValue
MushRubyMaptorObj<T>::MaptorObj_to_s(Mushware::tRubyValue inSelf)
{
	std::ostringstream objStream;
	objStream << MaptorObjBase(inSelf);
	
	return MushRubyUtil::StringNew(objStream.str());
}

template <class T>
inline Mushware::tRubyValue
MushRubyMaptorObj<T>::MaptorObj_to_xml(Mushware::tRubyValue inSelf)
{
	std::ostringstream objStream;
	MushcoreXMLOStream xmlStream(objStream);
	xmlStream << MaptorObjBase(inSelf);
	
	return MushRubyUtil::StringNew(objStream.str());
}

template <class T>
inline void
MushRubyMaptorObj<T>::MaptorObjMethodsInstall(void)
{
	MushRubyUtil::MethodDefine(MaptorObjKlass(), "initialize", MaptorObjInitialize);
	MushRubyUtil::MethodDefineOneParam(MaptorObjKlass(), "initialize_copy", MaptorObjInitializeCopy);
	MushRubyUtil::MethodDefineNoParams(MaptorObjKlass(), "to_s", MaptorObj_to_s);
	MushRubyUtil::MethodDefineNoParams(MaptorObjKlass(), "to_xml", MaptorObj_to_xml);
}

template <class T>
inline void
MushRubyMaptorObj<T>::MaptorObjInstall(const std::string &inName)
{
	if (m_rubyKlass == Mushware::kRubyQnil)
	{
		m_rubyKlass = MushRubyUtil::AllocatedClassDefine(inName, MaptorObjAllocate);
		MaptorObjMethodsInstall();
	}
}

template <class T>
inline void
MushRubyMaptorObj<T>::MaptorObjInstallSubclass(const std::string &inName, Mushware::tRubyValue inSuperclass)
{
	if (m_rubyKlass == Mushware::kRubyQnil)
	{
		m_rubyKlass = MushRubyUtil::AllocatedSubclassDefine(inName, inSuperclass, MaptorObjAllocate);
		MaptorObjMethodsInstall();
	}
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
