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
 * $Id$
 * $Log$
 */

#include "MushPieStandard.h"

#include "MushPiePiece.h"

//:xml1base MushPiePiece
//:generate standard ostream xml1
class MushPiePieceSimple : public MushPiePiece
{
public:
    MushPiePieceSimple() {}
    virtual ~MushPiePieceSimple() {}

private:
    Mushware::t3Val m_angle; //:readwrite
    Mushware::t3Val m_angularVel; //:readwrite
//%classPrototypes {
public:
    const Mushware::t3Val& AngleGet(void) const { return m_angle; }
    void AngleSet(const Mushware::t3Val& inValue) { m_angle=inValue; }
    const Mushware::t3Val& AngularVelGet(void) const { return m_angularVel; }
    void AngularVelSet(const Mushware::t3Val& inValue) { m_angularVel=inValue; }
    virtual const char *AutoNameGet(void) const;
    virtual MushPiePieceSimple *AutoClone(void) const;
    virtual MushPiePieceSimple *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    void AutoPrint(std::ostream& ioOut) const;
    bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } sn0sSjUmvIl//lU0eSJD7g
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
