//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageCollision.cpp
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
//%Header } FLSQqKp0PeXYgMUesN+b/A
/*
 * $Id: MushGameMessageCollision.cpp,v 1.3 2006/10/12 22:04:48 southa Exp $
 * $Log: MushGameMessageCollision.cpp,v $
 * Revision 1.3  2006/10/12 22:04:48  southa
 * Collision events
 *
 * Revision 1.2  2006/06/01 15:39:24  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/08/01 13:09:58  southa
 * Collision messaging
 *
 */

#include "MushGameMessageCollision.h"

#include "MushGameIntern.h"

#include "API/mushMushMeshRuby.h"

using namespace Mushware;
using namespace std;

Mushware::tRubyValue
MushGameMessageCollision::RubyObjectMake(void)
{
    tRubyValue retVal = MushRubyUtil::ClassNewInstance(MushGameIntern::Sgl().MushEventCollision()).Value();
    
    MushRubyUtil::InstanceVarSet(retVal, MushGameIntern::Sgl().ATm_piece1(), m_piece1->RubyObj().Value());
    MushRubyUtil::InstanceVarSet(retVal, MushGameIntern::Sgl().ATm_piece2(), m_piece2->RubyObj().Value());
    if (m_chunkNumsValid)
    {
        MushRubyUtil::InstanceVarSet(retVal, MushGameIntern::Sgl().ATm_chunkNum1(), MushRubyValue(m_chunkNum1).Value());
        MushRubyUtil::InstanceVarSet(retVal, MushGameIntern::Sgl().ATm_chunkNum2(), MushRubyValue(m_chunkNum2).Value());
    }
    // else leave undefined
    if (m_collisionPointValid)
    {
        tRubyValue collPoint = MushMeshRubyVector::NewInstance();
        MushMeshRubyVector::WRef(collPoint) = m_collisionPoint;
        MushRubyUtil::InstanceVarSet(retVal, MushGameIntern::Sgl().ATm_collisionPoint(), collPoint);
    }
    // else leave undefined
    
    return retVal;
}

//%outOfLineFunctions {

const char *MushGameMessageCollision::AutoName(void) const
{
    return "MushGameMessageCollision";
}

MushcoreVirtualObject *MushGameMessageCollision::AutoClone(void) const
{
    return new MushGameMessageCollision(*this);
}

MushcoreVirtualObject *MushGameMessageCollision::AutoCreate(void) const
{
    return new MushGameMessageCollision;
}

MushcoreVirtualObject *MushGameMessageCollision::AutoVirtualFactory(void)
{
    return new MushGameMessageCollision;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMessageCollision", MushGameMessageCollision::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMessageCollision::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameMessage::AutoPrint(ioOut);
    ioOut << "objectName1=" << m_objectName1 << ", ";
    ioOut << "objectName2=" << m_objectName2 << ", ";
    if (m_piece1 == NULL)
    {
        ioOut << "piece1=NULL"  << ", ";
    }
    else
    {
        ioOut << "piece1=" << *m_piece1 << ", ";
    }
    if (m_piece2 == NULL)
    {
        ioOut << "piece2=NULL"  << ", ";
    }
    else
    {
        ioOut << "piece2=" << *m_piece2 << ", ";
    }
    ioOut << "chunkNum1=" << m_chunkNum1 << ", ";
    ioOut << "chunkNum2=" << m_chunkNum2 << ", ";
    ioOut << "collisionPoint=" << m_collisionPoint << ", ";
    ioOut << "chunkNumsValid=" << m_chunkNumsValid << ", ";
    ioOut << "piecesValid=" << m_piecesValid << ", ";
    ioOut << "collisionPointValid=" << m_collisionPointValid;
    ioOut << "]";
}
bool
MushGameMessageCollision::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "objectName1")
    {
        ioIn >> m_objectName1;
    }
    else if (inTagStr == "objectName2")
    {
        ioIn >> m_objectName2;
    }
    else if (inTagStr == "piece1")
    {
        ioIn >> m_piece1;
    }
    else if (inTagStr == "piece2")
    {
        ioIn >> m_piece2;
    }
    else if (inTagStr == "chunkNum1")
    {
        ioIn >> m_chunkNum1;
    }
    else if (inTagStr == "chunkNum2")
    {
        ioIn >> m_chunkNum2;
    }
    else if (inTagStr == "collisionPoint")
    {
        ioIn >> m_collisionPoint;
    }
    else if (inTagStr == "chunkNumsValid")
    {
        ioIn >> m_chunkNumsValid;
    }
    else if (inTagStr == "piecesValid")
    {
        ioIn >> m_piecesValid;
    }
    else if (inTagStr == "collisionPointValid")
    {
        ioIn >> m_collisionPointValid;
    }
    else if (MushGameMessage::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameMessageCollision::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameMessage::AutoXMLPrint(ioOut);
    ioOut.TagSet("objectName1");
    ioOut << m_objectName1;
    ioOut.TagSet("objectName2");
    ioOut << m_objectName2;
    ioOut.TagSet("piece1");
    ioOut << m_piece1;
    ioOut.TagSet("piece2");
    ioOut << m_piece2;
    ioOut.TagSet("chunkNum1");
    ioOut << m_chunkNum1;
    ioOut.TagSet("chunkNum2");
    ioOut << m_chunkNum2;
    ioOut.TagSet("collisionPoint");
    ioOut << m_collisionPoint;
    ioOut.TagSet("chunkNumsValid");
    ioOut << m_chunkNumsValid;
    ioOut.TagSet("piecesValid");
    ioOut << m_piecesValid;
    ioOut.TagSet("collisionPointValid");
    ioOut << m_collisionPointValid;
}
//%outOfLineFunctions } kVk8++XNoa9VBYTtQsZh5A
