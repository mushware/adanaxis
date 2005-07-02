//%includeGuardStart {
#ifndef MUSHMESHPATCHEND_H
#define MUSHMESHPATCHEND_H
//%includeGuardStart } FkLmlDE9HMg2XY182Hj7XQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPatchEnd.h
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
//%Header } AX68yLXFdthnGkLe1+UC1Q

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
