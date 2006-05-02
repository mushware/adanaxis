//%includeGuardStart {
#ifndef MUSHGLTEXTURE_H
#define MUSHGLTEXTURE_H
//%includeGuardStart } 2OOZzxKbPULo3XX0MW1IxQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLTexture.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } AYQWMxoJ+uDPAQUnlwSk/w
/*
 * $Id: MushGLTexture.h,v 1.3 2005/09/05 12:54:30 southa Exp $
 * $Log: MushGLTexture.h,v $
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

//:generate virtual standard ostream xml1 nocopy
class MushGLTexture : public MushcoreVirtualObject
{
public:
    typedef MushcoreDataRef<MushGLTexture> tDataRef;
    
    MushGLTexture() :
        m_size(Mushware::t4U32(0,0,0)),
        m_bound(false),
        m_bindingNameValid(false),
        m_pixelType(kPixelTypeNone),
        m_storageType(kStorageTypeNone),
        m_made(false)
    {}

    void Make(void);
    void Bind(void);
    
    void PixelTypeRGBASet(void) { m_pixelType = kPixelTypeRGBA; }
    void StorageTypeGLSet(void) { m_storageType = kStorageTypeGL; }
    void StorageTypeSet(const std::string& inType);
    
    void PixelDataUse(void *pData);
    Mushware::t4Val U8RGBALookup(Mushware::t2Val inPos);
    
    static MushcoreScalar Texture(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);

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
    
    std::vector<Mushware::U8> m_u8Data;
    std::vector<Mushware::tVal> m_valData;
    Mushware::t4U32 m_size; //:readwrite
    bool m_bound;
    bool m_bindingNameValid;
    GLuint m_bindingName;
    Mushware::U32 m_pixelType;
    Mushware::U32 m_storageType;
    std::string m_srcName; //:readwrite
    bool m_made;
    
//%classPrototypes {
public:
    const Mushware::t4U32& Size(void) const { return m_size; }
    void SizeSet(const Mushware::t4U32& inValue) { m_size=inValue; }
    const std::string& SrcName(void) const { return m_srcName; }
    void SrcNameSet(const std::string& inValue) { m_srcName=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } dMBsMFRK5iAZwViDEknjPg
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
