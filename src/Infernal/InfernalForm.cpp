//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalForm.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } +yOg9P9RkziFVgQl5vriGg
/*
 * $Id$
 * $Log$
 */

#include "InfernalForm.h"

//%outOfLineFunctions {
const char *InfernalForm::AutoNameGet(void) const
{
    return "InfernalForm";
}
InfernalForm *InfernalForm::AutoClone(void) const
{
    return new InfernalForm(*this);
}
InfernalForm *InfernalForm::AutoCreate(void) const
{
    return new InfernalForm;
}
MushcoreVirtualObject *InfernalForm::AutoVirtualFactory(void)
{
    return new InfernalForm;
}
namespace
{
void Install(void)
{
    MushcoreFactory::Sgl().FactoryAdd("InfernalForm", InfernalForm::AutoVirtualFactory);
}
MushcoreInstaller Installer(Install);
} // end anonymous namespace
void
InfernalForm::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushPieForm::AutoPrint(ioOut);
    ioOut << "modelRef=" << m_modelRef;
    ioOut << "]";
}
bool
InfernalForm::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "modelRef")
    {
        ioIn >> m_modelRef;
    }
    else if (MushPieForm::AutoXMLDataProcess(ioIn, inTagStr))
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
InfernalForm::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushPieForm::AutoXMLPrint(ioOut);
    ioOut.TagSet("modelRef");
    ioOut << m_modelRef;
}
//%outOfLineFunctions } sJr9DmEMjb6YHg11fb0Cxw
