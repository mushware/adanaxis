//%includeGuardStart {
#ifndef MUSHGAMEMESSAGEUPLINKPIECE_H
#define MUSHGAMEMESSAGEUPLINKPIECE_H
//%includeGuardStart } TOTGErNU987aoOImssnOHw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageUplinkPiece.h
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
//%Header } tRZp/eU1PE3HU2/piDEORw
/*
 * $Id: MushGameMessageUplinkPiece.h,v 1.2 2006/06/01 15:39:25 southa Exp $
 * $Log: MushGameMessageUplinkPiece.h,v $
 * Revision 1.2  2006/06/01 15:39:25  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/11 14:48:46  southa
 * Uplink work
 *
 */

#include "MushGameStandard.h"

#include "MushGameMessage.h"

//:xml1base MushGameMessage
//:generate standard ostream xml1
class MushGameMessageUplinkPiece : public MushGameMessage
{
public:
    explicit MushGameMessageUplinkPiece(const std::string& inID = "") : MushGameMessage(inID) {}
    virtual ~MushGameMessageUplinkPiece() {}

private:
    MushMeshPosticity m_post; //:readwrite :wref
    
//%classPrototypes {
public:
    const MushMeshPosticity& Post(void) const { return m_post; }
    void PostSet(const MushMeshPosticity& inValue) { m_post=inValue; }
    // Writable reference for m_post
    MushMeshPosticity& PostWRef(void) { return m_post; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } xgYH1Kh+PR9uvdS4XNL1+w
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameMessageUplinkPiece& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } TSLzgxNvUjvIdIMdjN/n+Q
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
