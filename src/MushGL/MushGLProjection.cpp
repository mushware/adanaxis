//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLProjection.cpp
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
//%Header } YhOMN0lltAKj2CZMFJS+0A
/*
 * $Id$
 * $Log$
 */

#include "MushGLProjection.h"

using namespace Mushware;
using namespace std;

Mushware::tVal
MushGLProjection::FValueFromViewHalfRadians(Mushware::tVal inRadians)
{
    if (inRadians < 0 || inRadians > M_PI/2)
    {
        throw MushcoreDataFail("View half angle out of range");
    }
    return 1/std::tan(inRadians);
}


void
MushGLProjection::FromFAspectNearFarMake(Mushware::tVal inF, Mushware::tVal inAspect, Mushware::tVal inNear, Mushware::tVal inFar)
{
    if (inAspect == 0 || inNear == 0 || inNear == inFar)
    {
        throw MushcoreDataFail("Bad values for projection");
    }
    
    m_matrix = t4x4Val(t4Val(inF/inAspect, 0,   0,  0),
                       t4Val(0,            inF, 0,  0),
                       t4Val(0,            0,   0,  (inFar+inNear)/(inNear-inFar)),
                       t4Val(0,            0,   0,  -1));
    m_offset = t4Val(0, 0, 2*inFar*inNear/(inNear - inFar), 0);    
}
//%outOfLineFunctions {

const char *MushGLProjection::AutoName(void) const
{
    return "MushGLProjection";
}

MushcoreVirtualObject *MushGLProjection::AutoClone(void) const
{
    return new MushGLProjection(*this);
}

MushcoreVirtualObject *MushGLProjection::AutoCreate(void) const
{
    return new MushGLProjection;
}

MushcoreVirtualObject *MushGLProjection::AutoVirtualFactory(void)
{
    return new MushGLProjection;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLProjection", MushGLProjection::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLProjection::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "matrix=" << m_matrix << ", ";
    ioOut << "offset=" << m_offset;
    ioOut << "]";
}
bool
MushGLProjection::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "matrix")
    {
        ioIn >> m_matrix;
    }
    else if (inTagStr == "offset")
    {
        ioIn >> m_offset;
    }
    else
    {
        return false;
    }
    return true;
}
void
MushGLProjection::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("matrix");
    ioOut << m_matrix;
    ioOut.TagSet("offset");
    ioOut << m_offset;
}
//%outOfLineFunctions } 5zdpVltsmRAHgk/ED/fQ4g
