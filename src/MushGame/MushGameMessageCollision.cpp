//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageCollision.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } 1v0gxN1HJj5gA6gMJ/jSTw
/*
 * $Id: MushGameMessageCollision.cpp,v 1.2 2006/06/01 15:39:24 southa Exp $
 * $Log: MushGameMessageCollision.cpp,v $
 * Revision 1.2  2006/06/01 15:39:24  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/08/01 13:09:58  southa
 * Collision messaging
 *
 */

#include "MushGameMessageCollision.h"

#include "MushGameIntern.h"

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
    ioOut << "chunkNumsValid=" << m_chunkNumsValid << ", ";
    ioOut << "piecesValid=" << m_piecesValid;
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
    else if (inTagStr == "chunkNumsValid")
    {
        ioIn >> m_chunkNumsValid;
    }
    else if (inTagStr == "piecesValid")
    {
        ioIn >> m_piecesValid;
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
    ioOut.TagSet("chunkNumsValid");
    ioOut << m_chunkNumsValid;
    ioOut.TagSet("piecesValid");
    ioOut << m_piecesValid;
}
//%outOfLineFunctions } VMsKkYm+ZSgVJZFxP7Af+g
