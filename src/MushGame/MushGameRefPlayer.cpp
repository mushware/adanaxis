//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameRefPlayer.cpp
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
//%Header } ETJO/YTdNnJBUtnyOyRe/A
/*
 * $Id: MushGameRefPlayer.cpp,v 1.3 2005/07/02 00:42:38 southa Exp $
 * $Log: MushGameRefPlayer.cpp,v $
 * Revision 1.3  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.2  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 * Revision 1.1  2005/06/29 09:07:56  southa
 * MushGame camera work
 *
 */

#include "MushGameRefPlayer.h"

using namespace Mushware;
using namespace std;

MushGameRefPlayer::MushGameRefPlayer(const std::string& inName, MushcoreData<MushGamePlayer> *inInstance) :
    m_playerRef(inName, *inInstance)
{
}

//%outOfLineFunctions {

const char *MushGameRefPlayer::AutoName(void) const
{
    return "MushGameRefPlayer";
}

MushcoreVirtualObject *MushGameRefPlayer::AutoClone(void) const
{
    return new MushGameRefPlayer(*this);
}

MushcoreVirtualObject *MushGameRefPlayer::AutoCreate(void) const
{
    return new MushGameRefPlayer;
}

MushcoreVirtualObject *MushGameRefPlayer::AutoVirtualFactory(void)
{
    return new MushGameRefPlayer;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameRefPlayer", MushGameRefPlayer::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameRefPlayer::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameRef::AutoPrint(ioOut);
    ioOut << "playerRef=" << m_playerRef;
    ioOut << "]";
}
bool
MushGameRefPlayer::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "playerRef")
    {
        ioIn >> m_playerRef;
    }
    else if (MushGameRef::AutoXMLDataProcess(ioIn, inTagStr))
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
MushGameRefPlayer::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameRef::AutoXMLPrint(ioOut);
    ioOut.TagSet("playerRef");
    ioOut << m_playerRef;
}
//%outOfLineFunctions } 3r2e1FyW54Uq8+2Y8bl4rw
