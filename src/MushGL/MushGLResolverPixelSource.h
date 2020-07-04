//%includeGuardStart {
#ifndef MUSHGLRESOLVERPIXELSOURCE_H
#define MUSHGLRESOLVERPIXELSOURCE_H
//%includeGuardStart } UAHgKOsJyDZf+3ceiRPZqw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLResolverPixelSource.h
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
//%Header } 7tsceuhTFcT862bXeLdVTg
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
