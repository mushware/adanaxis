//%includeGuardStart {
#ifndef MUSHGLPIXELSOURCETIFF_H
#define MUSHGLPIXELSOURCETIFF_H
//%includeGuardStart } nH7Z6maSsLIzcTPVyFNcrQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLPixelSourceTIFF.h
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
//%Header } 4pAg/vOq6vFDmvSeLah2fg
/*
 * $Id: MushGLPixelSourceTIFF.h,v 1.5 2006/06/07 12:15:19 southa Exp $
 * $Log: MushGLPixelSourceTIFF.h,v $
 * Revision 1.5  2006/06/07 12:15:19  southa
 * Grid and test textures
 *
 * Revision 1.4  2006/06/06 17:58:32  southa
 * Ruby texture definition
 *
 * Revision 1.3  2006/06/01 15:39:18  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/08/29 18:40:56  southa
 * Solid rendering work
 *
 * Revision 1.1  2005/08/28 22:41:52  southa
 * MushGLTexture work
 *
 */

#include "MushGLStandard.h"

#include "MushGLPixelSource.h"

class MushGLTexture;

//:generate virtual standard ostream xml1
class MushGLPixelSourceTIFF : public MushGLPixelSource
{
public:
	MushGLPixelSourceTIFF();
    virtual void ToTextureCreate(MushGLTexture& outTexture);
	virtual void ParamDecode(const MushRubyValue& inName, const MushRubyValue& inValue);

private:
    std::string m_filename; //:readwrite
    
//%classPrototypes {
public:
    const std::string& Filename(void) const { return m_filename; }
    void FilenameSet(const std::string& inValue) { m_filename=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } xJVc2BAp9iykej3O+aElGA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLPixelSourceTIFF& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 5BAQQlXQC1ekl4kX6Wc5+Q
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
