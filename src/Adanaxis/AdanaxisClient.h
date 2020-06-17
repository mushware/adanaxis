//%includeGuardStart {
#ifndef ADANAXISCLIENT_H
#define ADANAXISCLIENT_H
//%includeGuardStart } 2sNIivWtxKZWCIEsJT7nEg
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisClient.h
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
//%Header } /e8aVlWeL+PFw03aeRLI9w
/*
 * $Id: AdanaxisClient.h,v 1.5 2007/04/18 09:21:59 southa Exp $
 * $Log: AdanaxisClient.h,v $
 * Revision 1.5  2007/04/18 09:21:59  southa
 * Header and level fixes
 *
 * Revision 1.4  2006/08/01 17:21:22  southa
 * River demo
 *
 * Revision 1.3  2006/06/01 15:38:46  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/06/20 14:30:33  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 10:49:57  southa
 * Client/server work
 *
 */

#include "AdanaxisStandard.h"

#include "API/mushMushGame.h"

//:xml1base MushGameClient
//:generate virtual standard ostream xml1
class AdanaxisClient : public MushGameClient
{
public:
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
operator<<(std::ostream& ioOut, const AdanaxisClient& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 88Tgs2k3k5hwpJuZ9Yc6rQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
