//%includeGuardStart {
#ifndef MUSHGLTEXTURE_H
#define MUSHGLTEXTURE_H
//%includeGuardStart } 2OOZzxKbPULo3XX0MW1IxQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLTexture.h
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
//%Header } M3l27y1AKgnUC/y7boOgRQ
/*
 * $Id: MushGLTexture.h,v 1.13 2007/02/08 17:55:14 southa Exp $
 * $Log: MushGLTexture.h,v $
 * Revision 1.13  2007/02/08 17:55:14  southa
 * Common routines in space generation
 *
 * Revision 1.12  2006/11/09 23:53:59  southa
 * Explosion and texture loading
 *
 * Revision 1.11  2006/11/07 11:08:54  southa
 * Texture loading from mushfiles
 *
 * Revision 1.10  2006/07/02 21:08:55  southa
 * Ruby menu work
 *
 * Revision 1.9  2006/06/30 15:05:33  southa
 * Texture and buffer purge
 *
 * Revision 1.8  2006/06/07 12:15:19  southa
 * Grid and test textures
 *
 * Revision 1.7  2006/06/06 17:58:32  southa
 * Ruby texture definition
 *
 * Revision 1.6  2006/06/05 16:54:44  southa
 * Ruby textures
 *
 * Revision 1.5  2006/06/02 18:14:36  southa
 * Texture caching
 *
 * Revision 1.4  2006/05/02 17:32:13  southa
 * Texturing
 *
 * Revision 1.3  2005/09/05 12:54:30  southa
 * Solid rendering work
 *
 * Revision 1.2  2005/08/29 18:40:57  southa
 * Solid rendering work
 *
 * Revision 1.1  2005/08/28 22:41:52  southa
 * MushGLTexture work
 *
 */

#include "MushGLStandard.h"

#include "mushMushRuby.h"

//:generate virtual standard ostream xml1 nocopy
class MushGLTexture : public MushcoreVirtualObject
{
public:
    typedef MushcoreDataRef<MushGLTexture> tDataRef;
    
    MushGLTexture() :
        m_size(Mushware::t4U32(0,0,0,1)),
        m_bound(false),
        m_bindingNameValid(false),
        m_pixelType(kPixelTypeNone),
        m_storageType(kStorageTypeNone),
		m_cacheable(true),
		m_cacheSaveRequired(false),
		m_compress(false),
        m_made(false),
        m_saveable(true),
        m_resident(false)
    {}

    void Make(void);
    void Bind(void);
    void Purge(void);
    
    void PixelTypeRGBASet(void) { m_pixelType = kPixelTypeRGBA; }
    void StorageTypeGLSet(void) { m_storageType = kStorageTypeGL; }
    void StorageTypeSet(const std::string& inType);
    
    void PixelDataUse(void *pData);
    Mushware::t4Val U8RGBALookup(Mushware::t2Val inPos) const;
    
    static Mushware::tSize ByteCount(void) { return m_byteCount; }
    static void ByteCountSet(Mushware::tSize inCount) { m_byteCount = inCount; }
    
    static MushcoreScalar Texture(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    static void RubyInstall(void);

	static Mushware::tRubyValue RubyDefine(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue RubyPrecache(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf);
		
private:
    enum 
    {
        kTypeInvalid,
        kPixelTypeNone,
        kPixelTypeRGBA,
        kPixelTypeFloat,
        kStorageTypeNone,
        kStorageTypeU8Data,
        kStorageTypeValData,
        kStorageTypeGL
    };

    void PixelDataGLRGBAUse(void *pData);
    void PixelDataU8RGBAUse(void *pData);
    void ToCacheSave(void);
	bool FromCacheLoad(void);
	
    std::vector<Mushware::U8> m_u8Data;
    std::vector<Mushware::tVal> m_valData;
    Mushware::t4U32 m_size; //:readwrite
    bool m_bound;
    bool m_bindingNameValid;
    GLuint m_bindingName;
    Mushware::U32 m_pixelType;
    Mushware::U32 m_storageType;
    std::string m_uniqueIdentifier; //:readwrite
	std::string m_name; //:readwrite
    std::string m_cacheFilename;
	bool m_cacheable; //:readwrite
	bool m_cacheSaveRequired;
	bool m_compress; //:readwrite
    bool m_made;
    bool m_saveable; //:readwrite
    bool m_resident; //:readwrite
    
    static Mushware::tSize m_byteCount;
    
//%classPrototypes {
public:
    const Mushware::t4U32& Size(void) const { return m_size; }
    void SizeSet(const Mushware::t4U32& inValue) { m_size=inValue; }
    const std::string& UniqueIdentifier(void) const { return m_uniqueIdentifier; }
    void UniqueIdentifierSet(const std::string& inValue) { m_uniqueIdentifier=inValue; }
    const std::string& Name(void) const { return m_name; }
    void NameSet(const std::string& inValue) { m_name=inValue; }
    const bool& Cacheable(void) const { return m_cacheable; }
    void CacheableSet(const bool& inValue) { m_cacheable=inValue; }
    const bool& Compress(void) const { return m_compress; }
    void CompressSet(const bool& inValue) { m_compress=inValue; }
    const bool& Saveable(void) const { return m_saveable; }
    void SaveableSet(const bool& inValue) { m_saveable=inValue; }
    const bool& Resident(void) const { return m_resident; }
    void ResidentSet(const bool& inValue) { m_resident=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } qO/uHtdHXFb5ixOoQT+26g
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLTexture& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } +ORFC1dr5UCCSVx9I4MYaQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
