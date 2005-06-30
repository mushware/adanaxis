//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceDeco.cpp
 *
 * Copyright: Andy Southgate 2005
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } sexYl99zeFqxCTpAO8DLNQ
/*
 * $Id$
 * $Log$
 */

#include "AdanaxisPieceDeco.h"

using namespace Mushware;
using namespace std;

AdanaxisPieceDeco::AdanaxisPieceDeco(const std::string& inID) :
    m_id(inID)
{
    MushMesh4Library::Sgl().UnitTesseractCreate(m_mesh);
    PostWRef().PosSet(t4Val(0,0,0,-10));
}

void
AdanaxisPieceDeco::Render(MushGameLogic& ioLogic, const MushGameCamera& inCamera)
{
    cout << "Rendered" << endl;
}

//%outOfLineFunctions {

const char *AdanaxisPieceDeco::AutoName(void) const
{
    return "AdanaxisPieceDeco";
}

MushcoreVirtualObject *AdanaxisPieceDeco::AutoClone(void) const
{
    return new AdanaxisPieceDeco(*this);
}

MushcoreVirtualObject *AdanaxisPieceDeco::AutoCreate(void) const
{
    return new AdanaxisPieceDeco;
}

MushcoreVirtualObject *AdanaxisPieceDeco::AutoVirtualFactory(void)
{
    return new AdanaxisPieceDeco;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisPieceDeco", AdanaxisPieceDeco::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisPieceDeco::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGamePiece::AutoPrint(ioOut);
    ioOut << "id=" << m_id << ", ";
    ioOut << "mesh=" << m_mesh;
    ioOut << "]";
}
bool
AdanaxisPieceDeco::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "id")
    {
        ioIn >> m_id;
    }
    else if (inTagStr == "mesh")
    {
        ioIn >> m_mesh;
    }
    else if (MushGamePiece::AutoXMLDataProcess(ioIn, inTagStr))
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
AdanaxisPieceDeco::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGamePiece::AutoXMLPrint(ioOut);
    ioOut.TagSet("id");
    ioOut << m_id;
    ioOut.TagSet("mesh");
    ioOut << m_mesh;
}
//%outOfLineFunctions } neZ3KmlpqSp58Luj5M2Nsg
