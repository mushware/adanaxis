//%includeGuardStart {
#ifndef MUSHPIESIGNALNUMERIC_H
#define MUSHPIESIGNALNUMERIC_H
//%includeGuardStart } GfddsmMvUhs6Hi7kTC+NGA
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieSignalNumeric.h
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
//%Header } LARyaYakJvmmuoenKLjBTA
/*
 * $Id: MushPieSignalNumeric.h,v 1.6 2006/06/01 15:39:37 southa Exp $
 * $Log: MushPieSignalNumeric.h,v $
 * Revision 1.6  2006/06/01 15:39:37  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/06/20 14:30:38  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.3  2005/02/10 12:34:17  southa
 * Template fixes
 *
 * Revision 1.2  2005/02/03 21:03:06  southa
 * Build fixes
 *
 * Revision 1.1  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
 */

#include "MushPieStandard.h"

#include "MushPieSignal.h"

//:generate virtual standard ostream xml1
class MushPieSignalNumeric : public MushPieSignal
{
public:
    MushPieSignalNumeric() : m_eventNumber(0) {}
    explicit MushPieSignalNumeric(Mushware::U32 inEventNumber) : m_eventNumber(inEventNumber) {}
    virtual ~MushPieSignalNumeric() {}
    
private:
    Mushware::U32 m_eventNumber; //:read
//%classPrototypes {
public:
    const Mushware::U32& EventNumber(void) const { return m_eventNumber; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } egGqU3I0I02Erbk8xb1a9A
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushPieSignalNumeric& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } woqyvkQc0XgwBloUTmMO1A
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
