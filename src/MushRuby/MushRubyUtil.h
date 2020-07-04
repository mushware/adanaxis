//%includeGuardStart {
#ifndef MUSHRUBYUTIL_H
#define MUSHRUBYUTIL_H
//%includeGuardStart } jBAo8cJeJ0/8vlN9kxlgfA
//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyUtil.h
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
//%Header } Gt/gUMeKakFNAfpxmPwqMg
/*
 * $Id: MushRubyUtil.h,v 1.17 2006/11/03 18:46:34 southa Exp $
 * $Log: MushRubyUtil.h,v $
 * Revision 1.17  2006/11/03 18:46:34  southa
 * Damage effectors
 *
 * Revision 1.16  2006/10/12 22:04:49  southa
 * Collision events
 *
 * Revision 1.15  2006/10/04 13:35:25  southa
 * Selective targetting
 *
 * Revision 1.14  2006/10/02 20:28:11  southa
 * Object lookup and target selection
 *
 * Revision 1.13  2006/08/20 14:19:23  southa
 * Seek operation
 *
 * Revision 1.12  2006/08/19 09:12:10  southa
 * Event handling
 *
 * Revision 1.11  2006/06/16 12:11:06  southa
 * Ruby subclasses
 *
 * Revision 1.10  2006/06/16 01:02:34  southa
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


#include "MushRubyStandard.h"

#include "MushRubyValue.h"

class MushRubyUtil
{
public:
    static void ValueConvert(std::string& outString, Mushware::tRubyValue inValue);
    static void ValueConvert(Mushware::tVal& outVal, Mushware::tRubyValue inValue);
    static Mushware::tRubyValue ParamPop(Mushware::tRubyArgC& ioArgC, Mushware::tRubyValue *& ioArgV);
    static void IVGet(Mushware::tVal& outVal, const std::string& inName, Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue Class(const std::string& inName);
    static Mushware::tRubyValue ClassDefine(const std::string& inName);
    static Mushware::tRubyValue SubclassDefine(const std::string& inName, Mushware::tRubyValue inSuperclass);
    static Mushware::tRubyValue AllocatedClassDefine(const std::string& inName, Mushware::tfpRubyAllocFunc inAllocFunc);
    static Mushware::tRubyValue AllocatedSubclassDefine(const std::string& inName, Mushware::tRubyValue inSuperclass, Mushware::tfpRubyAllocFunc inAllocFunc);
    static void MethodDefine(Mushware::tRubyValue inKlass, const std::string& inName,
                             Mushware::tfpRubyMethod infpMethod);
	static void MethodDefineNoParams(Mushware::tRubyValue inKlass, const std::string& inName,
									 Mushware::tfpRubyMethodNoParams infpMethod);
	static void MethodDefineOneParam(Mushware::tRubyValue inKlass, const std::string& inName,
									 Mushware::tfpRubyMethodOneParam infpMethod);
	static void MethodDefineTwoParams(Mushware::tRubyValue inKlass, const std::string& inName,
									   Mushware::tfpRubyMethodTwoParams infpMethod);
	static void MethodDefineThreeParams(Mushware::tRubyValue inKlass, const std::string& inName,
									   Mushware::tfpRubyMethodThreeParams infpMethod);
	static void MethodDefineFourParams(Mushware::tRubyValue inKlass, const std::string& inName,
									   Mushware::tfpRubyMethodFourParams infpMethod);
    static void SingletonMethodDefine(Mushware::tRubyValue inKlass, const std::string& inName,
									  Mushware::tfpRubyMethod infpMethod);
    static void SingletonMethodDefineNoParams(Mushware::tRubyValue inKlass, const std::string& inName,
												 Mushware::tfpRubyMethodNoParams infpMethod);
    static void SingletonMethodDefineOneParam(Mushware::tRubyValue inKlass, const std::string& inName,
												 Mushware::tfpRubyMethodOneParam infpMethod);
    static void SingletonMethodDefineTwoParams(Mushware::tRubyValue inKlass, const std::string& inName,
												 Mushware::tfpRubyMethodTwoParams infpMethod);
    static void SingletonMethodDefineThreeParams(Mushware::tRubyValue inKlass, const std::string& inName,
												 Mushware::tfpRubyMethodThreeParams infpMethod);
    static void SingletonMethodDefineFourParams(Mushware::tRubyValue inKlass, const std::string& inName,
												 Mushware::tfpRubyMethodFourParams infpMethod);
	static void HashConvert(Mushware::tRubyHash& outHash, const MushRubyValue& inHash);
	static void HashConvert(Mushware::tRubyHash& outHash, Mushware::tRubyValue inHash);
	static void Raise(const std::string& inStr);
	static bool SameDataType(Mushware::tRubyValue inA, Mushware::tRubyValue inB);
	static bool IsInstanceOf(Mushware::tRubyValue inValue, Mushware::tRubyID inKlass);
	static void RaiseUnlessInstanceOf(Mushware::tRubyValue inValue, Mushware::tRubyValue inKlass);
	static Mushware::tRubyValue DataWrapStruct(Mushware::tRubyValue inSelf, Mushware::tfpRubyDataFunc infpMark, Mushware::tfpRubyDataFunc infpFree, void *inpData);
	static void *DataGetStruct(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue StringNew(const std::string& inStr);
	static Mushware::tRubyValue ClassNewInstance(Mushware::tRubyValue inValue);
    static MushRubyValue ClassNewInstance(const MushRubyValue& inValue);
    static Mushware::tRubyValue DataObjectWrapNew(const MushRubyValue& inKlass, const MushRubyValue& inSelf, void *inpData);
    static void *DataObjectRetrieve(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue InstanceVar(Mushware::tRubyValue inObj, Mushware::tRubyID inSym);
    static void InstanceVarSet(Mushware::tRubyValue inObj, Mushware::tRubyID inSym, Mushware::tRubyValue inValue);
    static void Freeze(Mushware::tRubyValue& ioValue);
    static void HashValueSet(Mushware::tRubyValue inHash, Mushware::tRubyValue inKey, Mushware::tRubyValue inValue); 
    static Mushware::tRubyValue SymbolToValue(Mushware::tRubyID inSymbol);
    static MushRubyValue GlobalVar(const std::string& inName);
    static void ArrayPush(const MushRubyValue& inArray, const MushRubyValue& inValue);
    
private:
	static Mushware::tRubyValue HashHandler(Mushware::tRubyValue inArray, Mushware::tRubyValue inArg);

	// Static variable - not thread safe
	static Mushware::tRubyHash *m_pHash;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
