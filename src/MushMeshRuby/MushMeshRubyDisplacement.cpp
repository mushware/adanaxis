//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyDisplacement.cpp
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
//%Header } r4uJt7qAeGRBys+BB5eEWg
/*
 * $Id$
 * $Log$
 */

#include "MushMeshRubyDisplacement.h"

#include "MushMeshRubyRuby.h"

using namespace Mushware;
using namespace std;

Mushware::tRubyValue MushMeshRubyDisplacement::m_DisplacementKlass = Qnil;

void
MushMeshRubyDisplacement::MushDisplacementFree(void *inPtr)
{
	delete reinterpret_cast<MushMeshDisplacement *>(inPtr);
}

Mushware::tRubyValue
MushMeshRubyDisplacement::MushDisplacementAllocate(Mushware::tRubyValue inKlass)
{
	return Data_Wrap_Struct(inKlass, 0, MushDisplacementFree, new MushMeshDisplacement);
}


MushMeshDisplacement&
MushMeshRubyDisplacement::RefObj(Mushware::tRubyValue inSelf)
{
	MushMeshDisplacement *pValue = NULL;
	Data_Get_Struct(inSelf, MushMeshDisplacement, pValue);
	MUSHCOREASSERT(pValue != NULL);
	return *pValue;
}

Mushware::tRubyValue
MushMeshRubyDisplacement::MushDisplacementInitialize(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	try
	{
	}
	catch (MushcoreFail& e)
	{
		MushRubyUtil::Raise(e.what());
	}
	return inSelf;
}

Mushware::tRubyValue
MushMeshRubyDisplacement::MushDisplacementInitializeCopy(Mushware::tRubyValue inCopy, Mushware::tRubyValue inOrig)
{
	if (inCopy != inOrig)
	{
		if (MushRubyUtil::SameDataType(inCopy, inOrig))
		{
		    RefObj(inCopy) = RefObj(inOrig);
		}
		else
		{
			MushRubyUtil::Raise("Cannot copy to MushDisplacement from different type");
		}
	}
    return inCopy;
}

Mushware::tRubyValue
MushMeshRubyDisplacement::MushDisplacement_to_s(Mushware::tRubyValue inSelf)
{
	std::ostringstream objStream;
	objStream << RefObj(inSelf);
	
	return rb_str_new(objStream.str().data(), objStream.str().size());
}

void
MushMeshRubyDisplacement::RubyInstall(void)
{
	m_DisplacementKlass = MushRubyUtil::AllocatedClassDefine("MushDisplacement", MushDisplacementAllocate);
	
	MushRubyUtil::MethodDefine(m_DisplacementKlass, "initialize", MushDisplacementInitialize);
	MushRubyUtil::MethodDefineOneParam(m_DisplacementKlass, "initialize_copy", MushDisplacementInitializeCopy);
	MushRubyUtil::MethodDefineNoParams(m_DisplacementKlass, "to_s", MushDisplacement_to_s);
}

namespace
{
	void Install(void)
	{
		MushRubyInstall::Sgl().Add(MushMeshRubyDisplacement::RubyInstall);
	}
	MushcoreInstaller install(Install);
}
