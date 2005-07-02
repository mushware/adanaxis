//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieDialogue.cpp
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
//%Header } Jc7zA7p7ZQz1f9lxQyLUCw
/*
 * $Id: MushPieDialogue.cpp,v 1.4 2005/06/20 14:30:37 southa Exp $
 * $Log: MushPieDialogue.cpp,v $
 * Revision 1.4  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.3  2005/06/16 17:25:39  southa
 * Client/server work
 *
 * Revision 1.2  2005/05/19 13:02:12  southa
 * Mac release work
 *
 * Revision 1.1  2005/02/10 12:34:11  southa
 * Template fixes
 *
 */

#include "MushPieDialogue.h"

using namespace Mushware;
using namespace std;

MushPieDialogue::~MushPieDialogue()
{
}

void
MushPieDialogue::Render(void) const
{
}

void
MushPieDialogue::Move(void)
{
}

void
MushPieDialogue::TextSet(Mushware::U32 inWhich, const std::string& inStr)
{
}

void
MushPieDialogue::ExpireNow()
{
}

//%outOfLineFunctions {

const char *MushPieDialogue::AutoName(void) const
{
    return "MushPieDialogue";
}

MushcoreVirtualObject *MushPieDialogue::AutoClone(void) const
{
    return new MushPieDialogue(*this);
}

MushcoreVirtualObject *MushPieDialogue::AutoCreate(void) const
{
    return new MushPieDialogue;
}

MushcoreVirtualObject *MushPieDialogue::AutoVirtualFactory(void)
{
    return new MushPieDialogue;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushPieDialogue", MushPieDialogue::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushPieDialogue::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushPiePiece::AutoPrint(ioOut);
    ioOut << "age=" << m_age << ", ";
    ioOut << "expired=" << m_expired;
    ioOut << "]";
}
bool
MushPieDialogue::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "age")
    {
        ioIn >> m_age;
    }
    else if (inTagStr == "expired")
    {
        ioIn >> m_expired;
    }
    else if (MushPiePiece::AutoXMLDataProcess(ioIn, inTagStr))
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
MushPieDialogue::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushPiePiece::AutoXMLPrint(ioOut);
    ioOut.TagSet("age");
    ioOut << m_age;
    ioOut.TagSet("expired");
    ioOut << m_expired;
}
//%outOfLineFunctions } Cqf8rf1BxI1wCxPudieyqg
