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
 * $Id: MushMeshRubyVector.cpp,v 1.7 2006/06/22 19:07:34 southa Exp $
 * $Log: MushMeshRubyVector.cpp,v $
 * Revision 1.7  2006/06/22 19:07:34  southa
 * Build fixes
 *
 * Revision 1.6  2006/06/16 12:11:05  southa
 * Ruby subclasses
 *
 * Revision 1.5  2006/06/14 18:45:50  southa
 * Ruby mesh generation
 *
 * Revision 1.4  2006/06/13 19:30:38  southa
 * Ruby mesh generation
 *
 * Revision 1.3  2006/06/13 10:35:04  southa
 * Ruby data objects
 *
 * Revision 1.2  2006/06/12 16:01:23  southa
 * Ruby mesh generation
 *
 * Revision 1.1  2006/06/12 11:59:39  southa
 * Ruby wrapper for MushMeshVector
 *
 */

#include "MushMeshRubyVector.h"

// #include "MushMeshRubyRuby.h"

using namespace Mushware;
using namespace std;

MUSHRUBYOBJ_INSTANCE(Mushware::t4Val);

MUSHRUBYOBJ_INITIALIZE(Mushware::t4Val)(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	switch (inArgC)
	{
		case 0:
			// Leave uninitialised	
			break;
	
		case 1:
		{
			MushRubyValue param0(inpArgV[0]);
			WRef(inSelf) = t4Val(param0.ValVector());
		}
		break;
			
		case 4:
		{
			MushRubyValue param0(inpArgV[0]);
			MushRubyValue param1(inpArgV[1]);
			MushRubyValue param2(inpArgV[2]);
			MushRubyValue param3(inpArgV[3]);
		
			WRef(inSelf) = t4Val(param0.Val(), param1.Val(), param2.Val(), param3.Val());
		}
		break;
			
		default:
			MushRubyUtil::Raise("Wrong number of parameters to MushVector.initialize (must be 0, 1 array or 4 values)");	
			break;
	}
	return inSelf;
}

Mushware::tRubyValue
MushMeshRubyVector::MushVectorInPlaceAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1)
{
	WRef(inSelf) += Ref(inArg1);
	
	return inSelf;
}

Mushware::tRubyValue
MushMeshRubyVector::MushVectorAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1)
{
	tRubyValue retVal = MushRubyUtil::ClassNewInstance(ObjKlass());
    WRef(retVal) = Ref(inSelf);
	MushVectorInPlaceAdd(retVal, inArg1);
	
	return retVal;
}

Mushware::tRubyValue
MushMeshRubyVector::MushVectorInPlaceSubtract(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1)
{
	WRef(inSelf) -= Ref(inArg1);
	
	return inSelf;
}

Mushware::tRubyValue
MushMeshRubyVector::MushVectorSubtract(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1)
{
	tRubyValue retVal = MushRubyUtil::ClassNewInstance(ObjKlass());
    WRef(retVal) = Ref(inSelf);
	MushVectorInPlaceSubtract(retVal, inArg1);
	
	return retVal;
}

Mushware::tRubyValue
MushMeshRubyVector::MushVectorInPlaceMultiply(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1)
{
    if (IsInstanceOf(inArg1))
    {
	    WRef(inSelf) *= Ref(inArg1);
	}
    else
    {
        WRef(inSelf) *= MushRubyValue(inArg1).Val();
    }
	return inSelf;
}

Mushware::tRubyValue
MushMeshRubyVector::MushVectorMultiply(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1)
{
	tRubyValue retVal = MushRubyUtil::ClassNewInstance(ObjKlass());
    WRef(retVal) = Ref(inSelf);
	MushVectorInPlaceMultiply(retVal, inArg1);
	
	return retVal;
}

Mushware::tRubyValue
MushMeshRubyVector::MushVectorIsEqual(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1)
{
	tRubyValue retVal;
	if (Ref(inSelf) == Ref(inArg1))
	{
		retVal = Mushware::kRubyQtrue;	
	}
	else
	{
		retVal = Mushware::kRubyQfalse;	
	}
	return retVal;
}

Mushware::tRubyValue
MushMeshRubyVector::ApproxEqual(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0, Mushware::tRubyValue inArg1)
{
	if (!MushRubyUtil::IsInstanceOf(inArg0, ObjKlass()))
	{
		MushRubyUtil::Raise("Cannot compare vector with different type");
	}
	return Ref(inSelf).ApproxEqual(Ref(inArg0), MushRubyValue(inArg1).Val());
}

void
MushMeshRubyVector::RubyInstall(void)
{
	ObjInstall("MushVector");

	MushRubyUtil::MethodDefineOneParam(ObjKlass(), "+=", MushVectorInPlaceAdd);
	MushRubyUtil::MethodDefineOneParam(ObjKlass(), "+", MushVectorAdd);
	MushRubyUtil::MethodDefineOneParam(ObjKlass(), "-=", MushVectorInPlaceSubtract);
	MushRubyUtil::MethodDefineOneParam(ObjKlass(), "-", MushVectorSubtract);
	MushRubyUtil::MethodDefineOneParam(ObjKlass(), "*=", MushVectorInPlaceMultiply);
	MushRubyUtil::MethodDefineOneParam(ObjKlass(), "*", MushVectorMultiply);
	MushRubyUtil::MethodDefineOneParam(ObjKlass(), "==", MushVectorIsEqual);
	MushRubyUtil::MethodDefineTwoParams(ObjKlass(), "mApproxEqual", ApproxEqual);
}

MUSHRUBY_INSTALL(MushMeshRubyVector);
