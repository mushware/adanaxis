//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieSignal.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } zkVIx1LMcueJssUA2krrMw
/*
 * $Id: MushPieSignal.cpp,v 1.1 2004/01/10 20:29:35 southa Exp $
 * $Log: MushPieSignal.cpp,v $
 * Revision 1.1  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
 */

#include "MushPieSignal.h"

//%outOfLineFunctions {

const char *MushPieSignal::AutoNameGet(void) const
{
    return "MushPieSignal";
}

MushcoreVirtualObject *MushPieSignal::AutoClone(void) const
{
    return new MushPieSignal(*this);
}

MushcoreVirtualObject *MushPieSignal::AutoCreate(void) const
{
    return new MushPieSignal;
}

MushcoreVirtualObject *MushPieSignal::AutoVirtualFactory(void)
{
    return new MushPieSignal;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushPieSignal", MushPieSignal::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushPieSignal::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushPieSignal::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushPieSignal::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } 4ENMPWYAGfmdW/VbDEko+w
