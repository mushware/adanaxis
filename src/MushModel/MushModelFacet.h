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
 * $Id$
 * $Log$
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
    Mushware::U32 m_type; //:readwrite
    MushcoreDataRef<MushModelMaterial> m_material; //:readwrite
    std::vector<Mushware::t3Val> m_vertices; //:readwrite
    std::vector<Mushware::t4Val> m_texCoords; //:readwrite
    std::vector<Mushware::t3Val> m_normals; //:readwrite
//%classPrototypes {
public:
    const Mushware::U32& TypeGet(void) const { return m_type; }
    void TypeSet(const Mushware::U32& inValue) { m_type=inValue; }
    const MushcoreDataRef<MushModelMaterial>& MaterialGet(void) const { return m_material; }
    void MaterialSet(const MushcoreDataRef<MushModelMaterial>& inValue) { m_material=inValue; }
    const std::vector<Mushware::t3Val>& VerticesGet(void) const { return m_vertices; }
    void VerticesSet(const std::vector<Mushware::t3Val>& inValue) { m_vertices=inValue; }
    const std::vector<Mushware::t4Val>& TexCoordsGet(void) const { return m_texCoords; }
    void TexCoordsSet(const std::vector<Mushware::t4Val>& inValue) { m_texCoords=inValue; }
    const std::vector<Mushware::t3Val>& NormalsGet(void) const { return m_normals; }
    void NormalsSet(const std::vector<Mushware::t3Val>& inValue) { m_normals=inValue; }
    virtual const char *AutoNameGet(void) const;
    virtual MushModelFacet *AutoClone(void) const;
    virtual MushModelFacet *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    void AutoPrint(std::ostream& ioOut) const;
    bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } XF2WvlQiGZ82GQK638VaQw
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
