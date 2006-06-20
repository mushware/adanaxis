//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyTools.cpp
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
//%Header } oKuIr5eVL2esfxDutcXp9Q
/*
 * $Id: MushMeshRubyTools.cpp,v 1.1 2006/06/13 19:30:38 southa Exp $
 * $Log: MushMeshRubyTools.cpp,v $
 * Revision 1.1  2006/06/13 19:30:38  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshRubyTools.h"

#include "MushMeshRubyRotation.h"

using namespace Mushware;
using namespace std;

MUSHRUBYOBJ_INSTANCE(MushMeshTools);

Mushware::tRubyValue
MushMeshRubyTools::RotationInAxis(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0,
								  Mushware::tRubyValue inArg1)
{
	MushRubyValue param0(inArg0);
	MushRubyValue param1(inArg1);
	
	Mushware::tRubyValue retVal = MushMeshRubyRotation::NewInstance();
	
	MushMeshRubyRotation::WRef(retVal) = MushMeshTools::QuaternionRotateInAxis(param0.U32(), param1.Val());
	
	return retVal;
}

Mushware::tRubyValue
MushMeshRubyTools::RotationInXYPlane(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	Mushware::tRubyValue retVal = MushMeshRubyRotation::NewInstance();
	MushMeshRubyRotation::WRef(retVal) = MushMeshTools::QuaternionRotateInAxis(MushMeshTools::kAxisXY, MushRubyValue(inArg0).Val());
	return retVal;
}

Mushware::tRubyValue
MushMeshRubyTools::RotationInZWPlane(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	Mushware::tRubyValue retVal = MushMeshRubyRotation::NewInstance();
	MushMeshRubyRotation::WRef(retVal) = MushMeshTools::QuaternionRotateInAxis(MushMeshTools::kAxisZW, MushRubyValue(inArg0).Val());
	return retVal;
}

Mushware::tRubyValue
MushMeshRubyTools::RotationInXZPlane(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	Mushware::tRubyValue retVal = MushMeshRubyRotation::NewInstance();
	MushMeshRubyRotation::WRef(retVal) = MushMeshTools::QuaternionRotateInAxis(MushMeshTools::kAxisXZ, MushRubyValue(inArg0).Val());
	return retVal;
}

Mushware::tRubyValue
MushMeshRubyTools::RotationInYWPlane(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	Mushware::tRubyValue retVal = MushMeshRubyRotation::NewInstance();
	MushMeshRubyRotation::WRef(retVal) = MushMeshTools::QuaternionRotateInAxis(MushMeshTools::kAxisYW, MushRubyValue(inArg0).Val());
	return retVal;
}

Mushware::tRubyValue
MushMeshRubyTools::RotationInXWPlane(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	Mushware::tRubyValue retVal = MushMeshRubyRotation::NewInstance();
	MushMeshRubyRotation::WRef(retVal) = MushMeshTools::QuaternionRotateInAxis(MushMeshTools::kAxisXW, MushRubyValue(inArg0).Val());
	return retVal;
}

Mushware::tRubyValue
MushMeshRubyTools::RotationInYZPlane(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	Mushware::tRubyValue retVal = MushMeshRubyRotation::NewInstance();
	MushMeshRubyRotation::WRef(retVal) = MushMeshTools::QuaternionRotateInAxis(MushMeshTools::kAxisYZ, MushRubyValue(inArg0).Val());
	return retVal;
}

void
MushMeshRubyTools::RubyInstall(void)
{
	ObjInstall("MushTools");

	MushRubyUtil::SingletonMethodDefineTwoParams(ObjKlass(), "cRotationInPlane", RotationInAxis);
	MushRubyUtil::SingletonMethodDefineOneParam(ObjKlass(), "cRotationInXYPlane", RotationInXYPlane);
	MushRubyUtil::SingletonMethodDefineOneParam(ObjKlass(), "cRotationInZWPlane", RotationInZWPlane);
	MushRubyUtil::SingletonMethodDefineOneParam(ObjKlass(), "cRotationInXZPlane", RotationInXZPlane);
	MushRubyUtil::SingletonMethodDefineOneParam(ObjKlass(), "cRotationInYWPlane", RotationInYWPlane);
	MushRubyUtil::SingletonMethodDefineOneParam(ObjKlass(), "cRotationInXWPlane", RotationInXWPlane);
	MushRubyUtil::SingletonMethodDefineOneParam(ObjKlass(), "cRotationInYZPlane", RotationInYZPlane);
}

MUSHRUBY_INSTALL(MushMeshRubyTools);
