//%includeGuardStart {
#ifndef MUSHMESHPATCHEND_H
#define MUSHMESHPATCHEND_H
//%includeGuardStart } FkLmlDE9HMg2XY182Hj7XQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPatchEnd.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 15+xl0fcNhfldc8LXlwMxA

#include "MushMeshStandard.h"

#include "MushMeshArray.h"
#include "MushMeshBox.h"
#include "MushMeshPatch.h"
#include "MushMeshPatchTypes.h"
#include "MushMeshSelection.h"
#include "MushMeshStitchable.h"
#include "MushMeshVector.h"
#include "MushMeshWorkspaceBased.h"

//:generate ostream
class MushMeshPatchEnd : public MushMeshPatch
{
public:
    typedef Mushware::t2BoxU32 tActiveBox;

    virtual const Mushware::tGeometryArray& GeometryGet(void);
    virtual void GeometrySet(const Mushware::tGeometryArray& inArray);
    virtual const Mushware::tTexCoordArray& TexCoordGet(Mushware::U32 inIndex);
    virtual void TexCoordSet(const Mushware::tTexCoordArray& inArray, Mushware::U32 inIndex);

    // virtual void Render(void /* some render context */) = 0;
    virtual void Subdivide(Mushware::tVal inLevel);
    virtual void EdgeGet(MushMeshStitchable& outStitchable, tEdgeSelector inEdge);
    virtual void NeighbourSet(const MushMeshStitchable& inStitchable, tEdgeSelector inEdge);

private:
    void EdgeDefsGenerate(void);

    MushMeshWorkspaceBased<Mushware::tGeometryArray> m_geometry;
    
    MushMeshWorkspaceBased<Mushware::tTexCoordArrayVector> m_texCoords;

    tActiveBox m_activeBox;

    std::vector<MushMeshSelection> m_edgeDefs;
    std::vector<MushMeshSelection> m_neighbourDefs;

//%classPrototypes {
public:
    void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } igNZsqh+Ffme42HZCDZW6Q
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshPatchEnd& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } UJQ+sNhMGkUK88RpdwygyA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
