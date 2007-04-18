//%includeGuardStart {
#ifndef TESTMUSHMESHPATCH_H
#define TESTMUSHMESHPATCH_H
//%includeGuardStart } BFG5WurStwvR3cwySRKGUQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshPatch.h
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
//%Header } i7YbGtefpCKb0xDHDgAJ3A
/*
 * $Id: TestMushMeshPatch.h,v 1.5 2006/06/01 15:40:02 southa Exp $
 * $Log: TestMushMeshPatch.h,v $
 * Revision 1.5  2006/06/01 15:40:02  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:23  southa
 * Mac release work
 *
 * Revision 1.3  2004/01/02 21:13:17  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/26 10:05:30  southa
 * End patch testing
 *
 * Revision 1.1  2003/10/20 13:05:57  southa
 * Created
 *
 */


#include "TestMushMeshStandard.h"

class TestMushMeshPatch
{
public:
    static MushcoreScalar TestPatch(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);

private:
    enum
    {
        kXMax = 6,
        kYMax = 7
    };

    static void GeometryPrint(const Mushware::tGeometryArray& inArray);

    static bool ChangeVerify(const Mushware::tGeometryArray& inArray1,
                             const Mushware::tGeometryArray& inArray2,
                             Mushware::U32 inChanges);
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
