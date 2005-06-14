//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPixelSource.cpp
 *
 * Copyright: Andy Southgate 2005
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } do/pC4WFtsQItE9mWclSaw
/*
 * $Id: AdanaxisPixelSource.cpp,v 1.1 2005/06/13 17:34:54 southa Exp $
 * $Log: AdanaxisPixelSource.cpp,v $
 * Revision 1.1  2005/06/13 17:34:54  southa
 * Adanaxis creation
 *
 */

#include "AdanaxisPixelSource.h"

using namespace Mushware;
using namespace std;

void
AdanaxisPixelSource::ParameterSet(Mushware::U32 inNum, Mushware::tLongVal inVal)
{
    switch (inNum)
    {
        case kParamRed:
            m_colour.XSet(inVal);
            break;
            
        case kParamGreen:
            m_colour.YSet(inVal);
            break;
            
        case kParamBlue:
            m_colour.ZSet(inVal);
            break;
            
        case kParamAlpha:
            m_colour.WSet(inVal);
            break;
            
        case kParamSeed:
            m_seed = inVal;
            break;
            
        case kParamFrameTime:
            m_frameTime = inVal;
            break;
            
        default:
        {
            ostringstream msg;
            msg << "AdanaxisPixelSource::ParameterSet: Unknown paramerer: " << inNum;
            throw MushcoreRequestFail(msg.str());
        }
    }
}

void
AdanaxisPixelSource::BufferFill(Mushware::U32 * const outPtr, const Mushware::t2U32 inSize) const
{
    tVal scale = static_cast<tVal>(std::max(inSize.X(), inSize.Y())) / std::sqrt(2.0);
    tVal scale_m1 = static_cast<tVal>(std::max(inSize.X(), inSize.Y()) - 1) / std::sqrt(2.0);
    //cout << "scale=" <<scale << endl;
    t3x3Val transform(t3Val(1/scale_m1, 0, -(inSize.X()/(2*scale))),
                      t3Val(0, 1/scale_m1, -(inSize.Y()/(2*scale))),
                      t3Val(0, 0, 1));
    //cout << "transform=" << transform << endl;
    //cout << "inSize=" << inSize << endl;

    for (U32 y=0; y<inSize.Y(); ++y)
    {
        U8 *destPtr = reinterpret_cast<U8 *>(&outPtr[y * inSize.X()]);
        for (U32 x=0; x<inSize.X(); ++x)
        {
            t3Val vert(x, y, 1);
            vert = transform * vert;
            tVal alpha = 1 - std::sqrt(vert.X() * vert.X() + vert.Y() * vert.Y());

            alpha *= 0.7+0.3*(alpha + (1-alpha)*sin(7*std::atan2(vert.X(), vert.Y())));
            
            alpha = std::pow(alpha, 2);
            alpha -= ((double)rand() / RAND_MAX) * 0.05;

            if (alpha < 0) alpha = 0;
            if (alpha > 1.0) alpha = 1.0;
            
            if (x == 0 || x+1 == inSize.X() || y == 0 || y+1 == inSize.Y())
            {
                //alpha = 1;     
            }
            *destPtr++ = 0xff;
            *destPtr++ = 0xff;
            *destPtr++ = 0xff;
            *destPtr++ = static_cast<U8>(alpha * 0xff);
            if (x == 0 || x == 127 || x == 128 || x == 255)
            {
                //cout << "orig. vert=" << t3Val(x, y, 1) << ", vert=" << vert << "alpha=" << alpha << endl;   
            }
        }
    }
}

//%outOfLineFunctions {

const char *AdanaxisPixelSource::AutoNameGet(void) const
{
    return "AdanaxisPixelSource";
}

MushcoreVirtualObject *AdanaxisPixelSource::AutoClone(void) const
{
    return new AdanaxisPixelSource(*this);
}

MushcoreVirtualObject *AdanaxisPixelSource::AutoCreate(void) const
{
    return new AdanaxisPixelSource;
}

MushcoreVirtualObject *AdanaxisPixelSource::AutoVirtualFactory(void)
{
    return new AdanaxisPixelSource;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisPixelSource", AdanaxisPixelSource::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisPixelSource::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGLPixelSource::AutoPrint(ioOut);
    ioOut << "frameTime=" << m_frameTime << ", ";
    ioOut << "colour=" << m_colour << ", ";
    ioOut << "seed=" << m_seed;
    ioOut << "]";
}
bool
AdanaxisPixelSource::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "frameTime")
    {
        ioIn >> m_frameTime;
    }
    else if (inTagStr == "colour")
    {
        ioIn >> m_colour;
    }
    else if (inTagStr == "seed")
    {
        ioIn >> m_seed;
    }
    else if (MushGLPixelSource::AutoXMLDataProcess(ioIn, inTagStr))
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
AdanaxisPixelSource::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGLPixelSource::AutoXMLPrint(ioOut);
    ioOut.TagSet("frameTime");
    ioOut << m_frameTime;
    ioOut.TagSet("colour");
    ioOut << m_colour;
    ioOut.TagSet("seed");
    ioOut << m_seed;
}
//%outOfLineFunctions } WvdY9iFnRQD5vHZI9xV6Jw
