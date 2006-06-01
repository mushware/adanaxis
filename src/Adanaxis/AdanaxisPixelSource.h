//%includeGuardStart {
#ifndef ADANAXISPIXELSOURCE_H
#define ADANAXISPIXELSOURCE_H
//%includeGuardStart } 3ML7eBVH+ZAtt4j+jyKjrg
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPixelSource.h
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } R3ZEbgO66q0YJMS9WGK1zg
/*
 * $Id: AdanaxisPixelSource.h,v 1.5 2005/08/28 22:41:51 southa Exp $
 * $Log: AdanaxisPixelSource.h,v $
 * Revision 1.5  2005/08/28 22:41:51  southa
 * MushGLTexture work
 *
 * Revision 1.4  2005/07/02 00:42:36  southa
 * Conditioning tweaks
 *
 * Revision 1.3  2005/06/20 14:30:33  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/14 13:25:33  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/13 17:34:55  southa
 * Adanaxis creation
 *
 */

#include "AdanaxisStandard.h"

#include "mushMushGL.h"

//:xml1base MushGLPixelSource
//:generate standard ostream xml1
class AdanaxisPixelSource : public MushGLPixelSource
{
public:
    enum
    {
        kParamSpare = kParamBaseNext
    };
    virtual ~AdanaxisPixelSource() {}
    virtual void ValueParameterSet(const Mushware::U32 inNum, const Mushware::tLongVal inVal);
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
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 03HVpbGkUkG1vQNs27aIZA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisPixelSource& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } PdXqK+G2pgcvW3NSwQJ3VA

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
