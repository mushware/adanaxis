//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerPixelSource.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 6KMKKMCFz/p4gUdf1i7nYw
/*
 * $Id$
 * $Log$
 */

#include "TesseractTrainerPixelSource.h"

using namespace Mushware;
using namespace std;

void
TesseractTrainerPixelSource::ParameterSet(Mushware::U32 inNum, Mushware::tLongVal inVal)
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
            msg << "TesseractTrainerPixelSource::ParameterSet: Unknown paramerer: " << inNum;
            throw MushcoreRequestFail(msg.str());
        }
    }
}

void
TesseractTrainerPixelSource::BufferFill(Mushware::U32 * const outPtr, const Mushware::t2U32 inSize) const
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
        U32 *destPtr = &outPtr[y * inSize.X()];
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
            *destPtr++ = 0xffffff00 | (static_cast<U32>(alpha * 0xff));
            if (x == 0 || x == 127 || x == 128 || x == 255)
            {
                //cout << "orig. vert=" << t3Val(x, y, 1) << ", vert=" << vert << "alpha=" << alpha << endl;   
            }
        }
    }
}

//%outOfLineFunctions {

const char *TesseractTrainerPixelSource::AutoNameGet(void) const
{
    return "TesseractTrainerPixelSource";
}

MushcoreVirtualObject *TesseractTrainerPixelSource::AutoClone(void) const
{
    return new TesseractTrainerPixelSource(*this);
}

MushcoreVirtualObject *TesseractTrainerPixelSource::AutoCreate(void) const
{
    return new TesseractTrainerPixelSource;
}

MushcoreVirtualObject *TesseractTrainerPixelSource::AutoVirtualFactory(void)
{
    return new TesseractTrainerPixelSource;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("TesseractTrainerPixelSource", TesseractTrainerPixelSource::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
TesseractTrainerPixelSource::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGLPixelSource::AutoPrint(ioOut);
    ioOut << "frameTime=" << m_frameTime << ", ";
    ioOut << "colour=" << m_colour << ", ";
    ioOut << "seed=" << m_seed;
    ioOut << "]";
}
bool
TesseractTrainerPixelSource::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
TesseractTrainerPixelSource::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGLPixelSource::AutoXMLPrint(ioOut);
    ioOut.TagSet("frameTime");
    ioOut << m_frameTime;
    ioOut.TagSet("colour");
    ioOut << m_colour;
    ioOut.TagSet("seed");
    ioOut << m_seed;
}
//%outOfLineFunctions } 2rnWar+ryFb47cBm2you2w
