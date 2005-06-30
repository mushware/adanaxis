//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMesh4Library.cpp
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
//%Header } 3FPaZkPeOCD2fVyuZWK2Lg
/*
 * $Id: TestMushMesh4Library.cpp,v 1.1 2005/06/30 12:04:56 southa Exp $
 * $Log: TestMushMesh4Library.cpp,v $
 * Revision 1.1  2005/06/30 12:04:56  southa
 * Mesh work
 *
 */

#include "TestMushMesh4Library.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMesh4Library(TestMushMesh4Library::Install);

MushcoreScalar
TestMushMesh4Library::Test4Library(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    MushcoreXMLOStream xmlOut(std::cout);
    
    MushMesh4Mesh mesh;
    
    MushMesh4Library::Sgl().UnitTesseractCreate(mesh);
    mesh.Prebuild();
    
    std::cout << endl;;
    xmlOut << mesh;
    
    return MushcoreScalar(0);
}

void
TestMushMesh4Library::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushmesh4library", Test4Library);
}
