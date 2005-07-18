//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshOps.cpp
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
//%Header } ALTYrsUnRmh8nIy3s/p33Q
/*
 * $Id: MushMeshOps.cpp,v 1.6 2005/07/04 15:59:00 southa Exp $
 * $Log: MushMeshOps.cpp,v $
 * Revision 1.6  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.5  2005/05/19 13:02:10  southa
 * Mac release work
 *
 * Revision 1.4  2005/02/03 21:03:00  southa
 * Build fixes
 *
 * Revision 1.3  2004/12/13 11:09:11  southa
 * Quaternion and vector tweaks
 *
 * Revision 1.2  2004/12/12 10:55:37  southa
 * Quaternion conversions
 *
 * Revision 1.1  2004/11/17 23:43:47  southa
 * Added outer product
 *
 */

#include "MushMeshOps.h"

#include "MushMeshSTL.h"
#include "MushMeshPostMatrix.h"

using namespace Mushware;
using namespace std;

Mushware::t4Val
MushMeshOps::OuterProduct(Mushware::t4Val inA, Mushware::t4Val inB, Mushware::t4Val inC)
{
    /* Result is the determinant of the matrix
     * 
     *    X    Y    Z    W
     *
     *   aX   aY   aZ    aW
     *
     *   bX   bY   bZ    bW
     *
     *   cX   cY   cZ    cW
     */
    
    
    // Calculate determinants of 2x2 matrices on the bottom rows
    
    tVal detXY = inB.X() * inC.Y() - inB.Y() * inC.X();
    tVal detXZ = inB.X() * inC.Z() - inB.Z() * inC.X();
    tVal detXW = inB.X() * inC.W() - inB.W() * inC.X();
    tVal detYZ = inB.Y() * inC.Z() - inB.Z() * inC.Y();
    tVal detYW = inB.Y() * inC.W() - inB.W() * inC.Y();
    tVal detZW = inB.Z() * inC.W() - inB.W() * inC.Z();
        
    t4Val retVal;
    
    retVal.XSet( - inA.Y() * detZW + inA.Z() * detYW - inA.W() * detYZ);
    
    retVal.YSet(   inA.X() * detZW - inA.Z() * detXW + inA.W() * detXZ);
    
    retVal.ZSet( - inA.X() * detYW + inA.Y() * detXW - inA.W() * detXY);
    
    retVal.WSet(   inA.X() * detYZ - inA.Y() * detXZ + inA.Z() * detXY);
    
    return retVal;
}

t4x4Val
MushMeshOps::PreQuaternionToMatrix(const Mushware::tQVal& inQuat)
{
    return t4x4Val(t4Val(inQuat.X(), -inQuat.Y(), -inQuat.Z(), -inQuat.W()),
                   t4Val(inQuat.Y(),  inQuat.X(), -inQuat.W(),  inQuat.Z()),
                   t4Val(inQuat.Z(),  inQuat.W(),  inQuat.X(), -inQuat.Y()),
                   t4Val(inQuat.W(), -inQuat.Z(),  inQuat.Y(),  inQuat.X())
                   );
}

t4x4Val
MushMeshOps::PostQuaternionToMatrix(const Mushware::tQVal& inQuat)
{
    return t4x4Val(t4Val(inQuat.X(), -inQuat.Y(), -inQuat.Z(), -inQuat.W()),
                   t4Val(inQuat.Y(),  inQuat.X(),  inQuat.W(), -inQuat.Z()),
                   t4Val(inQuat.Z(), -inQuat.W(),  inQuat.X(),  inQuat.Y()),
                   t4Val(inQuat.W(),  inQuat.Z(), -inQuat.Y(),  inQuat.X())
                   );}

void
MushMeshOps::QuaternionPairToRotationMatrix(Mushware::t4x4Val& outMatrix, const Mushware::tQValPair& inPair)
{
    tVal a = inPair.First().X();
    tVal b = inPair.First().Y();
    tVal c = inPair.First().Z();
    tVal d = inPair.First().W();
    tVal e = inPair.Second().X();
    tVal f = inPair.Second().Y();
    tVal g = inPair.Second().Z();
    tVal h = inPair.Second().W();
    
    outMatrix = t4x4Val(
        t4Val(a*e-b*f-c*g-d*h, -a*f-b*e+c*h-d*g, -a*g-b*h-c*e+d*f, -a*h+b*g-c*f-d*e),
        t4Val(b*e+a*f-d*g+c*h, -b*f+a*e+d*h+c*g, -b*g+a*h-d*e-c*f, -b*h-a*g-d*f+c*e),
        t4Val(c*e+d*f+a*g-b*h, -c*f+d*e-a*h-b*g, -c*g+d*h+a*e+b*f, -c*h-d*g+a*f-b*e),
        t4Val(d*e-c*f+b*g+a*h, -d*f-c*e-b*h+a*g, -d*g-c*h+b*e-a*f, -d*h+c*g+b*f+a*e)
                        );
}


