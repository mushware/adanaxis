//%includeGuardStart {
#ifndef MUSHGAMEANIMPOSTMANIP_H
#define MUSHGAMEANIMPOSTMANIP_H
//%includeGuardStart } kKBUf99bhDV6sUzDfKprzw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameAnimPostManip.h
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
//%Header } JsgntM9bfxzo/CwdYlNAQA
/*
 * $Id: MushGameAnimPostManip.h,v 1.3 2006/06/01 15:39:20 southa Exp $
 * $Log: MushGameAnimPostManip.h,v $
 * Revision 1.3  2006/06/01 15:39:20  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/05 16:35:53  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 */

#include "MushGameStandard.h"

//:generate standard ostream xml1
class MushGameAnimPostManip : public MushcoreVirtualObject
{
public:
    MushGameAnimPostManip();
    virtual ~MushGameAnimPostManip() {}
    void PostAdjust(MushMeshPosticity& ioPost);

private:
    Mushware::tVal m_posSpeed; //:readwrite
    Mushware::tVal m_angSpeed; //:readwrite
    
//%classPrototypes {
public:
    const Mushware::tVal& PosSpeed(void) const { return m_posSpeed; }
    void PosSpeedSet(const Mushware::tVal& inValue) { m_posSpeed=inValue; }
    const Mushware::tVal& AngSpeed(void) const { return m_angSpeed; }
    void AngSpeedSet(const Mushware::tVal& inValue) { m_angSpeed=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } aU1OUTIp4fMMoMAB0QR5OA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameAnimPostManip& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } vjiZSxLd/otw4RLWhr3hKA

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
