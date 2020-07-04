//%includeGuardStart {
#ifndef MUSHPIEFORM_H
#define MUSHPIEFORM_H
//%includeGuardStart } chr+rdZQI8cOcPal/mrI9Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieForm.h
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
//%Header } cc9V/UubmAXip+N9HN7+2g
/*
 * $Id: MushPieForm.h,v 1.6 2006/06/01 15:39:36 southa Exp $
 * $Log: MushPieForm.h,v $
 * Revision 1.6  2006/06/01 15:39:36  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/05/19 13:02:12  southa
 * Mac release work
 *
 * Revision 1.3  2005/02/10 12:34:12  southa
 * Template fixes
 *
 * Revision 1.2  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
 * Revision 1.1  2004/01/06 10:08:51  southa
 * MushcoreData and MushPieForm work
 *
 */

#include "MushPieStandard.h"

class MushPieSignal;

//:generate virtual standard ostream xml1
class MushPieForm : public MushcoreVirtualObject
{
public:
    typedef MushcoreData<MushPieForm, Mushware::U32> tData;
    typedef MushcoreDataRef<MushPieForm, Mushware::U32> tDataRef;
    
    MushPieForm() {}
    virtual ~MushPieForm() {}
    
    virtual void SignalHandle(const MushPieSignal& inSignal);
    virtual void WriteableSignalHandle(MushPieSignal& inSignal);
    
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
operator<<(std::ostream& ioOut, const MushPieForm& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } t8f6LLmjLkfX4mZD/ckOag
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
