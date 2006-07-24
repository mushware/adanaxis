//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLCamera.cpp
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
//%Header } wyTdNVvaLGbgZdVFyUp6lA
/*
 * $Id$
 * $Log$
 */

#include "MushGLCamera.h"

MushGLCamera::~MushGLCamera()
{
}
//%outOfLineFunctions {

const char *MushGLCamera::AutoName(void) const
{
    return "MushGLCamera";
}

MushcoreVirtualObject *MushGLCamera::AutoClone(void) const
{
    return new MushGLCamera(*this);
}

MushcoreVirtualObject *MushGLCamera::AutoCreate(void) const
{
    return new MushGLCamera;
}

MushcoreVirtualObject *MushGLCamera::AutoVirtualFactory(void)
{
    return new MushGLCamera;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLCamera", MushGLCamera::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLCamera::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "post=" << m_post << ", ";
    ioOut << "projection=" << m_projection;
    ioOut << "]";
}
bool
MushGLCamera::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "post")
    {
        ioIn >> m_post;
    }
    else if (inTagStr == "projection")
    {
        ioIn >> m_projection;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLCamera::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("post");
    ioOut << m_post;
    ioOut.TagSet("projection");
    ioOut << m_projection;
}
//%outOfLineFunctions } Tl3Bd5czjEMqcliSZkP7SA
