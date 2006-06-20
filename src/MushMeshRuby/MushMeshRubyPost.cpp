//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyPost.cpp
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
//%Header } qET4CzgnHaT7yIw64k1ecg
/*
 * $Id$
 * $Log$
 */

#include "MushMeshRubyPost.h"

#include "MushMeshRubyRotation.h"
#include "MushMeshRubyVector.h"

using namespace Mushware;
using namespace std;

MUSHRUBYOBJ_INSTANCE(MushMeshPosticity);

MUSHRUBYOBJ_INITIALIZE(MushMeshPosticity)(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	MushMeshPosticity& postRef = WRef(inSelf);
	
	switch (inArgC)
	{
		case 0:
			postRef.ToIdentitySet();	
			break;
			
		case 1:
		{
			postRef.ToIdentitySet();	

			MushRubyValue param0(inpArgV[0]);
			if (param0.IsHash())
			{
				Mushware::tRubyHash paramHash = param0.Hash();
				
				for (Mushware::tRubyHash::iterator p = paramHash.begin(); p != paramHash.end(); ++p)
				{
					tRubyID symbol = p->first.Symbol();
					if (symbol == MushRubyIntern::position())
					{
						postRef.PosSet(MushMeshRubyVector::Ref(p->second.Value()));
					}
					else if (symbol == MushRubyIntern::angular_position())
					{
						postRef.AngPosSet(MushMeshRubyRotation::Ref(p->second.Value()));
					}
					else if (symbol == MushRubyIntern::velocity())
					{
						postRef.VelSet(MushMeshRubyVector::Ref(p->second.Value()));
					}
					else if (symbol == MushRubyIntern::angular_velocity())
					{
						postRef.AngVelSet(MushMeshRubyRotation::Ref(p->second.Value()));
					}
					else
					{
						MushRubyUtil::Raise("Unknown name in parameter hash '"+p->first.String()+"'");	
					}
				}
			}
		}
		break;
		
		case 4:
			postRef.PosSet(MushMeshRubyVector::Ref(inpArgV[0]));
			postRef.VelSet(MushMeshRubyVector::Ref(inpArgV[1]));
			postRef.AngPosSet(MushMeshRubyRotation::Ref(inpArgV[2]));
			postRef.AngVelSet(MushMeshRubyRotation::Ref(inpArgV[3]));
			break;
			
		default:
			MushRubyUtil::Raise("Wrong number of parameters to MushPost.new (must be 0, 1 hash or 4)");	
			break;
	}
	return inSelf;
}

Mushware::tRubyValue
MushMeshRubyPost::position(Mushware::tRubyValue inSelf)
{
	Mushware::tRubyValue retVal = MushMeshRubyVector::NewInstance();
	MushMeshRubyVector::WRef(retVal) = Ref(inSelf).Pos();
	return retVal;
}

Mushware::tRubyValue
MushMeshRubyPost::velocity(Mushware::tRubyValue inSelf)
{
	Mushware::tRubyValue retVal = MushMeshRubyVector::NewInstance();
	MushMeshRubyVector::WRef(retVal) = Ref(inSelf).Vel();
	return retVal;
}

Mushware::tRubyValue
MushMeshRubyPost::angular_position(Mushware::tRubyValue inSelf)
{
	Mushware::tRubyValue retVal = MushMeshRubyRotation::NewInstance();
	MushMeshRubyRotation::WRef(retVal) = Ref(inSelf).AngPos();
	return retVal;
}

Mushware::tRubyValue
MushMeshRubyPost::angular_velocity(Mushware::tRubyValue inSelf)
{
	Mushware::tRubyValue retVal = MushMeshRubyRotation::NewInstance();
	MushMeshRubyRotation::WRef(retVal) = Ref(inSelf).AngVel();
	return retVal;
}

Mushware::tRubyValue
MushMeshRubyPost::position_equal(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	WRef(inSelf).PosSet(MushMeshRubyVector::Ref(inArg0));
	return inSelf;
}

Mushware::tRubyValue
MushMeshRubyPost::velocity_equal(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	WRef(inSelf).VelSet(MushMeshRubyVector::Ref(inArg0));
	return inSelf;
}

Mushware::tRubyValue
MushMeshRubyPost::angular_position_equal(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	WRef(inSelf).AngPosSet(MushMeshRubyRotation::Ref(inArg0));
	return inSelf;
}

Mushware::tRubyValue
MushMeshRubyPost::angular_velocity_equal(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
	WRef(inSelf).AngVelSet(MushMeshRubyRotation::Ref(inArg0));
	return inSelf;
}

void
MushMeshRubyPost::RubyInstall(void)
{
	ObjInstall("MushPost");
	MushRubyUtil::MethodDefineNoParams(ObjKlass(), "position", position);
	MushRubyUtil::MethodDefineNoParams(ObjKlass(), "velocity", velocity);
	MushRubyUtil::MethodDefineNoParams(ObjKlass(), "angular_position", angular_position);
	MushRubyUtil::MethodDefineNoParams(ObjKlass(), "angular_velocity", angular_velocity);
	MushRubyUtil::MethodDefineOneParam(ObjKlass(), "position=", position_equal);
	MushRubyUtil::MethodDefineOneParam(ObjKlass(), "velocity=", velocity_equal);
	MushRubyUtil::MethodDefineOneParam(ObjKlass(), "angular_position=", angular_position_equal);
	MushRubyUtil::MethodDefineOneParam(ObjKlass(), "angular_velocity=", angular_velocity_equal);
}

MUSHRUBY_INSTALL(MushMeshRubyPost);
