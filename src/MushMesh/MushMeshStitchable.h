//%includeGuardStart {
#ifndef MUSHMESHSTITCHABLE_H
#define MUSHMESHSTITCHABLE_H
//%includeGuardStart } aYdUXjykoRCdCOUILW3tHg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshStitchable.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } W3kyDNAJV5Y8c9Vy1zFOEQ
/*
 * $Id$
 * $Log$
 */

#include "MushMeshStandard.h"

#include "MushMeshBox.h"
#include "MushMeshPatchTypes.h"

class MushMeshStitchable
{
public:
    MushMeshStitchable();    
private:
    const Mushware::tGeometryArray *m_pGeometry;
    const Mushware::tTexCoordArray *m_pTex;
    const Mushware::t2BoxU32 *m_pActiveBox;
    Mushware::t2U32 m_start;
    Mushware::t2U32 m_stride;
};

inline
MushMeshStitchable::MushMeshStitchable() :
    m_pGeometry(NULL),
    m_pTex(NULL),
    m_pActiveBox(NULL)
{
}



//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
