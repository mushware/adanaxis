//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLResolverPixelSource.cpp
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
//%Header } 3ppT9q8gO5IVI+Nga13RUQ
/*
 * $Id$
 * $Log$
 */


#include "MushGLResolverPixelSource.h"

#include "MushGLPixelSourceTIFF.h"

MUSHCORE_SINGLETON_INSTANCE(MushGLResolverPixelSource);

using namespace Mushware;
using namespace std;

void
MushGLResolverPixelSource::Resolve(const std::string& inSrcName)
{
    MushcoreRegExp regExp;
    MushcoreRegExp::tMatches matches;
    regExp.SearchPatternSet("file=\"[^\"]+\\.tiff?\"");
    if (regExp.Search(matches, inSrcName))
    {
        
    }
    else
    {
        throw MushcoreRequestFail("Cannot resolve pixel source for '"+inSrcName+"'");   
    }
}

//%outOfLineFunctions {

const char *MushGLResolverPixelSource::AutoName(void) const
{
    return "MushGLResolverPixelSource";
}

MushcoreVirtualObject *MushGLResolverPixelSource::AutoClone(void) const
{
    throw MushcoreRequestFail("Cannot clone 'MushGLResolverPixelSource'");;
}

MushcoreVirtualObject *MushGLResolverPixelSource::AutoCreate(void) const
{
    return new MushGLResolverPixelSource;
}

MushcoreVirtualObject *MushGLResolverPixelSource::AutoVirtualFactory(void)
{
    return new MushGLResolverPixelSource;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLResolverPixelSource", MushGLResolverPixelSource::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLResolverPixelSource::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushGLResolverPixelSource::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushGLResolverPixelSource::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } qoplTn4svQXPIwDeos01Bw
