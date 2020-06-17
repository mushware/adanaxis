//%includeGuardStart {
#ifndef MUSHGAMELINKLOCAL_H
#define MUSHGAMELINKLOCAL_H
//%includeGuardStart } 0/YY5aWWhNBrwLukR235Qw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameLinkLocal.h
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
//%Header } QTsXNdQ7I76XfCymmDqn1w
/*
 * $Id: MushGameLinkLocal.h,v 1.5 2006/06/01 15:39:23 southa Exp $
 * $Log: MushGameLinkLocal.h,v $
 * Revision 1.5  2006/06/01 15:39:23  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/06/23 11:58:28  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/22 20:01:59  southa
 * MushGame link work
 *
 * Revision 1.2  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.1  2005/06/20 16:14:31  southa
 * Adanaxis work
 *
 */

#include "MushGameStandard.h"

#include "MushGameClient.h"
#include "MushGameMailbox.h"
#include "MushGameLink.h"
#include "MushGameServer.h"

class MushGameLogic;

//:xml1base MushGameLink
//:generate virtual standard ostream xml1
class MushGameLinkLocal : public MushGameLink
{
public:
    typedef MushcoreData< MushcorePipe<MushGameMailbox> > tPipeData;
    typedef MushcoreDataRef< MushcorePipe<MushGameMailbox> > tPipeDataRef;
   
    MushGameLinkLocal();
    virtual ~MushGameLinkLocal() {}
    virtual void SrcDestSet(const std::string& inSrcName, const std::string& inDestName);

    virtual bool OutboxSendUnlessEmpty(void);
    virtual bool InboxGetUnlessEmpty(MushGameMailbox& outMailbox);
    virtual void ToOutboxCopy(const MushGameMessage& inMessage);
    
protected:
    // Pipe database for connecting links
    static tPipeData m_pipeData;
    
private:
    MushGameMailbox m_outBox; //:ignore
    MushGameMailbox m_inBox; //:ignore

    tPipeDataRef m_uplinkRef; //:ignore
    tPipeDataRef m_downlinkRef; //:ignore
    
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
operator<<(std::ostream& ioOut, const MushGameLinkLocal& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } GJAmucyBlwTyaWsSpOPcGw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
