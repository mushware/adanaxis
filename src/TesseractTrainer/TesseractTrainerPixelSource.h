//%includeGuardStart {
#ifndef TESSERACTTRAINERPIXELSOURCE_H
#define TESSERACTTRAINERPIXELSOURCE_H
//%includeGuardStart } gElDVBoRlQ6Sx9Ax7eEBTA
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerPixelSource.h
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
//%Header } 3BKw1I0xWLg+EEwcrnfn1w
/*
 * $Id: TesseractTrainerPixelSource.h,v 1.6 2006/06/29 23:57:57 southa Exp $
 * $Log: TesseractTrainerPixelSource.h,v $
 * Revision 1.6  2006/06/29 23:57:57  southa
 * Mac OS X library fixes
 *
 * Revision 1.5  2006/06/01 15:40:00  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/07/02 00:42:39  southa
 * Conditioning tweaks
 *
 * Revision 1.3  2005/06/20 14:30:39  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/05/19 13:02:22  southa
 * Mac release work
 *
 * Revision 1.1  2005/02/13 22:44:08  southa
 * Tesseract stuff
 *
 */

#include "TesseractTrainerStandard.h"

#include "mushMushGL.h"

//:xml1base MushGLPixelSource
//:generate standard ostream xml1
class TesseractTrainerPixelSource : public MushGLPixelSource
{
public:
    virtual ~TesseractTrainerPixelSource() {}
    virtual void ParameterSet(const Mushware::U32 inNum, const Mushware::tLongVal inVal);
    virtual void BufferFill(Mushware::U32 * const outPtr, const Mushware::t2U32 inSize) const;

private:
        
//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const TesseractTrainerPixelSource& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Joj79H2bzCnOZ5wf0KNnLw

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
