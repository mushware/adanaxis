//%includeGuardStart {
#ifndef MUSHSKINRESOLVERPIXELSOURCE_H
#define MUSHSKINRESOLVERPIXELSOURCE_H
//%includeGuardStart } tv2DLLCkkHUWcypzYDGXNQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinResolverPixelSource.h
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
//%Header } v3MrgrO4JsvAn3uDUG6X7g
/*
 * $Id: MushSkinResolverPixelSource.h,v 1.1 2006/04/11 23:30:11 southa Exp $
 * $Log: MushSkinResolverPixelSource.h,v $
 * Revision 1.1  2006/04/11 23:30:11  southa
 * Created MushRuby from ruby-1.8.4
 *
 */

#include "MushSkinStandard.h"

//:generate virtual standard ostream xml1 nocopy
class MushSkinResolverPixelSource : public MushGLResolverPixelSource
{
public:
    virtual void Resolve(const std::string& inSrcName);
    
private:
    
    
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
operator<<(std::ostream& ioOut, const MushSkinResolverPixelSource& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } TUFnZyEz8EQYO/tzUv6vZg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
