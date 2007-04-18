//%includeGuardStart {
#ifndef TESTMUSHMESHQUATERNION_H
#define TESTMUSHMESHQUATERNION_H
//%includeGuardStart } QsO6VqLi2p68/1q8tHLJKQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshQuaternion.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } guWOMH92KpnD6x2g7GpLxg
/*
 * $Id: TestMushMeshQuaternion.h,v 1.5 2006/06/01 15:40:02 southa Exp $
 * $Log: TestMushMeshQuaternion.h,v $
 * Revision 1.5  2006/06/01 15:40:02  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:23  southa
 * Mac release work
 *
 * Revision 1.3  2005/02/03 21:03:12  southa
 * Build fixes
 *
 * Revision 1.2  2004/12/12 10:55:37  southa
 * Quaternion conversions
 *
 * Revision 1.1  2004/12/06 20:44:18  southa
 * Quaternion and matrix operations
 *
 */

#include "TestMushMeshStandard.h"

class TestMushMeshQuaternion
{
public:
    static void PseudoRandomRotationGet(Mushware::t4x4Val& outMatrix, Mushware::tVal inSeed);
    static void PseudoRandomVectorGet(Mushware::t4Val& outVector, Mushware::tVal inSeed);
    static MushcoreScalar TestQuaternion(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    
private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
