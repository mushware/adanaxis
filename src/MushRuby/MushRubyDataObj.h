//%includeGuardStart {
#ifndef MUSHRUBYDATAOBJ_H
#define MUSHRUBYDATAOBJ_H
//%includeGuardStart } qu93FosdnZjYHSH+RA7pXA
//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyDataObj.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } VUlHUwrEIuX5ja7ZLgY+xA
/*
 * $Id: MushRubyDataObj.h,v 1.7 2006/07/02 09:43:28 southa Exp $
 * $Log: MushRubyDataObj.h,v $
 * Revision 1.7  2006/07/02 09:43:28  southa
 * MushGLFont work
 *
 * Revision 1.6  2006/06/27 11:58:10  southa
 * Warning fixes
 *
 * Revision 1.5  2006/06/16 12:11:05  southa
 * Ruby subclasses
 *
 * Revision 1.4  2006/06/14 18:45:50  southa
 * Ruby mesh generation
 *
 * Revision 1.3  2006/06/14 11:20:09  southa
 * Ruby mesh generation
 *
 * Revision 1.2  2006/06/13 19:30:39  southa
 * Ruby mesh generation
 *
 * Revision 1.1  2006/06/13 10:35:05  southa
 * Ruby data objects
 *
 */

#include "MushRubyStandard.h"
#include "MushRubyUtil.h"

template <class T>
class MushRubyDataObj
{
public:
	typedef T tDataObjBase;
	typedef MushcoreData<T> tDataObjData;
	typedef MushcoreDataRef<T> tDataObjRef;
	
