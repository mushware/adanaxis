//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshVector.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } mB7tJSwUOE22xsO0P0146A
/*
 * $Id: TestMushMeshVector.cpp,v 1.3 2003/10/15 11:54:55 southa Exp $
 * $Log: TestMushMeshVector.cpp,v $
 * Revision 1.3  2003/10/15 11:54:55  southa
 * MushMeshArray neighbour testing and subdivision
 *
 * Revision 1.2  2003/10/15 07:08:30  southa
 * MushMeshArray creation
 *
 */
#include "TestMushMeshVector.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMeshVectorInstaller(TestMushMeshVector::Install);

MushcoreScalar
TestMushMeshVector::TestVector(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    typedef MushMeshVector<tVal, 2> t2vecVal;
    // Basic operations
    t2vecVal a(1,2);
    t2vecVal b(1,2);

    if (a != b)
    {
        throw(MushcoreLogicFail("operator != failed"));
    }
    b = t2vecVal(2,2);
    if (a == b)
    {
        throw(MushcoreLogicFail("operator == failed"));
    }

    if (a + b != t2vecVal(3,4))
    {
        ostringstream message;
        message << "operator + failed : " << a << " + " << b << " != " << a+b;
        throw(MushcoreLogicFail(message.str()));
    }
    if (a - b != t2vecVal(-1,0))
    {
        throw(MushcoreLogicFail("operator - failed"));
    }
    if (a * b != t2vecVal(2,4))
    {
        throw(MushcoreLogicFail("operator * failed"));
    }
    if (a / b != t2vecVal(0.5,1))
    {
        throw(MushcoreLogicFail("operator / failed"));
    }
    return MushcoreScalar(0);
}

void
TestMushMeshVector::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testvector", TestVector);
}
