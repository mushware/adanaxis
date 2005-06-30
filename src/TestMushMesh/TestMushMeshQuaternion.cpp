//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshQuaternion.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } TGM/4ae2lNjW0/j6zPy6UA
/*
 * $Id: TestMushMeshQuaternion.cpp,v 1.5 2005/05/19 13:02:23 southa Exp $
 * $Log: TestMushMeshQuaternion.cpp,v $
 * Revision 1.5  2005/05/19 13:02:23  southa
 * Mac release work
 *
 * Revision 1.4  2005/02/03 21:03:11  southa
 * Build fixes
 *
 * Revision 1.3  2005/02/03 15:47:03  southa
 * Quaternion work
 *
 * Revision 1.2  2004/12/12 10:55:37  southa
 * Quaternion conversions
 *
 * Revision 1.1  2004/12/06 20:44:18  southa
 * Quaternion and matrix operations
 *
 */

#include "TestMushMeshQuaternion.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMeshQuaternion(TestMushMeshQuaternion::Install);

void
TestMushMeshQuaternion::PseudoRandomRotationGet(t4x4Val& outMatrix, tVal inSeed)
{
    t4x4Val aMatrix =
    t4x4Val(t4Val( cos(2*inSeed), -sin(2*inSeed),              0,             0),
            t4Val( sin(2*inSeed),  cos(2*inSeed),              0,             0),
            t4Val(             0,              0,       cos(5*inSeed), -sin(5*inSeed)),
            t4Val(             0,              0,       sin(5*inSeed),  cos(5*inSeed))
            );
    
    t4x4Val bMatrix =
        t4x4Val(t4Val( cos(3*inSeed), 0,              -sin(3*inSeed),             0),
                t4Val(             0,  cos(7*inSeed),              0, -sin(7*inSeed)),
                t4Val( sin(3*inSeed),              0,  cos(3*inSeed),             0),
                t4Val(             0,  sin(7*inSeed),              0,  cos(7*inSeed))
                );
    
    outMatrix = aMatrix * bMatrix;                
}

void
TestMushMeshQuaternion::PseudoRandomVectorGet(t4Val& outVector, tVal inSeed)
{
    outVector = t4Val(1.37*cos(0.72 + 2.32*inSeed),
                      5.21*cos(0.86 + 1.24*inSeed),
                      2.38*cos(0.98 + 3.02*inSeed),
                      3.76*cos(1.32 + 0.54*inSeed));
}

