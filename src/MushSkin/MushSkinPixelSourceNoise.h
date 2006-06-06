//%includeGuardStart {
#ifndef MUSHSKINPIXELSOURCENOISE_H
#define MUSHSKINPIXELSOURCENOISE_H
//%includeGuardStart } zzDX6Lm0vtHywsZ1Q8TL3w
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceNoise.h
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
//%Header } p+qloydajE1rCLfMhFW9wg
/*
 * $Id: MushSkinPixelSourceNoise.h,v 1.5 2006/06/05 11:48:26 southa Exp $
 * $Log: MushSkinPixelSourceNoise.h,v $
 * Revision 1.5  2006/06/05 11:48:26  southa
 * Noise textures
 *
 * Revision 1.4  2006/06/02 18:14:36  southa
 * Texture caching
 *
 * Revision 1.3  2006/05/02 17:32:13  southa
 * Texturing
 *
 * Revision 1.2  2006/04/11 23:30:11  southa
 * Created MushRuby from ruby-1.8.4
 *
 * Revision 1.1  2005/09/06 12:15:35  southa
 * Texture and rendering work
 *
 */

#include "MushSkinStandard.h"

//:generate virtual standard ostream xml1
class MushSkinPixelSourceNoise : public MushGLPixelSource
{
public:
    MushSkinPixelSourceNoise() :
        m_pPaletteTexture(NULL)
    {}
    
    virtual void ValueParameterSet(const Mushware::U32 inNum, const Mushware::tLongVal inVal);
    virtual void StringParameterSet(const Mushware::U32 inNum, const std::string& inStr);
    virtual void ToTextureCreate(MushGLTexture& outTexture);
    virtual void ParamDecode(const MushRubyValue& inName, const MushRubyValue& inValue);

protected:
    virtual void TileLineGenerate(Mushware::U8 *inpTileData, const MushMesh4Mesh::tTextureTile& inTileRef,
                                  Mushware::U32 inNumPixels, Mushware::t4Val inStartPos, Mushware::t4Val inEndPos);

    Mushware::t2Val m_paletteStart;    
    Mushware::t2Val m_paletteVector1;
    Mushware::t2Val m_paletteVector2;
    MushGLTexture *m_pPaletteTexture; // Not owned by this object
    
private:
    std::string m_meshName; //:read
    std::string m_paletteName; //:read
    
//%classPrototypes {
public:
    const std::string& SourceName(void) const { return m_meshName; }
    const std::string& PaletteName(void) const { return m_paletteName; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } hNp9sR/1oLVBPc7uQnaDNw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushSkinPixelSourceNoise& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } hrW5HfwUJFyV2mDS0sS9Jw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
