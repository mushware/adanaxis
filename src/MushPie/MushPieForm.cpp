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
 * $Id$
 * $Log$
 */

#include "MushPieForm.h"

MUSHCORE_SINGLETON_INSTANCE(MushPieForm::tData); // Data instance

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
void Install(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushPieForm", MushPieForm::AutoVirtualFactory);
}
MushcoreInstaller Installer(Install);
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
//%outOfLineFunctions } E3pxFCNG4aHC8nXb4L80zg
