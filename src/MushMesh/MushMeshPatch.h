//%includeGuardStart {
#ifndef MUSHMESHPATCH_H
#define MUSHMESHPATCH_H
//%includeGuardStart } WBwzTC4+Y/UtxsqEMY/TRg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPatch.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } zOjScA/10RD7ybR0LwcvFw

#include "MushMeshStandard.h"

class MushMeshPatch
{
public:
    virtual ~MushMeshPatch() {}
    // virtual void Render(void /* some render context */) = 0;
    virtual void Subdivide(Mushware::tVal inLevel) = 0;

};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
