//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieForm.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } vqABr3CLkwVzCFoXq7BXTQ
/*
 * $Id: MushPieForm.cpp,v 1.1 2004/01/06 10:08:51 southa Exp $
 * $Log: MushPieForm.cpp,v $
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
const char *MushPieForm::AutoNameGet(void) const
{
    return "MushPieForm";
}
MushPieForm *MushPieForm::AutoClone(void) const
{
    return new MushPieForm(*this);
}
MushPieForm *MushPieForm::AutoCreate(void) const
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
        ioIn >> *this;
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
//%outOfLineFunctions } rbAMOT7836I5GAKf9zYSSw
