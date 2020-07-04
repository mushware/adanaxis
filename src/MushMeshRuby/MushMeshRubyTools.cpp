//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyTools.cpp
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
//%Header } wQ43OQjXkGeu4uchZHokKA
/*
 * $Id: MushMeshRubyTools.cpp,v 1.5 2006/08/20 14:19:22 southa Exp $
 * $Log: MushMeshRubyTools.cpp,v $
 * Revision 1.5  2006/08/20 14:19:22  southa
 * Seek operation
 *
 * Revision 1.4  2006/07/18 16:58:38  southa
 * Texture fixes
 *
 * Revision 1.3  2006/07/17 14:43:41  southa
 * Billboarded deco objects
 *
 * Revision 1.2  2006/06/20 19:06:54  southa
 * Object creation
 *
 * Revision 1.1  2006/06/13 19:30:38  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshRubyTools.h"

#include "MushMeshRubyPost.h"
#include "MushMeshRubyRotation.h"
#include "MushMeshRubyVector.h"

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

Mushware::tRubyValue
MushMeshRubyTools::RandomOrientation(Mushware::tRubyValue inSelf)
{
	Mushware::tRubyValue retVal = MushMeshRubyRotation::NewInstance();
	MushMeshRubyRotation::WRef(retVal) = MushMeshTools::RandomOrientation();
	return retVal;
}

Mushware::tRubyValue
MushMeshRubyTools::RandomUnitVector(Mushware::tRubyValue inSelf)
{
	Mushware::tRubyValue retVal = MushMeshRubyVector::NewInstance();
	MushMeshRubyVector::WRef(retVal) = MushMeshTools::RandomUnitVector();
	return retVal;
}

Mushware::tRubyValue
MushMeshRubyTools::RandomAngularVelocity(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	Mushware::tRubyValue retVal = MushMeshRubyRotation::NewInstance();
    MushMeshTools::RandomAngularVelocity(MushMeshRubyRotation::WRef(retVal), MushRubyValue(inArg0).Val());
	return retVal;
}

Mushware::tRubyValue
MushMeshRubyTools::RandomSeedSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	srand(MushRubyValue(inArg0).U32());
	return kRubyQnil;;
}

Mushware::tRubyValue
MushMeshRubyTools::SeekRotation(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0,
                                Mushware::tRubyValue inArg1)
{
	Mushware::tRubyValue retVal = MushMeshRubyRotation::NewInstance();
    MushMeshTools::PartialRotateToWAxis(MushMeshRubyRotation::WRef(retVal),
                                        MushMeshRubyVector::Ref(inArg0),
                                        MushRubyValue(inArg1).Val());
	return retVal;
}

Mushware::tRubyValue
MushMeshRubyTools::TurnToFace(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0,
                              Mushware::tRubyValue inArg1, Mushware::tRubyValue inArg2)
{
	Mushware::tRubyValue retVal = MushMeshRubyRotation::NewInstance();
    MushMeshTools::TurnToFace(MushMeshRubyRotation::WRef(retVal),
                                        MushMeshRubyPost::Ref(inArg0),
                                        MushMeshRubyVector::Ref(inArg1),
                                        MushRubyValue(inArg2).Val());
	return retVal;
}

Mushware::tRubyValue
MushMeshRubyTools::Slerp(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0,
                         Mushware::tRubyValue inArg1, Mushware::tRubyValue inArg2)
{
	Mushware::tRubyValue retVal = MushMeshRubyRotation::NewInstance();
    MushMeshRubyRotation::WRef(retVal) =
        MushMeshOps::SlerpNormalised(MushMeshRubyRotation::Ref(inArg0),
                                     MushMeshRubyRotation::Ref(inArg1),
                                     MushRubyValue(inArg2).Val());
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
	MushRubyUtil::SingletonMethodDefineNoParams(ObjKlass(), "cRandomOrientation", RandomOrientation);
	MushRubyUtil::SingletonMethodDefineNoParams(ObjKlass(), "cRandomUnitVector", RandomUnitVector);
	MushRubyUtil::SingletonMethodDefineOneParam(ObjKlass(), "cRandomAngularVelocity", RandomAngularVelocity);
	MushRubyUtil::SingletonMethodDefineOneParam(ObjKlass(), "cRandomSeedSet", RandomSeedSet);
	MushRubyUtil::SingletonMethodDefineTwoParams(ObjKlass(), "cSeekRotation", SeekRotation);
	MushRubyUtil::SingletonMethodDefineThreeParams(ObjKlass(), "cTurnToFace", TurnToFace);
	MushRubyUtil::SingletonMethodDefineThreeParams(ObjKlass(), "cSlerp", Slerp);
	//MushRubyUtil::SingletonMethodDefineThreeParams(ObjKlass(), "cTurnToFace", TurnToFace);
}

MUSHRUBY_INSTALL(MushMeshRubyTools);
