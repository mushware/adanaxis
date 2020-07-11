//%includeGuardStart {
#ifndef MUSHGLCACHECONTROL_H
#define MUSHGLCACHECONTROL_H
//%includeGuardStart } n8X+UiXz7FkSLGTEDWyv6g
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLCacheControl.h
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
//%Header } g9Mppx27/QFvi1JObOjjOw
/*
 * $Id: MushGLCacheControl.h,v 1.2 2006/07/28 16:52:21 southa Exp $
 * $Log: MushGLCacheControl.h,v $
 * Revision 1.2  2006/07/28 16:52:21  southa
 * Options work
 *
 * Revision 1.1  2006/06/05 11:48:24  southa
 * Noise textures
 *
 */

#include "MushGLStandard.h"

//:generate virtual standard ostream xml1
class MushGLCacheControl : public MushcoreVirtualObject, public MushcoreSingleton<MushGLCacheControl>
{
public:
	MushGLCacheControl();
    virtual ~MushGLCacheControl() {}
	
	virtual std::string HashedFilenameMake(const std::string& inName);
	virtual std::string TextureCacheFilenameMake(const std::string& inName, const std::string& inUniqueId, Mushware::t2U32& inSize);
	virtual std::string TextureCachePlainFilenameMake(const std::string& inName);
	virtual std::string TextureCachePath(void) const;
	virtual void CachePurge(void);
    
    void TextureCacheHitRegister(void) { ++m_textureCacheHits; }
	void TextureCacheMissRegister(void) { ++m_textureCacheMisses; }
	
protected:
	enum
	{
		kFilenameHashLength = 16
	};
private:
	bool m_permitCache; //:readwrite
	bool m_permitCompression; //:readwrite
	std::string m_globalCachePath; //:read
	std::string m_hashSeed;
	Mushware::U32 m_textureCacheHits;
	Mushware::U32 m_textureCacheMisses;
//%classPrototypes {
public:
    const bool& PermitCache(void) const { return m_permitCache; }
    void PermitCacheSet(const bool& inValue) { m_permitCache=inValue; }
    const bool& PermitCompression(void) const { return m_permitCompression; }
    void PermitCompressionSet(const bool& inValue) { m_permitCompression=inValue; }
    const std::string& GlobalCachePath(void) const { return m_globalCachePath; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 6Rh/qVpdKpi7z2nFGPiaAw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLCacheControl& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 5OclbzFmBud3lC2bAtDcGw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
