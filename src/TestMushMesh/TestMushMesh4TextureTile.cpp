//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMesh4TextureTile.cpp
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
//%Header } PYMDjY0anyk/n9cDX570EQ
/*
 * $Id: TestMushMesh4TextureTile.cpp,v 1.2 2006/05/02 17:32:13 southa Exp $
 * $Log: TestMushMesh4TextureTile.cpp,v $
 * Revision 1.2  2006/05/02 17:32:13  southa
 * Texturing
 *
 * Revision 1.1  2006/05/01 17:39:01  southa
 * Texture generation
 *
 */

#include "TestMushMesh4TextureTile.h"

#include "TestMushMeshUtils.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMesh4TextureTile(TestMushMesh4TextureTile::Install);

void
TestMushMesh4TextureTile::TransformTest(const MushMesh4TextureTile& inTile,
                                        const Mushware::t2Val& inTestVec,
                                        const Mushware::t4Val& inExpectedVec)
{
    t4Val resultVec;
    inTile.Transform(resultVec, inTestVec);
    
    if (!TestMushMeshUtils::ApproxEquals(resultVec, inExpectedVec))
    {
        MushcoreLog::Sgl().XMLInfoLog() << "TextureTile was: " << inTile;
        ostringstream message;
        message << "Tile transform failed: Test vector " << inTestVec << ", " << resultVec << " != " << inExpectedVec;
        throw MushcoreCommandFail(message.str());   
    }
}

MushcoreScalar
TestMushMesh4TextureTile::Test4TextureTile(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    MushMesh4TextureTile texTile;
    
    texTile.TileBoxSet(t2BoxVal(0.1,0.2,0.3,0.5));
    
    for (U32 i=0; i<100; ++i)
    {
        texTile.TileP0Set(t2Val(i,2*i));
        texTile.TileV0Set(t2Val(2+3*i, 4*i));
        texTile.TileV1Set(t2Val(5*i,4+6*i));      
        
        texTile.ObjectP0Set(t4Val(1,0,0,0));
        texTile.ObjectV0Set(t4Val(0,1,0,0));
        texTile.ObjectV1Set(t4Val(0,0,1,0));
        
        texTile.Make();

        TransformTest(texTile, texTile.TileP0(), texTile.ObjectP0());
        TransformTest(texTile, texTile.TileP0()+texTile.TileV0(), texTile.ObjectP0()+texTile.ObjectV0());
        TransformTest(texTile, texTile.TileP0()+texTile.TileV1(), texTile.ObjectP0()+texTile.ObjectV1());
        TransformTest(texTile, texTile.TileP0()+texTile.TileV0()+texTile.TileV1(), texTile.ObjectP0()+texTile.ObjectV0()+texTile.ObjectV1());
        TransformTest(texTile, texTile.TileP0()+0.3*texTile.TileV0()+0.83*texTile.TileV1(), texTile.ObjectP0()+0.3*texTile.ObjectV0()+0.83*texTile.ObjectV1());
    }
    
    return MushcoreScalar(0);
}

void
TestMushMesh4TextureTile::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushmesh4texturetile", Test4TextureTile);
}
