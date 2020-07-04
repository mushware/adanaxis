//%includeGuardStart {
#ifndef MUSHGAMEJOBPLAYERCREATE_H
#define MUSHGAMEJOBPLAYERCREATE_H
//%includeGuardStart } 2CW9LTUtOg5wbcBm71geHQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameJobPlayerCreate.h
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
//%Header } 7G+//dGlHBsE6RqlY65dHg
/*
 * $Id: MushGameJobPlayerCreate.h,v 1.7 2006/06/01 15:39:22 southa Exp $
 * $Log: MushGameJobPlayerCreate.h,v $
 * Revision 1.7  2006/06/01 15:39:22  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.5  2005/06/23 17:25:25  southa
 * MushGame link work
 *
 * Revision 1.4  2005/06/23 13:56:58  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/22 20:01:58  southa
 * MushGame link work
 *
 * Revision 1.2  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.1  2005/06/21 13:10:51  southa
 * MushGame work
 *
 */

#include "MushGameStandard.h"

#include "MushGameJob.h"

#include "MushGameMessageWake.h"
#include "MushGameMessageJoinConfirm.h"
#include "MushGameMessageJoinDenied.h"

//:xml1base MushGameJob
//:generate standard ostream xml1
class MushGameJobPlayerCreate : public MushGameJob
{
public:
    explicit MushGameJobPlayerCreate(const std::string& inID = "");
    virtual ~MushGameJobPlayerCreate() {}

    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);
    virtual void WakeConsume(MushGameLogic& ioLogic, const MushGameMessageWake& inMessage);
    virtual void JoinConfirmConsume(MushGameLogic& ioLogic, const MushGameMessageJoinConfirm& inMessage);
    virtual void JoinDeniedConsume(MushGameLogic& ioLogic, const MushGameMessageJoinDenied& inMessage);
    
private:
    enum
    {
        kStateInit = 2,
        kStateWait,
        kRetryMsec = 1000
    };

    Mushware::U32 m_state;
    
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
operator<<(std::ostream& ioOut, const MushGameJobPlayerCreate& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } jzJ6KzXHdMtYjy12LO7zIA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw

