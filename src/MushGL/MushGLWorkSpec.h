//%includeGuardStart {
#ifndef MUSHGLWORKSPEC_H
#define MUSHGLWORKSPEC_H
//%includeGuardStart } 4IYGzsr2PcjyQ9a0eYSvXA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLWorkSpec.h
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
//%Header } BZyu/wg46trB+Iw52bW3GQ
/*
 * $Id: MushGLWorkSpec.h,v 1.7 2006/09/09 11:16:41 southa Exp $
 * $Log: MushGLWorkSpec.h,v $
 * Revision 1.7  2006/09/09 11:16:41  southa
 * One-time vertex buffer generation
 *
 * Revision 1.6  2006/06/20 19:06:52  southa
 * Object creation
 *
 * Revision 1.5  2006/06/19 15:57:17  southa
 * Materials
 *
 * Revision 1.4  2006/06/01 15:39:19  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/09/05 17:14:23  southa
 * Solid rendering
 *
 * Revision 1.2  2005/08/31 23:57:27  southa
 * Texture coordinate work
 *
 * Revision 1.1  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 */

#include "MushGLStandard.h"

#include "MushGLBuffers.h"
#include "MushGLTexture.h"

//:generate virtual standard ostream xml1
class MushGLWorkSpec : public MushcoreVirtualObject
{
public:
    enum
    {
        kRenderTypeLines = GL_LINES,
        kRenderTypeTriangles = GL_TRIANGLES,
    };
    
    MushGLWorkSpec() : m_renderType(0), m_useSharedVertices(true) {}
    virtual ~MushGLWorkSpec() {}

    void Execute(MushGLBuffers::tDataRef& ioDataRef, MushGLBuffers::tSharedDataRef& ioSharedDataRef);
    void TextureSet(MushGLTexture *inpTexture, Mushware::U32 inNum);
    MushGLTexture& Texture(Mushware::U32 inNum);
	Mushware::U32 NumTextures(void) const { return m_textures.size(); }
	bool IsValidTexture(Mushware::U32 inNum) const;
	
private:
    Mushware::U32 m_renderType; //:readwrite
	std::vector<MushGLTexture *> m_textures; // Object doesn't own these
    bool m_useSharedVertices; //:readwrite
    
//%classPrototypes {
public:
    const Mushware::U32& RenderType(void) const { return m_renderType; }
    void RenderTypeSet(const Mushware::U32& inValue) { m_renderType=inValue; }
    const bool& UseSharedVertices(void) const { return m_useSharedVertices; }
    void UseSharedVerticesSet(const bool& inValue) { m_useSharedVertices=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } xCDOaHzKXigndok/y9lFoA
};

inline void
MushGLWorkSpec::TextureSet(MushGLTexture *inpTexture, Mushware::U32 inNum)
{
	if (inNum >= m_textures.size())
	{
		m_textures.resize(inNum+1, NULL);
	}
	m_textures[inNum] = inpTexture;
}

inline MushGLTexture&
MushGLWorkSpec::Texture(Mushware::U32 inNum)
{
	MushcoreUtil::DebugBoundsCheck(inNum, m_textures.size());
	if (m_textures[inNum] == NULL)
	{
		throw MushcoreRequestFail("Access to non-existent texture");	
	}
	return *m_textures[inNum];
}

inline bool
MushGLWorkSpec::IsValidTexture(Mushware::U32 inNum) const
{
	return inNum < NumTextures() && m_textures[inNum] != NULL;	
}

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLWorkSpec& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Pml5Trl+jExBeyd0Uu8qJg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
