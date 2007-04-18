//%includeGuardStart {
#ifndef TESTMUSHMESHPREMATRIX_H
#define TESTMUSHMESHPREMATRIX_H
//%includeGuardStart } lAaKI38VTuxBu/lH7+FWoQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshPreMatrix.h
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
//%Header } kvC9y7lp9kk1vm5n09v4VA
/*
 * $Id: TestMushMeshPreMatrix.h,v 1.3 2006/06/01 15:40:02 southa Exp $
 * $Log: TestMushMeshPreMatrix.h,v $
 * Revision 1.3  2006/06/01 15:40:02  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/05/19 13:02:23  southa
 * Mac release work
 *
 * Revision 1.1  2004/10/31 09:22:51  southa
 * Added MushMeshPreMatrix
 *
 */
#include "TestMushMeshStandard.h"

class TestMushMeshPreMatrix
{
public:
    static MushcoreScalar TestPreMatrix(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    
private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
