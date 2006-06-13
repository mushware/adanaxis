//%includeGuardStart {
#ifndef MUSHRUBYDATAOBJ_H
#define MUSHRUBYDATAOBJ_H
//%includeGuardStart } qu93FosdnZjYHSH+RA7pXA
//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyDataObj.h
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
//%Header } px78SUrna42uj+15fa2T7w
/*
 * $Id$
 * $Log$
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

protected:
	static tDataObjRef& DataObjRef(Mushware::tRubyValue inSelf);
	static tDataObjBase& DataObjBase(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue DataObjKlass(void) { return m_dataObjKlass; }
	static Mushware::tRubyValue DataObjAllocate(Mushware::tRubyValue inKlass);		
	static Mushware::tRubyValue DataObj_to_s(Mushware::tRubyValue inSelf);
	static void DataObjInstall(const std::string &inName);
	
private:
	static void DataObjFree(void *inPtr);			
	
	static Mushware::tRubyValue m_dataObjKlass;	
};

#define MUSHRUBYDATAOBJ_INSTANCE(T) \
template <> Mushware::tRubyValue MushRubyDataObj<T>::m_dataObjKlass = MushRuby::QNil

template <class T>
void
MushRubyDataObj<T>::DataObjFree(void *inPtr)
{
	tDataObjRef *pRef = reinterpret_cast<tDataObjRef *>(inPtr);
	MUSHCOREASSERT(pRef != NULL);
	delete pRef;
}

template <class T>
Mushware::tRubyValue
MushRubyDataObj<T>::DataObjAllocate(Mushware::tRubyValue inKlass)
{
	return MushRubyUtil::DataWrapStruct(inKlass, 0, DataObjFree, new tDataObjRef);
}

template <class T>
typename MushRubyDataObj<T>::tDataObjRef&
MushRubyDataObj<T>::DataObjRef(Mushware::tRubyValue inSelf)
{
	tDataObjRef *pRetVal = reinterpret_cast<tDataObjRef *>(MushRubyUtil::DataGetStruct(inSelf));
	MUSHCOREASSERT(pRetVal != NULL);
	return *pRetVal;
}

template <class T>
typename MushRubyDataObj<T>::tDataObjBase&
MushRubyDataObj<T>::DataObjBase(Mushware::tRubyValue inSelf)
{
	return DataObjRef(inSelf).WRef();
}

template <class T>
const typename MushRubyDataObj<T>::tDataObjBase&
MushRubyDataObj<T>::Ref(Mushware::tRubyValue inSelf)
{
	MushRubyUtil::RaiseUnlessInstanceOf(inSelf, m_dataObjKlass);
	return DataObjBase(inSelf);
}

template <class T>
typename MushRubyDataObj<T>::tDataObjBase&
MushRubyDataObj<T>::WRef(Mushware::tRubyValue inSelf)
{
	MushRubyUtil::RaiseUnlessInstanceOf(inSelf, m_dataObjKlass);
	return DataObjBase(inSelf);
}

template <class T>
Mushware::tRubyValue
MushRubyDataObj<T>::DataObj_to_s(Mushware::tRubyValue inSelf)
{
	std::ostringstream objStream;
	objStream << DataObjBase(inSelf);
	
	return MushRubyUtil::StringNew(objStream.str());
}

template <class T>
void
MushRubyDataObj<T>::DataObjInstall(const std::string &inName)
{
	m_dataObjKlass = MushRubyUtil::AllocatedClassDefine(inName, DataObjAllocate);
	MushRubyUtil::MethodDefineNoParams(DataObjKlass(), "to_s", DataObj_to_s);
}


//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
