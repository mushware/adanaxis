//%includeGuardStart {
#ifndef MUSHPIESIGNAL_H
#define MUSHPIESIGNAL_H
//%includeGuardStart } 4Ppb7qlwhe1x6KEcwB9Qug
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieSignal.h
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
//%Header } iaNd7fa6FYdJIVlA1RjRVg
/*
 * $Id: MushPieSignal.h,v 1.5 2006/06/01 15:39:37 southa Exp $
 * $Log: MushPieSignal.h,v $
 * Revision 1.5  2006/06/01 15:39:37  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.3  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.2  2005/02/10 12:34:16  southa
 * Template fixes
 *
 * Revision 1.1  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
 */

#include "MushPieStandard.h"

//:generate virtual standard ostream xml1
class MushPieSignal : public MushcoreVirtualObject
{
public:
    MushPieSignal() {}
    virtual ~MushPieSignal() {}
    
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
operator<<(std::ostream& ioOut, const MushPieSignal& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } U1OYYIdjfEmHGMjXtntbzw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
