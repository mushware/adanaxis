//%includeGuardStart {
#ifndef MUSHMODELFACET_H
#define MUSHMODELFACET_H
//%includeGuardStart } ekWoJKi499bLm+Eqn8fo/w
//%Header {
/*****************************************************************************
 *
 * File: src/MushModel/MushModelFacet.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } KMRuFiR9Rvu+S944rUHZ1g
/*
 * $Id: MushModelFacet.h,v 1.3 2004/01/10 20:29:35 southa Exp $
 * $Log: MushModelFacet.h,v $
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

//:generate standard ostream xml1
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
    virtual MushModelFacet *AutoClone(void) const;
    virtual MushModelFacet *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 4RuU6lzH/VFGQv3VIQUMzg
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
