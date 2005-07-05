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
 * $Id: MushGLProjection.cpp,v 1.3 2005/07/04 11:10:43 southa Exp $
 * $Log: MushGLProjection.cpp,v $
 * Revision 1.3  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 * Revision 1.2  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.1  2005/07/01 10:03:30  southa
 * Projection work
 *
 */

#include "MushGLProjection.h"

using namespace Mushware;
using namespace std;

Mushware::tVal
MushGLProjection::FValueFromViewHalfRadians(Mushware::tVal inRadians) const
{
    if (inRadians < 0 || inRadians > M_PI/2)
    {
        throw MushcoreDataFail("View half angle out of range");
    }
    return 1/std::tan(inRadians);
}

void
MushGLProjection::FromAspectNearFarMake(Mushware::tVal inAspect, Mushware::tVal inNear, Mushware::tVal inFar)
{
    tVal fValue = FValueFromViewHalfRadians(m_viewHalfRadians);
    
    if (inAspect == 0 || inNear == 0 || inNear == inFar)
    {
        throw MushcoreDataFail("Bad values for projection");
    }
    
    m_mattress.MatrixSet(t4x4Val(t4Val(fValue/inAspect, 0,      0,  0),
                                 t4Val(0,               fValue, 0,  0),
                                 t4Val(0,               0,      0,  (inFar+inNear)/(inNear-inFar)),
                                 t4Val(0,               0,      0,  -1)));
    m_mattress.OffsetSet(t4Val(0, 0, 2*inFar*inNear/(inNear - inFar), 0));    
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
    ioOut << "viewHalfRadians=" << m_viewHalfRadians << ", ";
    ioOut << "mattress=" << m_mattress;
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
    else if (inTagStr == "viewHalfRadians")
    {
        ioIn >> m_viewHalfRadians;
    }
    else if (inTagStr == "mattress")
    {
        ioIn >> m_mattress;
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
    ioOut.TagSet("viewHalfRadians");
    ioOut << m_viewHalfRadians;
    ioOut.TagSet("mattress");
    ioOut << m_mattress;
}
//%outOfLineFunctions } YEDUaNmiEL8/fzIbpMKyVA
