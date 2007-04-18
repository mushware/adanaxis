//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLJob.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } MroCoGN/qF111k2bZ4o4Vw
/*
 * $Id: MushGLJob.cpp,v 1.2 2006/06/01 15:39:17 southa Exp $
 * $Log: MushGLJob.cpp,v $
 * Revision 1.2  2006/06/01 15:39:17  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 */

#include "MushGLJob.h"

//%outOfLineFunctions {

const char *MushGLJob::AutoName(void) const
{
    return "MushGLJob";
}

MushcoreVirtualObject *MushGLJob::AutoClone(void) const
{
    return new MushGLJob(*this);
}

MushcoreVirtualObject *MushGLJob::AutoCreate(void) const
{
    return new MushGLJob;
}

MushcoreVirtualObject *MushGLJob::AutoVirtualFactory(void)
{
    return new MushGLJob;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLJob", MushGLJob::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLJob::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushGLJob::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushGLJob::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } ZDzrkr4i8K59cOdOA+iKrw
