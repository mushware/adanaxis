//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMesh4TextureTile.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } jSyA6BFrX9UsygjYSciwTQ
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
