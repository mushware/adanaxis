//%includeGuardStart {
#ifndef MUSHGLRESOLVERPIXELSOURCE_H
#define MUSHGLRESOLVERPIXELSOURCE_H
//%includeGuardStart } UAHgKOsJyDZf+3ceiRPZqw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLResolverPixelSource.h
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
//%Header } UWY3Pxnr/7dustUxmKjfTA
/*
 * $Id: MushGLResolverPixelSource.h,v 1.1 2005/08/28 22:41:52 southa Exp $
 * $Log: MushGLResolverPixelSource.h,v $
 * Revision 1.1  2005/08/28 22:41:52  southa
 * MushGLTexture work
 *
 */

#include "MushGLStandard.h"

//:generate virtual standard ostream xml1 nocopy
class MushGLResolverPixelSource : public MushcoreVirtualObject, public MushcoreSingleton<MushGLResolverPixelSource>
{
public:
    virtual void Resolve(const std::string& inSrcName);
    
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
operator<<(std::ostream& ioOut, const MushGLResolverPixelSource& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } BUvQ7pd8A25s1q40fuShTA

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw