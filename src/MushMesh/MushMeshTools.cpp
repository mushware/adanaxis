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
 * $Id$
 * $Log$
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

MushMeshPreMatrix<tVal, 4, 4>
MushMeshTools::RotateInAxis(U32 inAxis, tVal inAngle)
{
    switch (inAxis)
    {
        case 0:            
            return MushMeshPreMatrix<tVal, 4, 4>
            (
             MushMeshVector<tVal, 4>( cos(inAngle), sin(inAngle),            0,            0),
             MushMeshVector<tVal, 4>(-sin(inAngle), cos(inAngle),            0,            0),
             MushMeshVector<tVal, 4>(            0,            0,            1,            0),
             MushMeshVector<tVal, 4>(            0,            0,            0,            1)
             );
            
        case 1:            
            return MushMeshPreMatrix<tVal, 4, 4>
            (
             MushMeshVector<tVal, 4>( cos(inAngle),            0, sin(inAngle),            0),
             MushMeshVector<tVal, 4>(            0,            1,            0,            0),
             MushMeshVector<tVal, 4>(-sin(inAngle),            0, cos(inAngle),            0),
             MushMeshVector<tVal, 4>(            0,            0,            0,            1)
             );
            
        case 2:            
            return MushMeshPreMatrix<tVal, 4, 4>
            (
             MushMeshVector<tVal, 4>( cos(inAngle),            0,            0, sin(inAngle)),
             MushMeshVector<tVal, 4>(            0,            1,            0,            0),
             MushMeshVector<tVal, 4>(            0,            0,            1,            0),
             MushMeshVector<tVal, 4>(-sin(inAngle),            0,            0, cos(inAngle))
             );
            
        case 3:            
            return MushMeshPreMatrix<tVal, 4, 4>
            (
             MushMeshVector<tVal, 4>(            1,            0,            0,            0),
             MushMeshVector<tVal, 4>(            0, cos(inAngle), sin(inAngle),            0),
             MushMeshVector<tVal, 4>(            0,-sin(inAngle), cos(inAngle),            0),
             MushMeshVector<tVal, 4>(            0,            0,            0,            1)
             );
            
        case 4:            
            return MushMeshPreMatrix<tVal, 4, 4>
            (
             MushMeshVector<tVal, 4>(            1,            0,            0,            0),
             MushMeshVector<tVal, 4>(            0, cos(inAngle),            0, sin(inAngle)),
             MushMeshVector<tVal, 4>(            0,            0,            1,            0),
             MushMeshVector<tVal, 4>(            0,-sin(inAngle),            0, cos(inAngle))
             );
            
            
        case 5:            
            return MushMeshPreMatrix<tVal, 4, 4>
            (
             MushMeshVector<tVal, 4>(            1,            0,            0,            0),
             MushMeshVector<tVal, 4>(            0,            1,            0,            0),
             MushMeshVector<tVal, 4>(            0,            0, cos(inAngle), sin(inAngle)),
             MushMeshVector<tVal, 4>(            0,            0,-sin(inAngle), cos(inAngle))
             );
            
            
        default:
        {
            ostringstream message;
            message << "Bad axis number (0 <= " << inAxis << " <= 5)";
            throw MushcoreLogicFail(message.str());
        }
    }
}

