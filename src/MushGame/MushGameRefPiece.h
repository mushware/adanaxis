//%includeGuardStart {
#ifndef MUSHGAMEREFPIECE_H
#define MUSHGAMEREFPIECE_H
//%includeGuardStart } J/WPmrB/9n93A5qDrulo0A
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameRefPiece.h
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
//%Header } 3A7zkgb2c9EfNqBkm5mwGQ
/*
 * $Id: MushGameRefPiece.h,v 1.2 2006/06/01 15:39:26 southa Exp $
 * $Log: MushGameRefPiece.h,v $
 * Revision 1.2  2006/06/01 15:39:26  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/06/29 09:07:56  southa
 * MushGame camera work
 *
 */

#include "MushGameStandard.h"

#include "MushGameRef.h"

#include "MushGamePiece.h"

//:xml1base MushGameRef
//:generate virtual standard ostream xml1
class MushGameRefPiece : public MushGameRef
{
public:
    virtual MushcoreVirtualObject& Ref() { return m_pieceRef.WRef(); }
    
private:
    MushcoreDataRef<MushGamePiece> m_pieceRef;
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
operator<<(std::ostream& ioOut, const MushGameRefPiece& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } LkPDcQ2KSOo0IqKGljtqtA

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
