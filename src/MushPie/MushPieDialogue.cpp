//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieDialogue.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } sAJkrqaKvPi/5OZ6pP++wA
/*
 * $Id$
 * $Log$
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

const char *MushPieDialogue::AutoNameGet(void) const
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
        ioIn >> *this;
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
//%outOfLineFunctions } UDOB44E6yQvn++YNR5OMAw
