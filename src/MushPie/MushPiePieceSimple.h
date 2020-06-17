//%includeGuardStart {
#ifndef MUSHPIEPIECESIMPLE_H
#define MUSHPIEPIECESIMPLE_H
//%includeGuardStart } UQRURsq8rb9WaUKq14D6MA
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePieceSimple.h
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
//%Header } MXnGb8/unSazy/izmfOKKA
/*
 * $Id: MushPiePieceSimple.h,v 1.9 2006/06/01 15:39:37 southa Exp $
 * $Log: MushPiePieceSimple.h,v $
 * Revision 1.9  2006/06/01 15:39:37  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.7  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.6  2005/02/10 12:34:14  southa
 * Template fixes
 *
 * Revision 1.5  2005/02/03 21:03:05  southa
 * Build fixes
 *
 * Revision 1.4  2004/09/27 22:42:10  southa
 * MSVC compilation fixes
 *
 * Revision 1.3  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 * Revision 1.2  2004/01/04 14:36:37  southa
 * Handle 'inline' in source conditioner
 *
 * Revision 1.1  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 */

#include "MushPieStandard.h"

#include "MushPiePiece.h"
#include "MushPiePosition.h"

//:xml1base MushPiePiece
//:generate virtual ostream xml1 standard
class MushPiePieceSimple : public MushPiePiece
{
public:
    MushPiePieceSimple() {}
    virtual ~MushPiePieceSimple() {}

private:
    MushPiePosition m_pos; //:readwrite
//%classPrototypes {
public:
    const MushPiePosition& Pos(void) const { return m_pos; }
    void PosSet(const MushPiePosition& inValue) { m_pos=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } s6US1P5CAkyS/r3hL8UhGg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushPiePieceSimple& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } T9GT/MzgcTsiiKLuRmDhGg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
