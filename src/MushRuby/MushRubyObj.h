//%includeGuardStart {
#ifndef MUSHRUBYOBJ_H
#define MUSHRUBYOBJ_H
//%includeGuardStart } AxkUiiJ29gGdqHhTttNxMg
//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyObj.h
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
//%Header } kjx6juFzwsH41luLhCyMIQ
/*
 * $Id: MushRubyObj.h,v 1.3 2006/06/14 18:45:50 southa Exp $
 * $Log: MushRubyObj.h,v $
 * Revision 1.3  2006/06/14 18:45:50  southa
 * Ruby mesh generation
 *
 * Revision 1.2  2006/06/14 11:20:09  southa
 * Ruby mesh generation
 *
 * Revision 1.1  2006/06/13 19:30:39  southa
 * Ruby mesh generation
 *
 */

#include "MushRubyStandard.h"
#include "MushRubyUtil.h"

template <class T>
class MushRubyObj
{
public:
	static const T& Ref(Mushware::tRubyValue inSelf);
	static T& WRef(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue NewInstance(void) { return MushRubyUtil::ClassNewInstance(ObjKlass()); }
	static bool IsInstanceOf(Mushware::tRubyValue inValue);
	static bool IsInstanceOf(MushRubyValue inValue) { return IsInstanceOf(inValue.Value()); }
	
protected:
	static T& ObjRef(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue ObjKlass(void) { return m_objKlass; }
	static Mushware::tRubyValue ObjAllocate(Mushware::tRubyValue inKlass);		
	static Mushware::tRubyValue Obj_to_s(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue Obj_to_xml(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue ObjInitialize(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue ObjInitializeCopy(Mushware::tRubyValue inCopy, Mushware::tRubyValue inOrig);
	static void MethodsInstall(void);
	static void ObjInstall(const std::string &inName);
	static void ObjInstallSubclass(const std::string &inName, const std::string& inSuperclass);

	// Initialize must be overriden to permit object creation
	static Mushware::tRubyValue Initialize(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf);

private:
	static void ObjFree(void *inPtr);			
	
	static Mushware::tRubyValue m_objKlass;	
};

#define MUSHRUBYOBJ_INSTANCE(T) \
template <> Mushware::tRubyValue MushRubyObj<T>::m_objKlass = MushRuby::QNil

#define MUSHRUBYOBJ_INITIALIZE(T) \
template <> \
Mushware::tRubyValue \
MushRubyObj<T>::Initialize

template <class T>
void
MushRubyObj<T>::ObjFree(void *inPtr)
{
	T *pRef = reinterpret_cast<T *>(inPtr);
	MUSHCOREASSERT(pRef != NULL);
	delete pRef;
}

template <class T>
Mushware::tRubyValue
MushRubyObj<T>::ObjAllocate(Mushware::tRubyValue inKlass)
{
	return MushRubyUtil::DataWrapStruct(inKlass, 0, ObjFree, new T);
}

template <class T>
T&
MushRubyObj<T>::ObjRef(Mushware::tRubyValue inSelf)
{
	T *pRetVal = reinterpret_cast<T *>(MushRubyUtil::DataGetStruct(inSelf));
	MUSHCOREASSERT(pRetVal != NULL);
	return *pRetVal;
}

template <class T>
const T&
MushRubyObj<T>::Ref(Mushware::tRubyValue inSelf)
{
	MushRubyUtil::RaiseUnlessInstanceOf(inSelf, m_objKlass);
	return ObjRef(inSelf);
}

template <class T>
T&
MushRubyObj<T>::WRef(Mushware::tRubyValue inSelf)
{
	MushRubyUtil::RaiseUnlessInstanceOf(inSelf, m_objKlass);
	return ObjRef(inSelf);
}

template <class T>
bool
MushRubyObj<T>::IsInstanceOf(Mushware::tRubyValue inValue)
{
	return MushRubyUtil::IsInstanceOf(inValue, m_objKlass);
}

template <class T>
Mushware::tRubyValue
MushRubyObj<T>::Initialize(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	throw MushcoreLogicFail("MushRubyObj::Initialize must be overriden by derived class to permit object creation");
}

template <class T>
Mushware::tRubyValue
MushRubyObj<T>::ObjInitialize(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	Mushware::tRubyValue retVal;
	try
	{
		retVal = Initialize(inArgC, inpArgV, inSelf);
	}
	catch (MushcoreFail& e)
	{
		MushRubyUtil::Raise(e.what());
	}
	return retVal;
}

template <class T>
Mushware::tRubyValue
MushRubyObj<T>::ObjInitializeCopy(Mushware::tRubyValue inCopy, Mushware::tRubyValue inOrig)
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
Mushware::tRubyValue
MushRubyObj<T>::Obj_to_s(Mushware::tRubyValue inSelf)
{
	std::ostringstream objStream;
	objStream << ObjRef(inSelf);
	
	return MushRubyUtil::StringNew(objStream.str());
}


template <class T>
Mushware::tRubyValue
MushRubyObj<T>::Obj_to_xml(Mushware::tRubyValue inSelf)
{
	std::ostringstream objStream;
	MushcoreXMLOStream xmlStream(objStream);
	xmlStream << ObjRef(inSelf);
	
	return MushRubyUtil::StringNew(objStream.str());
}


template <class T>
void
MushRubyObj<T>::MethodsInstall(void)
{
	MushRubyUtil::MethodDefine(ObjKlass(), "initialize", ObjInitialize);
	MushRubyUtil::MethodDefineOneParam(ObjKlass(), "initialize_copy", ObjInitializeCopy);
	MushRubyUtil::MethodDefineNoParams(ObjKlass(), "to_s", Obj_to_s);
	MushRubyUtil::MethodDefineNoParams(ObjKlass(), "to_xml", Obj_to_xml);
}

template <class T>
void
MushRubyObj<T>::ObjInstall(const std::string &inName)
{
	m_objKlass = MushRubyUtil::AllocatedClassDefine(inName, ObjAllocate);
	MethodsInstall();
}

template <class T>
void
MushRubyObj<T>::ObjInstallSubclass(const std::string &inName, const std::string &inSubclass)
{
	m_objKlass = MushRubyUtil::AllocatedSubclassDefine(inName, inSubclass, ObjAllocate);
	MethodsInstall();
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
