//%includeGuardStart {
#ifndef MUSHGLRESOLVERPIXELSOURCE_H
#define MUSHGLRESOLVERPIXELSOURCE_H
//%includeGuardStart } UAHgKOsJyDZf+3ceiRPZqw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLResolverPixelSource.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } fYp+Qf/9lTdz/7m/1OiiFQ
/*
 * $Id: MushGLResolverPixelSource.h,v 1.6 2006/06/07 12:15:19 southa Exp $
 * $Log: MushGLResolverPixelSource.h,v $
 * Revision 1.6  2006/06/07 12:15:19  southa
 * Grid and test textures
 *
 * Revision 1.5  2006/06/06 17:58:32  southa
 * Ruby texture definition
 *
 * Revision 1.4  2006/06/06 10:29:51  southa
 * Ruby texture definitions
 *
 * Revision 1.3  2006/06/01 15:39:18  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2006/04/11 23:30:08  southa
 * Created MushRuby from ruby-1.8.4
 *
 * Revision 1.1  2005/08/28 22:41:52  southa
 * MushGLTexture work
 *
 */

#include "MushGLStandard.h"

#include "mushMushRuby.h"

class MushGLPixelSource;

//:generate virtual standard ostream xml1 nocopy
class MushGLResolverPixelSource : public MushcoreVirtualObject, public MushcoreSingleton<MushGLResolverPixelSource>
{
public:
	MushGLResolverPixelSource();
	explicit MushGLResolverPixelSource(const MushGLResolverPixelSource *inpPixelSource);
   	virtual MushGLPixelSource& ParamHashResolve(const Mushware::tRubyHash& inHash);
	virtual void PrefixAdd(const std::string& inStr) { m_sourcePrefixes.push_front(inStr); }

private:
	typedef std::list<std::string> tSourcePrefixes;
	tSourcePrefixes m_sourcePrefixes; //:read

//%classPrototypes {
public:
    const tSourcePrefixes& SourcePrefixes(void) const { return m_sourcePrefixes; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } RHRo0QzPzZ0v0cARvEM4vw
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
