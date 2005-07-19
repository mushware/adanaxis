//%includeGuardStart {
#ifndef MUSHMESHTOOLS_H
#define MUSHMESHTOOLS_H
//%includeGuardStart } 3QmVbluf3UkkQebEInihFQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshTools.h
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
//%Header } MRqkmNXxP7DiVadot5CVdg
/*
 * $Id: MushMeshTools.h,v 1.6 2005/07/12 12:18:18 southa Exp $
 * $Log: MushMeshTools.h,v $
 * Revision 1.6  2005/07/12 12:18:18  southa
 * Projectile work
 *
 * Revision 1.5  2005/05/19 13:02:11  southa
 * Mac release work
 *
 * Revision 1.4  2005/02/27 01:01:31  southa
 * Eigenplane markers
 *
 * Revision 1.3  2005/02/03 21:03:02  southa
 * Build fixes
 *
 * Revision 1.2  2005/02/03 15:46:53  southa
 * Quaternion work
 *
 * Revision 1.1  2004/10/31 23:34:07  southa
 * Hypercube rendering test
 *
 */

#include "MushMeshStandard.h"
#include "MushMeshVector.h"
#include "MushMeshQuaternion.h"
#include "MushMeshQuaternionPair.h"
#include "MushMeshPreMatrix.h"

class MushMeshTools
{
public:
    enum
    {
        kAxisXY = 0,
        kAxisZW = 1,
        kAxisXZ = 2,
        kAxisYW = 3,
        kAxisXW = 4,
        kAxisYZ = 5
    };
    
    static Mushware::t3x3Val RotateInXY(Mushware::tVal inAngle);
    static Mushware::t4x4Val MatrixRotateInAxis(Mushware::U32 inAxis, Mushware::tVal inAngle);
    static Mushware::tQValPair QuaternionRotateInAxis(Mushware::U32 inAxis, Mushware::tVal inAngle);
    static Mushware::tQValPair RandomOrientation(void);
    static Mushware::tVal Random(const Mushware::tVal inMin, const Mushware::tVal inMax);
    static void RandomAngularVelocityMake(Mushware::tQValPair& outPair, Mushware::tVal inAmount);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
