//%includeGuardStart {
#ifndef MUSHMESHPATCHPIPE_H
#define MUSHMESHPATCHPIPE_H
//%includeGuardStart } gemvGRbDI5PU4GuNRmK/yQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPatchPipe.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } KcM46pJdcLwI+HHX/eMyxA

#include "MushMeshStandard.h"

#include "MushMeshArray.h"
#include "MushMeshBox.h"
#include "MushMeshPatch.h"
#include "MushMeshVector.h"
#include "MushMeshWorkspaceBased.h"

//:generate ostream
class MushMeshPatchPipe : public MushMeshPatch
{
public:
    typedef MushMeshVector<tCoordinateValue, kGeometryOrder> tGeometryVector;
    typedef MushMeshArray<tGeometryVector> tGeometryArray;
    typedef MushMeshVector<tTexCoordValue, kTexCoordOrder> tTexCoordVector;
    typedef MushMeshArray<tTexCoordVector> tTexCoordArray;
    typedef Mushware::t2BoxU32 tActiveBox;

    virtual void GeometrySet(const tGeometryArray& inArray);
    virtual void TexCoordSet(const tTexCoordArray& inArray, Mushware::U32 inIndex);

    // virtual void Render(void /* some render context */) = 0;
    virtual void Subdivide(Mushware::tVal inLevel);

private:
    MushMeshWorkspaceBased<tGeometryArray> m_geometry;
    
    MushMeshWorkspaceBased< std::vector<tTexCoordArray> > m_texCoords;

    tActiveBox m_activeBox;
//%classPrototypes {
public:
    void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } igNZsqh+Ffme42HZCDZW6Q
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshPatchPipe& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } kYQL8EqY9bCHCgXqtHxUig
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