	static const tDataObjBase& Ref(Mushware::tRubyValue inSelf);
	static tDataObjBase& WRef(Mushware::tRubyValue inSelf);
	static bool IsInstanceOf(Mushware::tRubyValue inValue);
	static bool IsInstanceOf(MushRubyValue inValue) { return IsInstanceOf(inValue.Value()); }
	static Mushware::tRubyValue Klass(void);
	static void RubyInstall(void) {} // Override this

protected:
	static tDataObjRef& DataObjRef(Mushware::tRubyValue inSelf);
	static tDataObjBase& DataObjBase(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue DataObjKlass(void) { return m_rubyKlass; }
	static Mushware::tRubyValue DataObjAllocate(Mushware::tRubyValue inKlass);		
	static Mushware::tRubyValue DataObjInitialize(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue DataObjInitializeCopy(Mushware::tRubyValue inCopy, Mushware::tRubyValue inOrig);
	static Mushware::tRubyValue DataObj_to_s(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue DataObj_to_xml(Mushware::tRubyValue inSelf);
	static void DataObjMethodsInstall(void);
	static void DataObjInstall(const std::string &inName);
	static void DataObjInstallSubclass(const std::string &inName, Mushware::tRubyValue inSuperclass);
	
	// Initialize must be overriden to permit object creation
	static Mushware::tRubyValue Initialize(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf);
	
private:
	static void DataObjFree(void *inPtr);			
	
	static Mushware::tRubyValue m_rubyKlass;	
};

#define MUSHRUBYDATAOBJ_INSTANCE(T) \
template <> Mushware::tRubyValue MushRubyDataObj<T>::m_rubyKlass = Mushware::kRubyQnil

#define MUSHRUBYDATAOBJ_INITIALIZE(T) \
template <> \
Mushware::tRubyValue \
MushRubyDataObj<T>::Initialize

#define MUSHRUBYDATAOBJ_INSTALL(D) \
template <> \
inline void \
MushRubyDataObj<D>::RubyInstall

template <class T>
inline void
MushRubyDataObj<T>::DataObjFree(void *inPtr)
{
	tDataObjRef *pRef = reinterpret_cast<tDataObjRef *>(inPtr);
	MUSHCOREASSERT(pRef != NULL);
	delete pRef;
}

template <class T>
inline Mushware::tRubyValue
MushRubyDataObj<T>::DataObjAllocate(Mushware::tRubyValue inKlass)
{
	return MushRubyUtil::DataWrapStruct(inKlass, 0, DataObjFree, new tDataObjRef);
}

template <class T>
inline typename MushRubyDataObj<T>::tDataObjRef&
MushRubyDataObj<T>::DataObjRef(Mushware::tRubyValue inSelf)
{
	tDataObjRef *pRetVal = reinterpret_cast<tDataObjRef *>(MushRubyUtil::DataGetStruct(inSelf));
	MUSHCOREASSERT(pRetVal != NULL);
	return *pRetVal;
}

template <class T>
inline typename MushRubyDataObj<T>::tDataObjBase&
MushRubyDataObj<T>::DataObjBase(Mushware::tRubyValue inSelf)
{
	return DataObjRef(inSelf).WRef();
}

template <class T>
inline const typename MushRubyDataObj<T>::tDataObjBase&
MushRubyDataObj<T>::Ref(Mushware::tRubyValue inSelf)
{
	MushRubyUtil::RaiseUnlessInstanceOf(inSelf, m_rubyKlass);
	return DataObjBase(inSelf);
}

template <class T>
inline typename MushRubyDataObj<T>::tDataObjBase&
MushRubyDataObj<T>::WRef(Mushware::tRubyValue inSelf)
{
	MushRubyUtil::RaiseUnlessInstanceOf(inSelf, m_rubyKlass);
	return DataObjBase(inSelf);
}

template <class T>
inline bool
MushRubyDataObj<T>::IsInstanceOf(Mushware::tRubyValue inValue)
{
	return MushRubyUtil::IsInstanceOf(inValue, m_rubyKlass);
}

template <class T>
inline Mushware::tRubyValue
MushRubyDataObj<T>::Klass(void)
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
MushRubyDataObj<T>::Initialize(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	throw MushcoreLogicFail("MushRubyDataObj::Initialize must be overriden by derived class to permit object creation");
}

template <class T>
inline Mushware::tRubyValue
MushRubyDataObj<T>::DataObjInitialize(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
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
MushRubyDataObj<T>::DataObjInitializeCopy(Mushware::tRubyValue inCopy, Mushware::tRubyValue inOrig)
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
MushRubyDataObj<T>::DataObj_to_s(Mushware::tRubyValue inSelf)
{
	std::ostringstream objStream;
	objStream << DataObjBase(inSelf);
	
	return MushRubyUtil::StringNew(objStream.str());
}

template <class T>
inline Mushware::tRubyValue
MushRubyDataObj<T>::DataObj_to_xml(Mushware::tRubyValue inSelf)
{
	std::ostringstream objStream;
	MushcoreXMLOStream xmlStream(objStream);
	xmlStream << DataObjBase(inSelf);
	
	return MushRubyUtil::StringNew(objStream.str());
}

template <class T>
inline void
MushRubyDataObj<T>::DataObjMethodsInstall(void)
{
	MushRubyUtil::MethodDefine(DataObjKlass(), "initialize", DataObjInitialize);
	MushRubyUtil::MethodDefineOneParam(DataObjKlass(), "initialize_copy", DataObjInitializeCopy);
	MushRubyUtil::MethodDefineNoParams(DataObjKlass(), "to_s", DataObj_to_s);
	MushRubyUtil::MethodDefineNoParams(DataObjKlass(), "to_xml", DataObj_to_xml);
}

template <class T>
inline void
MushRubyDataObj<T>::DataObjInstall(const std::string &inName)
{
	if (m_rubyKlass == Mushware::kRubyQnil)
	{
		m_rubyKlass = MushRubyUtil::AllocatedClassDefine(inName, DataObjAllocate);
		DataObjMethodsInstall();
	}
}

template <class T>
inline void
MushRubyDataObj<T>::DataObjInstallSubclass(const std::string &inName, Mushware::tRubyValue inSuperclass)
{
	if (m_rubyKlass == Mushware::kRubyQnil)
	{
		m_rubyKlass = MushRubyUtil::AllocatedSubclassDefine(inName, inSuperclass, DataObjAllocate);
		DataObjMethodsInstall();
	}
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
