//%includeGuardStart {
#ifndef MUSHGAMELOGICLOCAL_H
#define MUSHGAMELOGICLOCAL_H
//%includeGuardStart } gX86MOXtLh2LiVRaAbr5dQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameLogicLocal.h
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
//%Header } 8Ehx+F2U4N7OAVLDbUH3nw
/*
 * $Id: MushGameLogicLocal.h,v 1.5 2006/06/01 15:39:23 southa Exp $
 * $Log: MushGameLogicLocal.h,v $
 * Revision 1.5  2006/06/01 15:39:23  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/06/23 17:25:25  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/22 20:01:59  southa
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

#include "MushGameLogic.h"

//:xml1base MushGameLogic
//:generate virtual standard ostream xml1
class MushGameLogicLocal : public MushGameLogic
{
public:
    MushGameLogicLocal();
    virtual ~MushGameLogicLocal() {}
    
    virtual void SinglePlayerCheck(void);
    virtual void PerFrameProcessing(void);
    virtual void JobMessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);

protected:    
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
operator<<(std::ostream& ioOut, const MushGameLogicLocal& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } LEOGPdjIWn5fvNU2FWiMZg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
