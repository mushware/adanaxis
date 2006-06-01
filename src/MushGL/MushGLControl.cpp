//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLControl.cpp
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
//%Header } UjhtJkQUdwY4VkI9vBO+rQ
/*
 * $Id: MushGLControl.cpp,v 1.4 2005/07/02 00:42:37 southa Exp $
 * $Log: MushGLControl.cpp,v $
 * Revision 1.4  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.3  2005/06/20 14:30:35  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/16 17:25:39  southa
 * Client/server work
 *
 * Revision 1.1  2005/06/13 17:35:37  southa
 * Adanaxis creation
 *
 */

#include "MushGLControl.h"

#include "mushMushcoreIO.h"


//%outOfLineFunctions {

const char *MushGLControl::AutoName(void) const
{
    return "MushGLControl";
}

MushcoreVirtualObject *MushGLControl::AutoClone(void) const
{
    return new MushGLControl(*this);
}

MushcoreVirtualObject *MushGLControl::AutoCreate(void) const
{
    return new MushGLControl;
}

MushcoreVirtualObject *MushGLControl::AutoVirtualFactory(void)
{
    return new MushGLControl;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLControl", MushGLControl::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLControl::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "timestamp=" << m_timestamp << ", ";
    ioOut << "keys=" << m_keys << ", ";
    ioOut << "axes=" << m_axes;
    ioOut << "]";
}
bool
MushGLControl::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "timestamp")
    {
        ioIn >> m_timestamp;
    }
    else if (inTagStr == "keys")
    {
        ioIn >> m_keys;
    }
    else if (inTagStr == "axes")
    {
        ioIn >> m_axes;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLControl::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("timestamp");
    ioOut << m_timestamp;
    ioOut.TagSet("keys");
    ioOut << m_keys;
    ioOut.TagSet("axes");
    ioOut << m_axes;
}
//%outOfLineFunctions } Ldo4MEjmsEEXQ6mtx/v8Dg
