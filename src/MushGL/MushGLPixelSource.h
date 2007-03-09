//%includeGuardStart {
#ifndef MUSHGLPIXELSOURCE_H
#define MUSHGLPIXELSOURCE_H
//%includeGuardStart } kwijVJ9oL6wy/PlBOEfl6w
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLPixelSource.h
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
//%Header } kSpZJaClZ1AGAVBRXcCLKg
/*
 * $Id: MushGLPixelSource.h,v 1.11 2006/11/09 23:53:59 southa Exp $
 * $Log: MushGLPixelSource.h,v $
 * Revision 1.11  2006/11/09 23:53:59  southa
 * Explosion and texture loading
 *
 * Revision 1.10  2006/06/27 11:58:09  southa
 * Warning fixes
 *
 * Revision 1.9  2006/06/22 19:07:31  southa
 * Build fixes
 *
 * Revision 1.8  2006/06/07 12:15:19  southa
 * Grid and test textures
 *
 * Revision 1.7  2006/06/06 17:58:32  southa
 * Ruby texture definition
 *
 * Revision 1.6  2006/06/02 18:14:35  southa
 * Texture caching
 *
 * Revision 1.5  2006/05/02 17:32:13  southa
 * Texturing
 *
 * Revision 1.4  2006/04/11 23:30:08  southa
 * Created MushRuby from ruby-1.8.4
 *
 * Revision 1.3  2005/08/28 22:41:52  southa
 * MushGLTexture work
 *
 * Revision 1.2  2005/05/19 13:02:09  southa
 * Mac release work
 *
 * Revision 1.1  2005/02/13 22:44:07  southa
 * Tesseract stuff
 *
 */

#include "MushGLStandard.h"

#include "API/mushMushRuby.h"

class MushGLTexture;

//:generate virtual standard ostream xml1
class MushGLPixelSource : public MushcoreVirtualObject
{
public:    
    MushGLPixelSource();
    virtual ~MushGLPixelSource() {}
	virtual void ParamDecode(const MushRubyValue& inName, const MushRubyValue& inValue);
	virtual void ParamHashDecode(const Mushware::tRubyHash& inHash);
    virtual void BufferFill(Mushware::U32 * const outPtr, const Mushware::t2U32 inSize) const; // Deprecated
    virtual void ToTextureCreate(MushGLTexture& outTexture);
	
	static void Install(void);
	
private:
	std::string m_name; //:readwrite
    std::string m_storageType; //:read
	Mushware::t4U32 m_size; //:readwrite
	bool m_cacheable; //:readwrite
	bool m_compress; //:readwrite
	bool m_resident; //:readwrite
	
//%classPrototypes {
public:
    const std::string& Name(void) const { return m_name; }
    void NameSet(const std::string& inValue) { m_name=inValue; }
    const std::string& StorageType(void) const { return m_storageType; }
    const Mushware::t4U32& Size(void) const { return m_size; }
    void SizeSet(const Mushware::t4U32& inValue) { m_size=inValue; }
    const bool& Cacheable(void) const { return m_cacheable; }
    void CacheableSet(const bool& inValue) { m_cacheable=inValue; }
    const bool& Compress(void) const { return m_compress; }
    void CompressSet(const bool& inValue) { m_compress=inValue; }
    const bool& Resident(void) const { return m_resident; }
    void ResidentSet(const bool& inValue) { m_resident=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } kPw9jUVIzD6bHVkbKZuE/g
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
