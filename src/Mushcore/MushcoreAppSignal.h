//%includeGuardStart {
#ifndef MUSHCOREAPPSIGNAL_H
#define MUSHCOREAPPSIGNAL_H
//%includeGuardStart } sxQ+5UlqoMWb/uAPaQW/yw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreAppSignal.h
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
//%Header } R9NQHz756ZSDD8FJSWyEcQ
/*
 * $Id: MushcoreAppSignal.h,v 1.8 2006/06/01 15:39:41 southa Exp $
 * $Log: MushcoreAppSignal.h,v $
 * Revision 1.8  2006/06/01 15:39:41  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/05/19 13:02:14  southa
 * Mac release work
 *
 * Revision 1.6  2004/01/02 21:13:12  southa
 * Source conditioning
 *
 * Revision 1.5  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.4  2003/08/21 23:09:04  southa
 * Fixed file headers
 *
 * Revision 1.3  2003/01/18 13:33:57  southa
 * Created MushcoreSingleton
 *
 * Revision 1.2  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:05  southa
 * Created Mushcore
 *
 * Revision 1.7  2002/12/20 13:17:31  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/10/22 20:41:57  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/27 08:56:15  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:44  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:14  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:02  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/31 15:18:15  southa
 * Keyboard reading
 *
 */

#include "MushcoreStandard.h"

class MushcoreAppSignal
{
public:
    enum MushcoreAppSigNumber
    {
        kMinMushcoreAppSignal=0,
        kInvalid,
        kNone,
        kQuit,
        kEscape,
        kMaxMushcoreAppSignal
    };
    
    MushcoreAppSignal(Mushware::U32 inSigNumber): m_sigNumber(inSigNumber) {} // for clients
    virtual ~MushcoreAppSignal();
    
    Mushware::U32 SigNumberGet(void) const { return m_sigNumber; }
    void SigNumberSet(Mushware::U32 inSigNumber) { m_sigNumber=inSigNumber; }
    bool IsMushcoreAppSignal(void) const;

private:
    Mushware::U32 m_sigNumber;
};

inline bool
MushcoreAppSignal::IsMushcoreAppSignal(void) const
{
    return m_sigNumber > kMinMushcoreAppSignal && m_sigNumber < kMaxMushcoreAppSignal;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
