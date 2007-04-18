//%includeGuardStart {
#ifndef MUSHGLCACHECONTROL_H
#define MUSHGLCACHECONTROL_H
//%includeGuardStart } n8X+UiXz7FkSLGTEDWyv6g
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLCacheControl.h
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
//%Header } Jni0kebaqtFUXU09GjTL9w
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
	virtual std::string TextureCacheFilenameMake(const std::string& inName);
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
