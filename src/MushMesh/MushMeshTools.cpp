//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshTools.cpp
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
//%Header } cQoVIV2DdH4LiqrKzfp8tw
/*
 * $Id: MushMeshTools.cpp,v 1.7 2006/05/01 17:39:01 southa Exp $
 * $Log: MushMeshTools.cpp,v $
 * Revision 1.7  2006/05/01 17:39:01  southa
 * Texture generation
 *
 * Revision 1.6  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.5  2005/07/12 12:18:18  southa
 * Projectile work
 *
 * Revision 1.4  2005/05/19 13:02:11  southa
 * Mac release work
 *
 * Revision 1.3  2005/02/27 01:01:31  southa
 * Eigenplane markers
 *
 * Revision 1.2  2005/02/03 15:46:53  southa
 * Quaternion work
 *
 * Revision 1.1  2004/10/31 23:34:07  southa
 * Hypercube rendering test
 *
 */

#include "MushMeshTools.h"

#include "MushMeshSTL.h"

using namespace Mushware;
using namespace std;

MushMeshPreMatrix<tVal, 3, 3>
MushMeshTools::RotateInXY(tVal inAngle)
{
    return MushMeshPreMatrix<tVal, 3, 3>
    (
         MushMeshVector<tVal, 3>( cos(inAngle), sin(inAngle), 0),
         MushMeshVector<tVal, 3>(-sin(inAngle), cos(inAngle), 0),
         MushMeshVector<tVal, 3>(            0,            0, 1)
     );
}

Mushware::t4x4Val
MushMeshTools::MatrixRotateInAxis(U32 inAxis, tVal inAngle)
{
    switch (inAxis)
    {
        case 0:            
            return MushMeshPreMatrix<tVal, 4, 4>
            (
             MushMeshVector<tVal, 4>( cos(inAngle),-sin(inAngle),            0,            0),
             MushMeshVector<tVal, 4>( sin(inAngle), cos(inAngle),            0,            0),
             MushMeshVector<tVal, 4>(            0,            0,            1,            0),
             MushMeshVector<tVal, 4>(            0,            0,            0,            1)
             );
            
        case 1:            
            return MushMeshPreMatrix<tVal, 4, 4>
            (
             MushMeshVector<tVal, 4>(            1,            0,            0,            0),
             MushMeshVector<tVal, 4>(            0,            1,            0,            0),
             MushMeshVector<tVal, 4>(            0,            0, cos(inAngle),-sin(inAngle)),
             MushMeshVector<tVal, 4>(            0,            0, sin(inAngle), cos(inAngle))
             );
        
        case 2:            
            return MushMeshPreMatrix<tVal, 4, 4>
            (
             MushMeshVector<tVal, 4>( cos(inAngle),            0,-sin(inAngle),            0),
             MushMeshVector<tVal, 4>(            0,            1,            0,            0),
             MushMeshVector<tVal, 4>( sin(inAngle),            0, cos(inAngle),            0),
             MushMeshVector<tVal, 4>(            0,            0,            0,            1)
             );
            
        case 3:            
            return MushMeshPreMatrix<tVal, 4, 4>
            (
             MushMeshVector<tVal, 4>(            1,            0,            0,            0),
             MushMeshVector<tVal, 4>(            0, cos(inAngle),            0,-sin(inAngle)),
             MushMeshVector<tVal, 4>(            0,            0,            1,            0),
             MushMeshVector<tVal, 4>(            0, sin(inAngle),            0, cos(inAngle))
             );
            
        case 4:            
            return MushMeshPreMatrix<tVal, 4, 4>
            (
             MushMeshVector<tVal, 4>( cos(inAngle),            0,            0,-sin(inAngle)),
             MushMeshVector<tVal, 4>(            0,            1,            0,            0),
             MushMeshVector<tVal, 4>(            0,            0,            1,            0),
             MushMeshVector<tVal, 4>( sin(inAngle),            0,            0, cos(inAngle))
             );
            
        case 5:            
            return MushMeshPreMatrix<tVal, 4, 4>
            (
             MushMeshVector<tVal, 4>(            1,            0,            0,            0),
             MushMeshVector<tVal, 4>(            0, cos(inAngle),-sin(inAngle),            0),
             MushMeshVector<tVal, 4>(            0, sin(inAngle), cos(inAngle),            0),
             MushMeshVector<tVal, 4>(            0,            0,            0,            1)
             );

        default:
        {
            ostringstream message;
            message << "Bad axis number (0 <= " << inAxis << " <= 5)";
            throw MushcoreLogicFail(message.str());
        }
    }
}

