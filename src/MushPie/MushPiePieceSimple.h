//%includeGuardStart {
#ifndef MUSHPIEPIECESIMPLE_H
#define MUSHPIEPIECESIMPLE_H
//%includeGuardStart } UQRURsq8rb9WaUKq14D6MA
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePieceSimple.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } vgNHjnCCayhlm093vD2VmA
/*
 * $Id: MushPiePieceSimple.h,v 1.5 2005/02/03 21:03:05 southa Exp $
 * $Log: MushPiePieceSimple.h,v $
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
    virtual const char *AutoNameGet(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } TWcI/rkUL/e8qTwqXdVZOA
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