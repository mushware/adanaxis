//%includeGuardStart {
#ifndef TESTMUSHMESHOPS_H
#define TESTMUSHMESHOPS_H
//%includeGuardStart } 4dGfAMR+uoe7iTaqb4c6XQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshOps.h
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
//%Header } FXGAtEkMXZbUuHP5RysEHg
/*
 * $Id: TestMushMeshOps.h,v 1.2 2004/11/30 00:18:06 southa Exp $
 * $Log: TestMushMeshOps.h,v $
 * Revision 1.2  2004/11/30 00:18:06  southa
 * Additional vector operations
 *
 * Revision 1.1  2004/11/17 23:43:48  southa
 * Added outer product
 *
 */
#include "TestMushMeshStandard.h"

class TestMushMeshOps
{
public:
    static MushcoreScalar TestInnerProduct(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar TestOuterProduct(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar TestNormalise(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar TestSlerp(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    
private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