Mushware::tQValPair
MushMeshTools::QuaternionRotateInAxis(U32 inAxis, tVal inAngle)
{
    tVal halfAngle = inAngle/2;
    switch (inAxis)
    {
        case 0:            
            return tQValPair
            (
             tQVal(cos(halfAngle), sin(halfAngle), 0, 0),
             tQVal(cos(halfAngle), sin(halfAngle), 0, 0)
             );
            
        case 1:            
            return tQValPair
            (
             tQVal(cos(halfAngle), sin(halfAngle), 0, 0),
             tQVal(cos(halfAngle),-sin(halfAngle), 0, 0)
             );
            
        case 2:            
            return tQValPair
            (
             tQVal(cos(halfAngle), 0, sin(halfAngle), 0),
             tQVal(cos(halfAngle), 0, sin(halfAngle), 0)
             );
            
        case 3:            
            return tQValPair
            (
             tQVal(cos(halfAngle), 0,-sin(halfAngle), 0),
             tQVal(cos(halfAngle), 0, sin(halfAngle), 0)
             );
            
        case 4:            
            return tQValPair
            (
             tQVal(cos(halfAngle), 0, 0, sin(halfAngle)),
             tQVal(cos(halfAngle), 0, 0, sin(halfAngle))
             );
            
        case 5:            
            return tQValPair
            (
             tQVal(cos(halfAngle), 0, 0, sin(halfAngle)),
             tQVal(cos(halfAngle), 0, 0,-sin(halfAngle))
             );
            
        default:
        {
            ostringstream message;
            message << "Bad axis number (0 <= " << inAxis << " <= 5)";
            throw MushcoreLogicFail(message.str());
        }
    }
}

Mushware::tQValPair
MushMeshTools::RandomOrientation(void)
{
    tQVal q1, q2;
    for (U32 i=0; i<4; ++i)
    {
        q1.Set(Random(-1,1), i);
        q2.Set(Random(-1,1), i);
    }
    
    q1.InPlaceNormalise();
    q2.InPlaceNormalise();
    
    return tQValPair(q1, q2);
}    

Mushware::tVal
MushMeshTools::Random(const Mushware::tVal inMin, const Mushware::tVal inMax)
{
    return inMin + (inMax - inMin) * static_cast<double>(std::rand())/RAND_MAX;
}

Mushware::t4Val
MushMeshTools::RandomVector(const Mushware::tVal inMin, const Mushware::tVal inMax)
{
	t4Val retVal;
    for (U32 i=0; i<4; ++i)
	{
		if (Random(-1,1) > 0)
		{
			retVal.Set(Random(inMin, inMax), i);			
		}
		else
		{
			retVal.Set(-Random(inMin, inMax), i);
		}
	}
	return retVal;
}

void
MushMeshTools::RandomAngularVelocityMake(Mushware::tQValPair& outPair, Mushware::tVal inAmount)
{
    tQValPair orientation = MushMeshTools::RandomOrientation();
    outPair.ToRotationIdentitySet();
    
    outPair.OuterMultiplyBy(orientation);
    
    // Rotate in xy
    outPair.OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis
                                                    (0, MushMeshTools::Random(-inAmount, inAmount)));
    // Rotate in zw
    outPair.OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis
                                                    (1, MushMeshTools::Random(-inAmount, inAmount)));
    
    outPair.OuterMultiplyBy(orientation.Conjugate());
}

Mushware::tQValPair
MushMeshTools::QuaternionRotateToXAxis(const Mushware::t4Val &inVec)
{
	// Generates a rotation which aligns the supplied vector with the x axis
    t4Val rotVec(inVec);
	
	tQValPair retVal = QuaternionRotateInAxis(kAxisXW, -std::atan2(rotVec.W(), rotVec.X()));
	retVal.VectorRotate(rotVec);
	
	tQValPair rotXZ = QuaternionRotateInAxis(kAxisXZ, -std::atan2(rotVec.Z(), rotVec.X()));
	rotXZ.VectorRotate(rotVec);
	retVal.OuterMultiplyBy(rotXZ);
	
	tQValPair rotXY = QuaternionRotateInAxis(kAxisXY, -std::atan2(rotVec.Y(), rotVec.X()));
    retVal.OuterMultiplyBy(rotXY);
    
	return retVal;
}

Mushware::tQValPair
MushMeshTools::QuaternionRotateToXYPlane(const Mushware::t4Val &inVec)
{
	/* Generates a rotation which moves the supplied vector into the xy plane
	 * without using any rotations which change x
	 */
    t4Val rotVec(inVec);
	
	tQValPair retVal = QuaternionRotateInAxis(kAxisYW, -std::atan2(rotVec.W(), rotVec.Y()));
	retVal.VectorRotate(rotVec);
	
	tQValPair rotYZ = QuaternionRotateInAxis(kAxisYZ, -std::atan2(rotVec.Z(), rotVec.Y()));
    retVal.OuterMultiplyBy(rotYZ);
    
	return retVal;
}

Mushware::tQValPair
MushMeshTools::QuaternionRotateVectorPairToXYPlane(const Mushware::t4Val &inVec1, const Mushware::t4Val &inVec2)
{
	/* Generates a rotation which moves the first vector to the x axis, and the second
	 * vector into the xy plane.  Details are in the 'Projection and Rendering 1'
	 * document (2006-06-08 version) at mushware.com, in the texture generation section
	 */
	
	tQValPair qR1 = QuaternionRotateToXAxis(inVec1); // R1 matrix
	tQValPair qR2 = QuaternionRotateToXYPlane(qR1.RotatedVector(inVec2));
	
	qR1.OuterMultiplyBy(qR2); // qR1 now the final rotation
	
	return qR1;
}

