//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLKeys.cpp
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
//%Header } Kb0HMFA2q5I75SSOqKIO8A
/*
 * $Id: GLKeys.cpp,v 1.13 2005/07/06 19:08:26 southa Exp $
 * $Log: GLKeys.cpp,v $
 * Revision 1.13  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.12  2005/05/19 13:01:59  southa
 * Mac release work
 *
 * Revision 1.11  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.10  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.9  2003/08/21 23:08:21  southa
 * Fixed file headers
 *
 * Revision 1.8  2002/12/29 20:59:52  southa
 * More build fixes
 *
 * Revision 1.7  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/10/22 20:42:00  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/31 15:18:16  southa
 * Keyboard reading
 *
 */

#include "GLKeys.h"

using namespace Mushware;
using namespace std;

//%outOfLineFunctions {

const char *GLKeys::AutoName(void) const
{
    return "GLKeys";
}

MushcoreVirtualObject *GLKeys::AutoClone(void) const
{
    return new GLKeys(*this);
}

MushcoreVirtualObject *GLKeys::AutoCreate(void) const
{
    return new GLKeys;
}

MushcoreVirtualObject *GLKeys::AutoVirtualFactory(void)
{
    return new GLKeys;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("GLKeys", GLKeys::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
GLKeys::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "keyValue=" << m_keyValue;
    ioOut << "]";
}
bool
GLKeys::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "keyValue")
    {
        ioIn >> m_keyValue;
    }
    else 
    {
        return false;
    }
    return true;
}
void
GLKeys::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("keyValue");
    ioOut << m_keyValue;
}
//%outOfLineFunctions } QApUFO08KObKyp5ixpqcrw
