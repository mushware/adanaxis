//%includeGuardStart {
#ifndef MUSHGLPIXELSOURCE_H
#define MUSHGLPIXELSOURCE_H
//%includeGuardStart } kwijVJ9oL6wy/PlBOEfl6w
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLPixelSource.h
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 929uH06nvmR9AZQiCgrrTw
/*
 * $Id: MushGLPixelSource.h,v 1.1 2005/02/13 22:44:07 southa Exp $
 * $Log: MushGLPixelSource.h,v $
 * Revision 1.1  2005/02/13 22:44:07  southa
 * Tesseract stuff
 *
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
