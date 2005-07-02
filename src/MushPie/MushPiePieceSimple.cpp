//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePieceSimple.cpp
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
//%Header } BZiJCDiOBWqtsOyCjq4lrA
/*
 * $Id: MushPiePieceSimple.cpp,v 1.8 2005/06/20 14:30:37 southa Exp $
 * $Log: MushPiePieceSimple.cpp,v $
 * Revision 1.8  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.7  2005/06/16 17:25:40  southa
 * Client/server work
 *
 * Revision 1.6  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.5  2005/02/10 12:34:14  southa
 * Template fixes
 *
 * Revision 1.4  2004/09/27 22:42:10  southa
 * MSVC compilation fixes
 *
 * Revision 1.3  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 * Revision 1.2  2004/01/04 14:36:37  southa
 * Handle 'inline' in source conditioner
 *
 * Revision 1.1  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 */

#include "MushPiePieceSimple.h"

//%outOfLineFunctions {

const char *MushPiePieceSimple::AutoName(void) const
{
    return "MushPiePieceSimple";
}

MushcoreVirtualObject *MushPiePieceSimple::AutoClone(void) const
{
    return new MushPiePieceSimple(*this);
}

MushcoreVirtualObject *MushPiePieceSimple::AutoCreate(void) const
{
    return new MushPiePieceSimple;
}

MushcoreVirtualObject *MushPiePieceSimple::AutoVirtualFactory(void)
{
    return new MushPiePieceSimple;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushPiePieceSimple", MushPiePieceSimple::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushPiePieceSimple::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushPiePiece::AutoPrint(ioOut);
    ioOut << "pos=" << m_pos;
    ioOut << "]";
}
bool
MushPiePieceSimple::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "pos")
    {
        ioIn >> m_pos;
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
MushPiePieceSimple::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushPiePiece::AutoXMLPrint(ioOut);
    ioOut.TagSet("pos");
    ioOut << m_pos;
}
//%outOfLineFunctions } 8Ha57RgHInH3ZQdWoV+seg
