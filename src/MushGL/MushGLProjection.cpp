//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLProjection.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } HnW+KGSjTFB4x1i0dy0ddQ
/*
 * $Id: MushGLProjection.cpp,v 1.7 2006/07/25 20:31:03 southa Exp $
 * $Log: MushGLProjection.cpp,v $
 * Revision 1.7  2006/07/25 20:31:03  southa
 * Scanner work
 *
 * Revision 1.6  2006/07/24 18:46:49  southa
 * Depth sorting
 *
 * Revision 1.5  2006/06/01 15:39:18  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/07/05 16:35:53  southa
 * Adanaxis work
 *
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
    
    m_aspectRatio = inAspect;
    
    m_mattress.MatrixSet(t4x4Val(t4Val(fValue/inAspect, 0,      0,  0),
                                 t4Val(0,               fValue, 0,  0),
                                 t4Val(0,               0,      0,  (inFar+inNear)/(inNear-inFar)),
                                 t4Val(0,               0,      0,  -1)));
    m_mattress.OffsetSet(t4Val(0, 0, 2*inFar*inNear/(inNear - inFar), 0));    

    /* In these clip values, x y and z are proportional (the boundary is value = x/w)
     * and the w value is absolute
     */
    m_clipMin = t4Val(
        -tan(m_viewHalfRadians) * inAspect,
        -tan(m_viewHalfRadians),
        -tan(m_viewHalfRadians),
        inNear);
    
    m_clipMax = t4Val(
        tan(m_viewHalfRadians) * inAspect,
        tan(m_viewHalfRadians),
        tan(m_viewHalfRadians),
        inFar);
    
    m_boundingRadiusFactor = t4Val(
        1 / cos(m_viewHalfRadians),
        1 / cos(m_viewHalfRadians),
        1 / cos(m_viewHalfRadians),
        1);
    
#if  0
    // Pull cull boundaries in a bit for debugging
    m_clipMin *= 0.9;                   
    m_clipMax *= 0.9;                   
#endif
}

Mushware::tVal
MushGLProjection::XHalfAngle(void) const
{
    return atan(m_aspectRatio * tan(m_viewHalfRadians));
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
    ioOut << "mattress=" << m_mattress << ", ";
    ioOut << "clipMin=" << m_clipMin << ", ";
    ioOut << "clipMax=" << m_clipMax << ", ";
    ioOut << "boundingRadiusFactor=" << m_boundingRadiusFactor << ", ";
    ioOut << "aspectRatio=" << m_aspectRatio;
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
    else if (inTagStr == "clipMin")
    {
        ioIn >> m_clipMin;
    }
    else if (inTagStr == "clipMax")
    {
        ioIn >> m_clipMax;
    }
    else if (inTagStr == "boundingRadiusFactor")
    {
        ioIn >> m_boundingRadiusFactor;
    }
    else if (inTagStr == "aspectRatio")
    {
        ioIn >> m_aspectRatio;
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
    ioOut.TagSet("clipMin");
    ioOut << m_clipMin;
    ioOut.TagSet("clipMax");
    ioOut << m_clipMax;
    ioOut.TagSet("boundingRadiusFactor");
    ioOut << m_boundingRadiusFactor;
    ioOut.TagSet("aspectRatio");
    ioOut << m_aspectRatio;
}
//%outOfLineFunctions } aRCQwz6d9srVJ/Kp2GxwPQ
