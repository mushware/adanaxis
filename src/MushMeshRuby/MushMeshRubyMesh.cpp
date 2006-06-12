//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyMesh.cpp
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
//%Header } oR7WPhSKmfGQldTVFg6TpQ
/*
 * $Id$
 * $Log$
 */

#include "MushMeshRubyMesh.h"

#include "MushMeshRubyRuby.h"

using namespace Mushware;
using namespace std;

Mushware::tRubyValue MushMeshRubyMesh::m_meshKlass = Qnil;

void
MushMeshRubyMesh::MushMeshFree(void *inPtr)
{
	delete reinterpret_cast<tContainer *>(inPtr);
}

Mushware::tRubyValue
MushMeshRubyMesh::MushMeshAllocate(Mushware::tRubyValue inKlass)
{
	return Data_Wrap_Struct(inKlass, 0, MushMeshFree, new tContainer);
}

MushMeshRubyMesh::tContainer&
MushMeshRubyMesh::ContainerObj(Mushware::tRubyValue inSelf)
{
	tContainer *pValue = NULL;
	Data_Get_Struct(inSelf, tContainer, pValue);
	MUSHCOREASSERT(pValue != NULL);
	return *pValue;
}

MushMeshRubyMesh::tBase&
MushMeshRubyMesh::RefObj(Mushware::tRubyValue inSelf)
{
	tContainer *pValue = NULL;
	Data_Get_Struct(inSelf, tContainer, pValue);
	MUSHCOREASSERT(pValue != NULL);
	return pValue->WRef();
}

MushMeshRubyMesh::tBase&
MushMeshRubyMesh::Ref(Mushware::tRubyValue inSelf)
{
	MushRubyUtil::RaiseUnlessInstanceOf(inSelf, m_meshKlass);
	return RefObj(inSelf);
}

Mushware::tRubyValue
MushMeshRubyMesh::MushMeshInitialize(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	try
	{
		if (inArgC != 1)
		{
			MushRubyUtil::Raise("MushMesh constructor requires one parameter <mesh name>");
		}
		MushRubyValue nameValue(inpArgV[0]);
		std::string nameStr = nameValue.String();
		ContainerObj(inSelf).NameSet(nameStr);
		MushcoreData<tBase>::Sgl().GetOrCreate(nameStr); // Create mesh if it doesn't exist
	}
	catch (MushcoreFail& e)
	{
		MushRubyUtil::Raise(e.what());
	}
	return inSelf;
}

Mushware::tRubyValue
MushMeshRubyMesh::MushMeshInitializeCopy(Mushware::tRubyValue inCopy, Mushware::tRubyValue inOrig)
{
	if (inCopy != inOrig)
	{
		MushRubyUtil::Raise("Cannot clone or dup MushMesh");
	}
    return inCopy;
}

Mushware::tRubyValue
MushMeshRubyMesh::MushMesh_to_s(Mushware::tRubyValue inSelf)
{
	std::ostringstream objStream;
	objStream << RefObj(inSelf);
	
	return rb_str_new(objStream.str().data(), objStream.str().size());
}

void
MushMeshRubyMesh::RubyInstall(void)
{
	m_meshKlass = MushRubyUtil::AllocatedClassDefine("MushMesh", MushMeshAllocate);
	
	MushRubyUtil::MethodDefine(m_meshKlass, "initialize", MushMeshInitialize);
	MushRubyUtil::MethodDefineOneParam(m_meshKlass, "initialize_copy", MushMeshInitializeCopy);
	MushRubyUtil::MethodDefineNoParams(m_meshKlass, "to_s", MushMesh_to_s);
}

namespace
{
	void Install(void)
	{
		MushRubyInstall::Sgl().Add(MushMeshRubyMesh::RubyInstall);
	}
	MushcoreInstaller install(Install);
}
