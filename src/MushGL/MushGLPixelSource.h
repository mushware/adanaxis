//%includeGuardStart {
#ifndef MUSHGLPIXELSOURCE_H
#define MUSHGLPIXELSOURCE_H
//%includeGuardStart } kwijVJ9oL6wy/PlBOEfl6w
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLPixelSource.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } TheOEjkgG2vHwfZ4wpw87Q
/*
 * $Id$
 * $Log$
 */

#include "MushGLStandard.h"

//:generate virtual ostream xml1
class MushGLPixelSource : public MushcoreVirtualObject
{
public:
    enum
    {
        kParamInvalid,
        kParamNone,
        kParamFrameTime,
        kParamRed,
        kParamGreen,
        kParamBlue,
        kParamAlpha,
        kParamSeed,
        kParamBaseNext
    };
    virtual ~MushGLPixelSource() {}
    virtual void ParameterSet(const Mushware::U32 inNum, const Mushware::tLongVal inVal) = 0;
    virtual void BufferFill(Mushware::U32 * const outPtr, const Mushware::t2U32 inSize) const = 0;
    
private:
//%classPrototypes {
public:
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } ZNroX5cBIW8CbBVukLOWpQ
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLPixelSource& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Hkku+u2zp3t0yLCsH+78Gw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
