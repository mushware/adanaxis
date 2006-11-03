//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyUtil.cpp
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
//%Header } gSaMBKSS/9FVf/ypP8x5kA
/*
 * $Id: MushRubyUtil.cpp,v 1.17 2006/10/12 22:04:49 southa Exp $
 * $Log: MushRubyUtil.cpp,v $
 * Revision 1.17  2006/10/12 22:04:49  southa
 * Collision events
 *
 * Revision 1.16  2006/10/04 13:35:25  southa
 * Selective targetting
 *
 * Revision 1.15  2006/10/02 20:28:11  southa
 * Object lookup and target selection
 *
 * Revision 1.14  2006/08/20 14:19:23  southa
 * Seek operation
 *
 * Revision 1.13  2006/08/19 09:12:10  southa
 * Event handling
 *
 * Revision 1.12  2006/08/17 08:57:13  southa
 * Event handling
 *
 * Revision 1.11  2006/06/16 12:11:06  southa
 * Ruby subclasses
 *
 * Revision 1.10  2006/06/16 01:02:33  southa
 * Ruby mesh generation
 *
 * Revision 1.9  2006/06/14 11:20:09  southa
 * Ruby mesh generation
 *
 * Revision 1.8  2006/06/13 19:30:39  southa
 * Ruby mesh generation
 *
 * Revision 1.7  2006/06/13 10:35:06  southa
 * Ruby data objects
 *
 * Revision 1.6  2006/06/12 16:01:24  southa
 * Ruby mesh generation
 *
 * Revision 1.5  2006/06/12 11:59:40  southa
 * Ruby wrapper for MushMeshVector
 *
 * Revision 1.4  2006/06/06 17:58:33  southa
 * Ruby texture definition
 *
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

#include "MushRubyUtil.h"

#include "MushRubyFail.h"
#include "MushRubyIntern.h"
#include "MushRubyRuby.h"
#include "MushRubySTL.h"
#include "MushRubyValue.h"

using namespace Mushware;
using namespace std;

Mushware::tRubyHash *MushRubyUtil::m_pHash = NULL;

void
MushRubyUtil::IVGet(Mushware::tVal& outVal, const std::string& inName, Mushware::tRubyValue inSelf)
{
    tRubyValue rubyValue = rb_iv_get(inSelf, inName.c_str());
    outVal = NUM2DBL(rubyValue);
}

Mushware::tRubyValue
MushRubyUtil::ParamPop(Mushware::tRubyArgC& ioArgC, Mushware::tRubyValue *& ioArgV)
{
    if (ioArgC < 1)
    {
        throw MushRubyFail("Not enough arguments");
    }
    
    tRubyValue retVal = *ioArgV;
    ++ioArgC;
    ++ioArgV;
    
    return retVal;
}

void
MushRubyUtil::ValueConvert(std::string& outString, Mushware::tRubyValue inValue)
{
    tRubyValue stringValue = StringValue(inValue);
    
    outString = std::string(RSTRING(stringValue)->ptr, RSTRING(stringValue)->ptr + RSTRING(stringValue)->len);
}

void
MushRubyUtil::ValueConvert(Mushware::tVal& outVal, Mushware::tRubyValue inValue)
{
    outVal = NUM2DBL(inValue);
}

Mushware::tRubyValue
MushRubyUtil::Class(const std::string& inName)
{
    tRubyValue klass = rb_const_get(rb_cObject, rb_intern(inName.c_str()));
    return klass;
}

Mushware::tRubyValue
MushRubyUtil::ClassDefine(const std::string& inName)
{
    tRubyValue klass = rb_define_class(inName.c_str(), rb_cObject);
    return klass;
}

Mushware::tRubyValue
MushRubyUtil::SubclassDefine(const std::string& inName, Mushware::tRubyValue  inSuperclass)
{
    tRubyValue klass = rb_define_class(inName.c_str(), inSuperclass);
    return klass;
}

Mushware::tRubyValue
MushRubyUtil::AllocatedClassDefine(const std::string& inName, Mushware::tfpRubyAllocFunc inAllocFunc)
{
    tRubyValue klass = ClassDefine(inName);
	rb_define_alloc_func(klass, inAllocFunc);
    return klass;
}

Mushware::tRubyValue
MushRubyUtil::AllocatedSubclassDefine(const std::string& inName, Mushware::tRubyValue inSuperclass, Mushware::tfpRubyAllocFunc inAllocFunc)
{
    tRubyValue klass = SubclassDefine(inName, inSuperclass);
	rb_define_alloc_func(klass, inAllocFunc);
    return klass;
}

void
MushRubyUtil::MethodDefine(Mushware::tRubyValue inKlass, const std::string& inName,
						   tfpRubyMethod infpMethod)
{
    rb_define_method(inKlass, inName.c_str(), RUBY_METHOD_FUNC(infpMethod), -1);
}

void
MushRubyUtil::MethodDefineNoParams(Mushware::tRubyValue inKlass, const std::string& inName,
						           Mushware::tfpRubyMethodNoParams infpMethod)
{
    rb_define_method(inKlass, inName.c_str(), RUBY_METHOD_FUNC(infpMethod), 0);
}

void
MushRubyUtil::MethodDefineOneParam(Mushware::tRubyValue inKlass, const std::string& inName,
						           Mushware::tfpRubyMethodOneParam infpMethod)
{
    rb_define_method(inKlass, inName.c_str(), RUBY_METHOD_FUNC(infpMethod), 1);
}

void
MushRubyUtil::MethodDefineTwoParams(Mushware::tRubyValue inKlass, const std::string& inName,
									 Mushware::tfpRubyMethodTwoParams infpMethod)
{
    rb_define_method(inKlass, inName.c_str(), RUBY_METHOD_FUNC(infpMethod), 2);
}

void
MushRubyUtil::MethodDefineThreeParams(Mushware::tRubyValue inKlass, const std::string& inName,
									 Mushware::tfpRubyMethodThreeParams infpMethod)
{
    rb_define_method(inKlass, inName.c_str(), RUBY_METHOD_FUNC(infpMethod), 3);
}

void
MushRubyUtil::MethodDefineFourParams(Mushware::tRubyValue inKlass, const std::string& inName,
									 Mushware::tfpRubyMethodFourParams infpMethod)
{
    rb_define_method(inKlass, inName.c_str(), RUBY_METHOD_FUNC(infpMethod), 4);
}

void
MushRubyUtil::SingletonMethodDefine(Mushware::tRubyValue inKlass, const std::string& inName,
									tfpRubyMethod infpMethod)
{
    rb_define_singleton_method(inKlass, inName.c_str(), RUBY_METHOD_FUNC(infpMethod), -1);
}

void
MushRubyUtil::SingletonMethodDefineNoParams(Mushware::tRubyValue inKlass, const std::string& inName,
									tfpRubyMethodNoParams infpMethod)
{
    rb_define_singleton_method(inKlass, inName.c_str(), RUBY_METHOD_FUNC(infpMethod), 0);
}

void
MushRubyUtil::SingletonMethodDefineOneParam(Mushware::tRubyValue inKlass, const std::string& inName,
											   tfpRubyMethodOneParam infpMethod)
{
    rb_define_singleton_method(inKlass, inName.c_str(), RUBY_METHOD_FUNC(infpMethod), 1);
}

void
MushRubyUtil::SingletonMethodDefineTwoParams(Mushware::tRubyValue inKlass, const std::string& inName,
											   tfpRubyMethodTwoParams infpMethod)
{
    rb_define_singleton_method(inKlass, inName.c_str(), RUBY_METHOD_FUNC(infpMethod), 2);
}

void
MushRubyUtil::SingletonMethodDefineThreeParams(Mushware::tRubyValue inKlass, const std::string& inName,
											   tfpRubyMethodThreeParams infpMethod)
{
    rb_define_singleton_method(inKlass, inName.c_str(), RUBY_METHOD_FUNC(infpMethod), 3);
}

void
MushRubyUtil::SingletonMethodDefineFourParams(Mushware::tRubyValue inKlass, const std::string& inName,
											   tfpRubyMethodFourParams infpMethod)
{
    rb_define_singleton_method(inKlass, inName.c_str(), RUBY_METHOD_FUNC(infpMethod), 2);
}

Mushware::tRubyValue
MushRubyUtil::HashHandler(Mushware::tRubyValue inArray, Mushware::tRubyValue inArg)
{
	MUSHCOREASSERT(m_pHash != NULL);
    MushRubyValue keyValue(rb_ary_entry(inArray, 0));
    MushRubyValue hashValue(rb_ary_entry(inArray, 1));
	(*m_pHash)[keyValue] = hashValue;
	return Qtrue;
}

void
MushRubyUtil::HashConvert(Mushware::tRubyHash& outHash, Mushware::tRubyValue inHash)
{
	m_pHash = &outHash;
	rb_iterate(rb_each, inHash, RUBY_METHOD_FUNC(HashHandler), Qnil);
	m_pHash = NULL;
}

void
MushRubyUtil::HashConvert(Mushware::tRubyHash& outHash, const MushRubyValue& inHash)
{
	HashConvert(outHash, inHash.Value());
}

void
MushRubyUtil::Raise(const std::string& inStr)
{
	rb_raise(rb_eException, "%s", inStr.c_str());
}

bool
MushRubyUtil::SameDataType(Mushware::tRubyValue inA, Mushware::tRubyValue inB)
{
    return (TYPE(inA) == T_DATA &&
			TYPE(inB) == T_DATA &&
			RDATA(inA)->dfree == RDATA(inB)->dfree);
}

bool
MushRubyUtil::IsInstanceOf(Mushware::tRubyValue inValue, Mushware::tRubyID inKlass)
{
	return rb_obj_is_instance_of(inValue, inKlass);
}

void
MushRubyUtil::RaiseUnlessInstanceOf(Mushware::tRubyValue inValue, Mushware::tRubyValue inKlass)
{
	if (!IsInstanceOf(inValue, inKlass))
	{
		Raise("Object is of wrong type");	
	}
}

Mushware::tRubyValue
MushRubyUtil::DataWrapStruct(Mushware::tRubyValue inSelf, tfpRubyDataFunc infpMark, tfpRubyDataFunc infpFree, void *inpData)
{
	// Use ruby macro
	return Data_Wrap_Struct(inSelf, infpMark, infpFree, inpData);	
}

void *
MushRubyUtil::DataGetStruct(Mushware::tRubyValue inSelf)
{
	void *pRetVal;
	Data_Get_Struct(inSelf, void, pRetVal);
	return pRetVal;
}

Mushware::tRubyValue
MushRubyUtil::StringNew(const std::string& inStr)
{
    return rb_str_new(inStr.data(), inStr.size());
}

Mushware::tRubyValue
MushRubyUtil::ClassNewInstance(Mushware::tRubyValue inValue)
{
    return rb_class_new_instance(0, 0, inValue);
}

MushRubyValue
MushRubyUtil::ClassNewInstance(const MushRubyValue& inValue)
{
    return MushRubyValue(rb_class_new_instance(0, 0, inValue.Value()));
}

Mushware::tRubyValue
MushRubyUtil::DataObjectWrapNew(const MushRubyValue& inKlass, const MushRubyValue& inSelf, void *inpData)
{
    tRubyValue dataObj = Data_Wrap_Struct(rb_cData, NULL, NULL, inpData);
    rb_ivar_set(inSelf.Value(), MushRubyIntern::AT_embeddedDataPtr(), dataObj);
    return dataObj;
}

void *
MushRubyUtil::DataObjectRetrieve(Mushware::tRubyValue inSelf)
{
 	void *pRetVal;
    tRubyValue dataValue = rb_ivar_get(inSelf, MushRubyIntern::AT_embeddedDataPtr());
	Data_Get_Struct(dataValue, void, pRetVal);
	return pRetVal;   
}


Mushware::tRubyValue
MushRubyUtil::InstanceVar(Mushware::tRubyValue inObj, Mushware::tRubyID inSym)
{
    return rb_ivar_get(inObj, inSym);
}

void
MushRubyUtil::InstanceVarSet(Mushware::tRubyValue inObj, Mushware::tRubyID inSym, Mushware::tRubyValue inValue)
{
    rb_ivar_set(inObj, inSym, inValue);
}

void
MushRubyUtil::Freeze(Mushware::tRubyValue& ioValue)
{
    OBJ_FREEZE(ioValue);
}

void
MushRubyUtil::HashValueSet(Mushware::tRubyValue inHash, Mushware::tRubyValue inKey, Mushware::tRubyValue inValue)
{
    if (!rb_obj_is_instance_of(inHash, rb_cHash))
	{
		throw MushRubyFail("Cannot set hash element in non-hash type");
	}
    rb_hash_aset(inHash, inKey, inValue);
}

Mushware::tRubyValue
MushRubyUtil::SymbolToValue(Mushware::tRubyID inSymbol)
{
	return ID2SYM(inSymbol);
}

MushRubyValue
MushRubyUtil::GlobalVar(const std::string& inName)
{
    return MushRubyValue(rb_gv_get(inName.c_str()));
}

void
MushRubyUtil::ArrayPush(const MushRubyValue& inArray, const MushRubyValue& inValue)
{
    rb_ary_push(inArray.Value(), inValue.Value());
}

