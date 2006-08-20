//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyRotation.cpp
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
//%Header } IYs87CodIcNWOTBfGGVoeQ
/*
 * $Id: MushMeshRubyRotation.cpp,v 1.3 2006/06/22 19:07:33 southa Exp $
 * $Log: MushMeshRubyRotation.cpp,v $
 * Revision 1.3  2006/06/22 19:07:33  southa
 * Build fixes
 *
 * Revision 1.2  2006/06/20 19:06:53  southa
 * Object creation
 *
 * Revision 1.1  2006/06/13 19:30:38  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshRubyRotation.h"

// #include "MushMeshRubyRuby.h"
#include "MushMeshRubyVector.h"


using namespace Mushware;
using namespace std;

MUSHRUBYOBJ_INSTANCE(Mushware::tQValPair);

MUSHRUBYOBJ_INITIALIZE(Mushware::tQValPair)(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	switch (inArgC)
	{
		case 0:
			WRef(inSelf).ToRotationIdentitySet();	
			break;
			
		default:
			MushRubyUtil::Raise("Wrong number of parameters to MushRotation.new (must be 0)");	
			break;
	}
	return inSelf;
}

Mushware::tRubyValue
MushMeshRubyRotation::IsEqual(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1)
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
MushMeshRubyRotation::Rotate(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	if (MushMeshRubyVector::IsInstanceOf(inArg0))
	{
		Ref(inSelf).VectorRotate(MushMeshRubyVector::WRef(inArg0));
	}	
	else if (MushMeshRubyRotation::IsInstanceOf(inArg0))
	{
		MushMeshRubyRotation::WRef(inArg0).OuterMultiplyBy(Ref(inSelf));
	}
    
	return inSelf;
}

Mushware::tRubyValue
MushMeshRubyRotation::Inverse(Mushware::tRubyValue inSelf)
{
	tRubyValue retVal = NewInstance();
    WRef(retVal) = Ref(inSelf).Conjugate();
    
	return retVal;
}

Mushware::tRubyValue
MushMeshRubyRotation::Normalise(Mushware::tRubyValue inSelf)
{
	WRef(inSelf).InPlaceNormalise();
	return inSelf;
}

Mushware::tRubyValue
MushMeshRubyRotation::Scale(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    tVal prop = MushRubyValue(inArg0).Val();
    
    if (prop < 0.0 || prop > 1.0)
    {
        ostringstream message;
        message << "MushRotation.Scale(" << prop << ") called, but accepts only 0 <= value <= 1";
        MushRubyUtil::Raise(message.str());
    }
    
    WRef(inSelf) = MushMeshOps::SlerpNormalised(tQValPair::RotationIdentity(), Ref(inSelf), prop);
    
    return inSelf;
}

Mushware::tRubyValue
MushMeshRubyRotation::Scaled(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    tVal prop = MushRubyValue(inArg0).Val();
    
    if (prop < 0.0 || prop > 1.0)
    {
        ostringstream message;
        message << "MushRotation.Scale(" << prop << ") called, but accepts only 0 <= value <= 1";
        MushRubyUtil::Raise(message.str());
    }
    
    Mushware::tRubyValue retVal = MushMeshRubyRotation::NewInstance();
    MushMeshRubyRotation::WRef(retVal) =
        MushMeshOps::SlerpNormalised(tQValPair::RotationIdentity(),
                                     Ref(inSelf),
                                     prop);
	return retVal;    
}

void
MushMeshRubyRotation::RubyInstall(void)
{
	ObjInstall("MushRotation");
	MushRubyUtil::MethodDefineOneParam(ObjKlass(), "==", IsEqual);
	MushRubyUtil::MethodDefineOneParam(ObjKlass(), "mRotate", Rotate);
	MushRubyUtil::MethodDefineNoParams(ObjKlass(), "mInverse", Inverse);
	MushRubyUtil::MethodDefineNoParams(ObjKlass(), "mNormalise!", Normalise);
	MushRubyUtil::MethodDefineOneParam(ObjKlass(), "mScale!", Scale);
	MushRubyUtil::MethodDefineOneParam(ObjKlass(), "mScaled", Scaled);
}

MUSHRUBY_INSTALL(MushMeshRubyRotation);