void
MushMeshOps::RotationMatrixToQuaternionPair(Mushware::tQValPair& outPair, const Mushware::t4x4Val& inMatrix)
{
    tQVal qS = tQVal(inMatrix.ColumnGet(0));
    
    t4x4Val mS = PreQuaternionToMatrix(qS.Conjugate());
    t4x4Val mP = mS * inMatrix;
    
    //std::cout << "mA=" << inMatrix << endl;
    //std::cout << "qS=" << qS << endl;
    //std::cout << "mS=" << mS << endl;
    //std::cout << "mP=" << mP << endl;
    
    tVal p11 = mP.RCGet(1, 1);
    tVal p22 = mP.RCGet(2, 2);
    tVal p33 = mP.RCGet(3, 3);
    
    tVal q0sqr = 0.25*(1+p11+p22+p33);
    tVal q1sqr = 0.25*(1+p11-p22-p33);
    tVal q2sqr = 0.25*(1-p11+p22-p33);
    tVal q3sqr = 0.25*(1-p11-p22+p33);
    
    tVal q0, q1, q2, q3;
    
    if (q0sqr > q1sqr)
    {
        if (q0sqr > q2sqr)
        {
            if (q0sqr > q3sqr)
            {
                // q0 largest
                q0 = sqrt(q0sqr);
                tVal q0x4 = 4*q0;
                q1 = (mP.RCGet(3, 2)-mP.RCGet(2, 3))/q0x4;
                q2 = (mP.RCGet(1, 3)-mP.RCGet(3, 1))/q0x4;
                q3 = (mP.RCGet(2, 1)-mP.RCGet(1, 2))/q0x4;
            }
            else
            {
                // q3 largest
                goto Q3LARGEST;
            }
        }
        else
        {
            if (q2sqr > q3sqr)
            {
                // q2 largest
                goto Q2LARGEST;
            }
            else
            {
                // q3 largest
                goto Q3LARGEST;
            }
        }
    }
    else
    {
        if (q1sqr > q2sqr)
        {
            if (q1sqr > q3sqr)
            {
                // q1 largest
                q1 = sqrt(q1sqr);
                tVal q1x4 = 4*q1;
                q0 = (mP.RCGet(3, 2)-mP.RCGet(2, 3))/q1x4;
                q2 = (mP.RCGet(1, 2)+mP.RCGet(2, 1))/q1x4;
                q3 = (mP.RCGet(1, 3)+mP.RCGet(3, 1))/q1x4;
            }
            else
            {
                // q3 largest
                goto Q3LARGEST;
            }
        }
        else
        {
            if (q2sqr > q3sqr)
            {
                // q2 largest
Q2LARGEST:
                q2 = sqrt(q2sqr);
                tVal q2x4 = 4*q2;
                q0 = (mP.RCGet(1, 3)-mP.RCGet(3, 1))/q2x4;
                q1 = (mP.RCGet(1, 2)+mP.RCGet(2, 1))/q2x4;
                q3 = (mP.RCGet(2, 3)+mP.RCGet(3, 2))/q2x4;
            }
            else
            {
                // q3 largest
Q3LARGEST:
                q3 = sqrt(q3sqr);
                tVal q3x4 = 4*q3;
                q0 = (mP.RCGet(2, 1)-mP.RCGet(1, 2))/q3x4;
                q1 = (mP.RCGet(1, 3)+mP.RCGet(3, 1))/q3x4;
                q2 = (mP.RCGet(2, 3)+mP.RCGet(3, 2))/q3x4;
            }
        }
    }
    
    tQVal qP = tQVal(q0, q1, q2, q3);
    outPair.FirstSet(qS * qP);
    outPair.SecondSet(qP.Conjugate());
}

void
MushMeshOps::PosticityToMattress(Mushware::t4x4o4Val& outMattress, const MushMeshPosticity& inPost)
{
    QuaternionPairToRotationMatrix(outMattress.MatrixWRef(), inPost.AngPos());
    outMattress.OffsetSet(inPost.Pos());
}

