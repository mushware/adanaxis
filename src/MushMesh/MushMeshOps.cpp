//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshOps.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } ZOIfzk0ChCSMw9uZrC+PiA
/*
 * $Id$
 * $Log$
 */

#include "MushMeshOps.h"

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
