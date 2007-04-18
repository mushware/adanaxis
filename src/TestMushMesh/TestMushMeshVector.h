//%includeGuardStart {
#ifndef TESTMUSHMESHVECTOR_H
#define TESTMUSHMESHVECTOR_H
//%includeGuardStart } Cg5iaZQe5a1IqHgg/QMflQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshVector.h
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
//%Header } 1J9ZLa5R5soGo2Oz2ldhsA
/*
 * $Id: TestMushMeshVector.h,v 1.4 2006/06/01 15:40:03 southa Exp $
 * $Log: TestMushMeshVector.h,v $
 * Revision 1.4  2006/06/01 15:40:03  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/05/19 13:02:23  southa
 * Mac release work
 *
 * Revision 1.2  2004/01/02 21:13:17  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/14 13:07:26  southa
 * MushMesh vector creation
 *
 */

#include "TestMushMeshStandard.h"

class TestMushMeshVector
{
public:
    static MushcoreScalar TestVector(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
