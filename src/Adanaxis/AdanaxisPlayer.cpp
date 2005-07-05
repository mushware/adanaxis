//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPlayer.cpp
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
//%Header } ow0iEi0s5HhumBjS38PxOA
/*
 * $Id: AdanaxisPlayer.cpp,v 1.4 2005/07/04 15:59:00 southa Exp $
 * $Log: AdanaxisPlayer.cpp,v $
 * Revision 1.4  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.3  2005/07/02 00:42:36  southa
 * Conditioning tweaks
 *
 * Revision 1.2  2005/06/23 17:25:24  southa
 * MushGame link work
 *
 * Revision 1.1  2005/06/20 14:46:41  southa
 * Adanaxis work
 *
 */

#include "AdanaxisPlayer.h"

using namespace Mushware;
using namespace std;

AdanaxisPlayer::AdanaxisPlayer(const std::string& inPlayerID) :
    MushGamePlayer(inPlayerID)
{
    PostWRef().PosSet(t4Val(0,0,0,20));
}

//%outOfLineFunctions {

const char *AdanaxisPlayer::AutoName(void) const
{
    return "AdanaxisPlayer";
}

MushcoreVirtualObject *AdanaxisPlayer::AutoClone(void) const
{
    return new AdanaxisPlayer(*this);
}

MushcoreVirtualObject *AdanaxisPlayer::AutoCreate(void) const
{
    return new AdanaxisPlayer;
}

MushcoreVirtualObject *AdanaxisPlayer::AutoVirtualFactory(void)
{
    return new AdanaxisPlayer;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisPlayer", AdanaxisPlayer::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisPlayer::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGamePlayer::AutoPrint(ioOut);
    ioOut << "postManip=" << m_postManip;
    ioOut << "]";
}
bool
AdanaxisPlayer::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "postManip")
    {
        ioIn >> m_postManip;
    }
    else if (MushGamePlayer::AutoXMLDataProcess(ioIn, inTagStr))
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
AdanaxisPlayer::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGamePlayer::AutoXMLPrint(ioOut);
    ioOut.TagSet("postManip");
    ioOut << m_postManip;
}
//%outOfLineFunctions } 8a3ZQQ1VuL7/gplsOwseXg
