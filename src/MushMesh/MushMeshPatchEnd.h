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
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } IQeOleRzx2FiLffTdjVuiA

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

    MushMeshPatchEnd() : m_order(0) {}

    Mushware::U32 OrderGet(void) const { return m_order; }
    void OrderSet(Mushware::U32 inOrder);

    virtual const Mushware::tGeometryArray& GeometryGet(void);
    virtual void GeometrySet(const Mushware::tGeometryArray& inArray);
    virtual const Mushware::tTexCoordArray& TexCoordGet(Mushware::U32 inIndex);
    virtual void TexCoordSet(const Mushware::tTexCoordArray& inArray, Mushware::U32 inIndex);

    // virtual void Render(void /* some render context */) = 0;
    virtual void Subdivide(Mushware::tVal inLevel);
    virtual void EdgeStitchableGet(MushMeshStitchable& outStitchable, tEdgeSelector inEdge);

    virtual void NeighbourSet(const MushMeshStitchable& inStitchable, tEdgeSelector inEdge);

protected:
    virtual void NeighbourSelectionGet(MushMeshSelection& outSelection, tEdgeSelector inEdge);

private:
    MushMeshWorkspaceBased<Mushware::tGeometryArray> m_geometry;
    
    MushMeshWorkspaceBased<Mushware::tTexCoordArrayVector> m_texCoords;

    tActiveBox m_activeBox;

    Mushware::U32 m_order;

    std::vector<MushMeshSelection> m_edgeDefs;
    std::vector<MushMeshSelection> m_neighbourDefs;

//%classPrototypes {
public:
    virtual void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } b86DSDsq8lQQbiM0rrNtkg
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
