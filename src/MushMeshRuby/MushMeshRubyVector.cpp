//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyVector.cpp
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
//%Header } 0xPG/7jmGTzjaD0AmAZyzw
/*
 * $Id$
 * $Log$
 */

#include "MushMeshRubyVector.h"

#include "MushMeshRubyRuby.h"

using namespace Mushware;
using namespace std;

Mushware::tRubyValue MushMeshRubyVector::m_t4ValKlass = Qnil;

void
MushMeshRubyVector::Mush4ValFree(void *inPtr)
{
	delete reinterpret_cast<Mushware::t4Val *>(inPtr);
}

Mushware::tRubyValue
MushMeshRubyVector::Mush4ValAllocate(Mushware::tRubyValue inKlass)
{
	return Data_Wrap_Struct(inKlass, 0, Mush4ValFree, new Mushware::t4Val);
}


Mushware::t4Val&
MushMeshRubyVector::Reft4Val(Mushware::tRubyValue inSelf)
{
	Mushware::t4Val *pVal = NULL;
	Data_Get_Struct(inSelf, Mushware::t4Val, pVal);
	MUSHCOREASSERT(pVal != NULL);
	return *pVal;
}

Mushware::tRubyValue
MushMeshRubyVector::Mush4ValInitialize(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	try
	{
		if (inArgC == 0)
		{
			// Leave uninitialised	
		}
		else if (inArgC == 1)
		{
			MushRubyValue param0(inpArgV[0]);
			Reft4Val(inSelf) = t4Val(param0.ValVector());
		}
		else if (inArgC == 4)
		{
			MushRubyValue param0(inpArgV[0]);
			MushRubyValue param1(inpArgV[1]);
			MushRubyValue param2(inpArgV[2]);
			MushRubyValue param3(inpArgV[3]);
			
			Reft4Val(inSelf) = t4Val(param0.Val(), param1.Val(), param2.Val(), param3.Val());
		}
		else
		{
			MushRubyUtil::Raise("Wrong number of parameters to Mush4Val.intialise (must be 0, 1 array or 4 values)");	
		}
	}
	catch (MushcoreFail& e)
	{
			MushRubyUtil::Raise(e.what());
	}
	return inSelf;
}

Mushware::tRubyValue
MushMeshRubyVector::Mush4ValInitializeCopy(Mushware::tRubyValue inCopy, Mushware::tRubyValue inOrig)
{
	if (inCopy != inOrig)
	{
		if (MushRubyUtil::SameDataType(inCopy, inOrig))
		{
		    Reft4Val(inCopy) = Reft4Val(inOrig);
		}
		else
		{
			MushRubyUtil::Raise("Cannot copy to Mush4Val from different type");
		}
	}
    return inCopy;
}

Mushware::tRubyValue
MushMeshRubyVector::Mush4Val_to_s(Mushware::tRubyValue inSelf)
{
	std::ostringstream objStream;
	objStream << Reft4Val(inSelf);
	
	return rb_str_new(objStream.str().data(), objStream.str().size());
}

Mushware::tRubyValue
MushMeshRubyVector::Mush4ValInPlaceAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1)
{
	Reft4Val(inSelf) += Reft4Val(inArg1);
	
	return inSelf;
}

Mushware::tRubyValue
MushMeshRubyVector::Mush4ValAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1)
{
	tRubyValue retVal = rb_class_new_instance(0, 0, m_t4ValKlass);
    Reft4Val(retVal) = Reft4Val(inSelf);
	Mush4ValInPlaceAdd(retVal, inArg1);
	
	return retVal;
}

Mushware::tRubyValue
MushMeshRubyVector::Mush4ValIsEqual(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1)
{
	tRubyValue retVal;
	if (Reft4Val(inSelf) == Reft4Val(inArg1))
	{
		retVal = MushRuby::QTrue;	
	}
	else
	{
		retVal = MushRuby::QFalse;	
	}
	return retVal;
}

void
MushMeshRubyVector::RubyInstall(void)
{
	m_t4ValKlass = MushRubyUtil::AllocatedClassDefine("Mush4Val", Mush4ValAllocate);
	
	MushRubyUtil::MethodDefine(m_t4ValKlass, "initialize", Mush4ValInitialize);
	MushRubyUtil::MethodDefineOneParam(m_t4ValKlass, "initialize_copy", Mush4ValInitializeCopy);
	MushRubyUtil::MethodDefineNoParams(m_t4ValKlass, "to_s", Mush4Val_to_s);
	MushRubyUtil::MethodDefineOneParam(m_t4ValKlass, "+=", Mush4ValInPlaceAdd);
	MushRubyUtil::MethodDefineOneParam(m_t4ValKlass, "+", Mush4ValAdd);
	MushRubyUtil::MethodDefineOneParam(m_t4ValKlass, "==", Mush4ValIsEqual);
}

namespace
{
	void Install(void)
	{
		MushRubyInstall::Sgl().Add(MushMeshRubyVector::RubyInstall);
	}
	MushcoreInstaller install(Install);
}
