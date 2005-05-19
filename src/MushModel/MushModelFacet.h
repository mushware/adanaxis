//%includeGuardStart {
#ifndef MUSHMODELFACET_H
#define MUSHMODELFACET_H
//%includeGuardStart } ekWoJKi499bLm+Eqn8fo/w
//%Header {
/*****************************************************************************
 *
 * File: src/MushModel/MushModelFacet.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } edr+IsFCWwFE/fGY1LZExA
/*
 * $Id: MushModelFacet.h,v 1.5 2005/02/10 12:34:09 southa Exp $
 * $Log: MushModelFacet.h,v $
 * Revision 1.5  2005/02/10 12:34:09  southa
 * Template fixes
 *
 * Revision 1.4  2005/02/03 21:03:03  southa
 * Build fixes
 *
 * Revision 1.3  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
 * Revision 1.2  2004/01/08 22:41:10  southa
 * MushModel commands
 *
 * Revision 1.1  2004/01/07 18:01:19  southa
 * MushModel and Infernal work
 *
 */

#include "MushModelStandard.h"

#include "mushGL.h"

#include "MushModelMaterial.h"

//:generate virtual standard ostream xml1
class MushModelFacet : public MushcoreVirtualObject
{
public:
    MushModelFacet() {}
    virtual ~MushModelFacet() {}
    
private:
    std::string m_renderType; //:readwrite
    MushcoreDataRef<MushModelMaterial> m_materialRef; //:readwrite
    std::vector<Mushware::t3Val> m_vertices; //:readwrite
    std::vector< std::vector<Mushware::t4Val> > m_texCoords; //:readwrite
    std::vector<Mushware::t3Val> m_normals; //:readwrite
//%classPrototypes {
public:
    const std::string& RenderType(void) const { return m_renderType; }
    void RenderTypeSet(const std::string& inValue) { m_renderType=inValue; }
    const MushcoreDataRef<MushModelMaterial>& MaterialRef(void) const { return m_materialRef; }
    void MaterialRefSet(const MushcoreDataRef<MushModelMaterial>& inValue) { m_materialRef=inValue; }
    const std::vector<Mushware::t3Val>& Vertices(void) const { return m_vertices; }
    void VerticesSet(const std::vector<Mushware::t3Val>& inValue) { m_vertices=inValue; }
    const std::vector< std::vector<Mushware::t4Val> >& TexCoords(void) const { return m_texCoords; }
    void TexCoordsSet(const std::vector< std::vector<Mushware::t4Val> >& inValue) { m_texCoords=inValue; }
    const std::vector<Mushware::t3Val>& Normals(void) const { return m_normals; }
    void NormalsSet(const std::vector<Mushware::t3Val>& inValue) { m_normals=inValue; }
    virtual const char *AutoNameGet(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 52pb6TXzqoPnUA09USnWcw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushModelFacet& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 03eBAmcmyjJc7hMFTGzhZQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
