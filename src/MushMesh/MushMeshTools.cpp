//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshTools.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } iBl6/bhvcrVVWDxtT03+yg
/*
 * $Id: MushMeshTools.cpp,v 1.2 2005/02/03 15:46:53 southa Exp $
 * $Log: MushMeshTools.cpp,v $
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
