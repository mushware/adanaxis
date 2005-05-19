//%includeGuardStart {
#ifndef TESSERACTTRAINERPIXELSOURCE_H
#define TESSERACTTRAINERPIXELSOURCE_H
//%includeGuardStart } gElDVBoRlQ6Sx9Ax7eEBTA
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerPixelSource.h
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
//%Header } 6wrxduT8qjqQA8gwnwHt8A
/*
 * $Id: TesseractTrainerPixelSource.h,v 1.1 2005/02/13 22:44:08 southa Exp $
 * $Log: TesseractTrainerPixelSource.h,v $
 * Revision 1.1  2005/02/13 22:44:08  southa
 * Tesseract stuff
 *
 */

#include "TesseractTrainerStandard.h"

#include "mushMushGL.h"

//:xml1base MushGLPixelSource
//:generate standard ostream xml1
class TesseractTrainerPixelSource : public MushGLPixelSource
{
public:
    enum
    {
        kParamSpare = kParamBaseNext
    };
    virtual ~TesseractTrainerPixelSource() {}
    virtual void ParameterSet(const Mushware::U32 inNum, const Mushware::tLongVal inVal);
    virtual void BufferFill(Mushware::U32 * const outPtr, const Mushware::t2U32 inSize) const;

private:
    Mushware::tLongVal m_frameTime; //:readwrite
    Mushware::t4Val m_colour; //:readwrite
    Mushware::tLongVal m_seed; //:readwrite
        
//%classPrototypes {
public:
    const Mushware::tLongVal& FrameTime(void) const { return m_frameTime; }
    void FrameTimeSet(const Mushware::tLongVal& inValue) { m_frameTime=inValue; }
    const Mushware::t4Val& Colour(void) const { return m_colour; }
    void ColourSet(const Mushware::t4Val& inValue) { m_colour=inValue; }
    const Mushware::tLongVal& Seed(void) const { return m_seed; }
    void SeedSet(const Mushware::tLongVal& inValue) { m_seed=inValue; }
    const char *AutoNameGet(void) const;
    MushcoreVirtualObject *AutoClone(void) const;
    MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    void AutoPrint(std::ostream& ioOut) const;
    bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } IHyD2VNyJWz0tfZ0EcsB7g
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const TesseractTrainerPixelSource& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Joj79H2bzCnOZ5wf0KNnLw

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