MushcoreScalar
TestMushMeshQuaternion::TestQuaternion(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    tQVal aQuat(7, 5, 3, 1);
    tQVal bQuat, cQuat;
    tVal length = std::sqrt(7*7+5*5+3*3+1.0);
    tQVal resultQuat(7/length, 5/length, 3/length, 1/length);
    
    MushMeshOps::Normalise(aQuat);
    
    if (resultQuat != aQuat)
    {
        ostringstream message;
        message << "Normalise failed : Normalise(" << aQuat << ") != " << resultQuat;
        throw MushcoreCommandFail(message.str());
    }
    
    aQuat = tQVal(1, 2, 3, 4);
    bQuat = tQVal(5, 6, 7, 8);
    
    resultQuat = tQVal(1*5-2*6-3*7-4*8,
                       1*6+2*5+3*8-4*7,
                       1*7+3*5-2*8+4*6,
                       1*8+4*5+2*7-3*6);
    
    if (aQuat * bQuat != resultQuat)
    {
        ostringstream message;
        message << "operator tQVal * tQVal failed : " << aQuat << " * " << bQuat << " == " << aQuat * bQuat;
        message << " (expected " << resultQuat << ")";
        throw MushcoreCommandFail(message.str());
    }
    
    cQuat = aQuat;
    cQuat.PostMultiplyBy(bQuat);
    
    if (cQuat != resultQuat)
    {
        ostringstream message;
        message << "Quat.PostMultiplyBy failed : " << aQuat << ".PostMultiplyBy(" << bQuat << ") == " << cQuat;
        message << " (expected " << resultQuat << ")";
        throw MushcoreCommandFail(message.str());
    }
    
    cQuat = bQuat;
    cQuat.PreMultiplyBy(aQuat);
    
    if (cQuat != resultQuat)
    {
        ostringstream message;
        message << "Quat.PreMultiplyBy failed : " << bQuat << ".PreMultiplyBy(" << aQuat << ") == " << cQuat;
        message << " (expected " << resultQuat << ")";
        throw MushcoreCommandFail(message.str());
    }
    
    tQVal::tBase cVec = bQuat;
    aQuat.PreMultiplyVector(cVec);
    
    if (tQVal(cVec) != resultQuat)
    {
        ostringstream message;
        message << "Quat.PreMultiplyVector failed : " << bQuat << ".PreMultiplyVector(" << aQuat << ") == " << cVec;
        message << " (expected " << resultQuat << ")";
        throw MushcoreCommandFail(message.str());
    }
 
    cVec = aQuat;
    bQuat.PostMultiplyVector(cVec);
    
    if (tQVal(cVec) != resultQuat)
    {
        ostringstream message;
        message << "Quat.PostMultiplyVector failed : " << aQuat << ".PostMultiplyVector(" << bQuat << ") == " << cVec;
        message << " (expected " << resultQuat << ")";
        throw MushcoreCommandFail(message.str());
    }
    
    tQValPair aQuatPair;
    t4x4Val aMatrix, bMatrix;
    
    for (tVal i=0; i<100; i+=0.77)
    {
        PseudoRandomRotationGet(aMatrix, i);
        
        MushMeshOps::RotationMatrixToQuaternionPair(aQuatPair, aMatrix);
        MushMeshOps::QuaternionPairToRotationMatrix(bMatrix, aQuatPair);
        
        if (!MushMeshOps::ApproxEquals(aMatrix, bMatrix))
        {
            ostringstream message;
            message << "QuatPair/Matrix conversion failed : " << aMatrix << " != " << bMatrix;
            message << " (quaternions were " << aQuatPair.First() << ", " << aQuatPair.Second() << ")";
            throw MushcoreCommandFail(message.str());
        }
    }
    
    for (tVal angle=0; angle<100; angle+=0.73)
    {
        for (U32 axis=0; axis<6; ++axis)
        {
            tQValPair qPair = MushMeshTools::QuaternionRotateInAxis(axis, angle);
            
            MushMeshOps::QuaternionPairToRotationMatrix(aMatrix, qPair);

            bMatrix = MushMeshTools::MatrixRotateInAxis(axis, angle);
            
            if (!MushMeshOps::ApproxEquals(aMatrix, bMatrix))
            {
                ostringstream message;
                message << "xxxRotateInAxis failed (angle=" << angle << ", axis=" << axis << ") : " << aMatrix << " != " << bMatrix;
                message << " (quaternions were " << aQuatPair.First() << ", " << aQuatPair.Second() << ")";
                throw MushcoreCommandFail(message.str());
            }
            
            for (U32 nextAxis=0; nextAxis < 6; ++nextAxis)
            {
                tQValPair qNextPair = MushMeshTools::QuaternionRotateInAxis(nextAxis, 1+angle);
                
                qPair.OuterMultiplyBy(qNextPair);
                
                MushMeshOps::QuaternionPairToRotationMatrix(aMatrix, qPair);
                
                bMatrix = MushMeshTools::MatrixRotateInAxis(nextAxis, 1+angle) * bMatrix;
                
                if (!MushMeshOps::ApproxEquals(aMatrix, bMatrix))
                {
                    ostringstream message;
                    message << "OuterMultiplyBy failed (nextAngle=" << 1+angle << ", nextAxis=" << nextAxis << ") : " << aMatrix << " != " << bMatrix;
                    message << " (quaternions were " << aQuatPair.First() << ", " << aQuatPair.Second() << ")";
                    throw MushcoreCommandFail(message.str());
                }
            }
        }
    }
    
    for (tVal seed=0; seed<100; seed += 0.34)
    {
        t4Val aVec, bVec;
        PseudoRandomVectorGet(aVec, seed);
        bVec = aVec;
        
        for (U32 i=0; i<6; ++i)
        {
            MushMeshPreMatrix<tVal, 4, 4> rotate = MushMeshTools::MatrixRotateInAxis(i, cos((i+1)*(1.0+seed/30.0))*4*sin(seed/4));

            bVec = rotate * bVec;
        }

        tQValPair orient(tQValPair::RotationIdentityGet());
        
        for (U32 i=0; i<6; ++i)
        {
            orient.OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(i, cos((i+1)*(1.0+seed/30.0))*4*sin(seed/4)));
        }
        
        orient.InPlaceRotate(aVec);
        
        if (!MushMeshOps::ApproxEquals(aVec, bVec))
        {
            ostringstream message;
            message << "InPlaceRotate failed : " << aQuat << " != " << bQuat;
            throw MushcoreCommandFail(message.str());
        }
    }  
    
    return MushcoreScalar(0);
}

void
TestMushMeshQuaternion::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushmeshquaternion", TestQuaternion);
}
