//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerPixelSource.cpp
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
//%Header } CaiepSpvjjF04Fe8I90znA
/*
 * $Id: TesseractTrainerPixelSource.cpp,v 1.9 2006/12/14 00:33:50 southa Exp $
 * $Log: TesseractTrainerPixelSource.cpp,v $
 * Revision 1.9  2006/12/14 00:33:50  southa
 * Control fix and audio pacing
 *
 * Revision 1.8  2006/06/29 23:57:57  southa
 * Mac OS X library fixes
 *
 * Revision 1.7  2006/06/01 15:40:00  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/07/02 00:42:39  southa
 * Conditioning tweaks
 *
 * Revision 1.5  2005/06/20 14:30:39  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/06/16 17:25:41  southa
 * Client/server work
 *
 * Revision 1.3  2005/05/26 00:46:41  southa
 * Made buildable on win32
 *
 * Revision 1.2  2005/05/19 13:02:22  southa
 * Mac release work
 *
 * Revision 1.1  2005/02/13 22:44:08  southa
 * Tesseract stuff
 *
 */

#include "TesseractTrainerPixelSource.h"

using namespace Mushware;
using namespace std;

void
TesseractTrainerPixelSource::ParameterSet(Mushware::U32 inNum, Mushware::tLongVal inVal)
{
    switch (inNum)
    {
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

    t3x3Val transform(t3Val(1/scale_m1, 0, -(inSize.X()/(2*scale))),
                      t3Val(0, 1/scale_m1, -(inSize.Y()/(2*scale))),
                      t3Val(0, 0, 1));

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
        }
    }
}

//%outOfLineFunctions {

const char *TesseractTrainerPixelSource::AutoName(void) const
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
    ioOut << "]";
}
bool
TesseractTrainerPixelSource::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
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
}
//%outOfLineFunctions } azR1vFwZm7vQkaqCyXVHCg
