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
 * $Id$
 * $Log$
 */

#include "MushMeshRubyRotation.h"

#include "MushMeshRubyRuby.h"
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
			MushRubyUtil::Raise("Wrong number of parameters to MushRotation (must be 0)");	
			break;
	}
	return inSelf;
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

void
MushMeshRubyRotation::RubyInstall(void)
{
	ObjInstall("MushRotation");
	MushRubyUtil::MethodDefineOneParam(ObjKlass(), "mRotate", Rotate);
}

MUSHRUBY_INSTALL(MushMeshRubyRotation);
