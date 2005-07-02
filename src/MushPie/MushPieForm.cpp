//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieForm.cpp
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
//%Header } 5btgIJdgvUud/9DtUw4GnQ
/*
 * $Id: MushPieForm.cpp,v 1.6 2005/06/20 14:30:37 southa Exp $
 * $Log: MushPieForm.cpp,v $
 * Revision 1.6  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.5  2005/06/16 17:25:39  southa
 * Client/server work
 *
 * Revision 1.4  2005/05/19 13:02:12  southa
 * Mac release work
 *
 * Revision 1.3  2005/02/10 12:34:12  southa
 * Template fixes
 *
 * Revision 1.2  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
 * Revision 1.1  2004/01/06 10:08:51  southa
 * MushcoreData and MushPieForm work
 *
 */

#include "MushPieForm.h"

#include "MushPieSignal.h"
#include "MushPieSTL.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MushPieForm::tData); // Data instance

void
MushPieForm::SignalHandle(const MushPieSignal& inSignal)
{
    ostringstream message;
    message << "Unhandled signal " << inSignal;
    throw MushcoreRequestFail(message.str());
}

void
MushPieForm::WriteableSignalHandle(MushPieSignal& inSignal)
{
    ostringstream message;
    message << "Unhandled signal " << inSignal;
    throw MushcoreRequestFail(message.str());
}

//%outOfLineFunctions {

const char *MushPieForm::AutoName(void) const
{
    return "MushPieForm";
}

MushcoreVirtualObject *MushPieForm::AutoClone(void) const
{
    return new MushPieForm(*this);
}

MushcoreVirtualObject *MushPieForm::AutoCreate(void) const
{
    return new MushPieForm;
}

MushcoreVirtualObject *MushPieForm::AutoVirtualFactory(void)
{
    return new MushPieForm;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushPieForm", MushPieForm::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushPieForm::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushPieForm::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushPieForm::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } g1wsfIKpSBNkWevX7X7gVA
