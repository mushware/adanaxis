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
#include "MushMeshPatch.h"
#include "MushMeshVector.h"

class MushMeshPatchPipe : public MushMeshPatch
{
public:
    typedef MushMeshVector<Mushware::tVal, 4> tVector;
    typedef MushMeshArray<tVector> tArray;
    // virtual void Render(void /* some render context */) = 0;
    virtual void Subdivide(Mushware::tVal inLevel);

private:
    tArray m_values;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
