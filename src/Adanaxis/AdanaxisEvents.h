//%includeGuardStart {
#ifndef ADANAXISEVENTS_H
#define ADANAXISEVENTS_H
//%includeGuardStart } PFClCvea6tI3loXKhvRBhA
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisEvents.h
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
//%Header } /0/aMsWocssuxoRI2taq2w
/*
 * $Id: AdanaxisEvents.h,v 1.4 2007/06/14 01:03:52 southa Exp $
 * $Log: AdanaxisEvents.h,v $
 * Revision 1.4  2007/06/14 01:03:52  southa
 * win32 build fixes
 *
 * Revision 1.3  2007/04/18 09:22:00  southa
 * Header and level fixes
 *
 * Revision 1.2  2006/11/03 18:46:33  southa
 * Damage effectors
 *
 * Revision 1.1  2006/11/02 09:47:33  southa
 * Player weapon control
 *
 */

#include "AdanaxisStandard.h"

//:generate virtual standard ostream xml1
class AdanaxisEvents : public MushcoreVirtualObject, public MushcoreSingleton<AdanaxisEvents>
{
public:
    virtual ~AdanaxisEvents() {}
    
    MushRubyValue EventFireMake(const MushMeshPosticity& inPost);
    MushRubyValue EventKeyStateMake(void);
    void EventKeyStateAddState(MushRubyValue& ioEvent, Mushware::U32 inNum, bool inState);
    
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
operator<<(std::ostream& ioOut, const AdanaxisEvents& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 26CeuLmW+qc4ymzqMBFIPg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
