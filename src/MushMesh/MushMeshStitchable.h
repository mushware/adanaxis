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
 * $Id: MushMeshStitchable.h,v 1.1 2003/10/19 12:41:42 southa Exp $
 * $Log: MushMeshStitchable.h,v $
 * Revision 1.1  2003/10/19 12:41:42  southa
 * Connectors
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshBox.h"
#include "MushMeshPatchTypes.h"
#include "MushMeshSelection.h"

//:generate ostream
class MushMeshStitchable
{
public:
    MushMeshStitchable();

    void SourceSet(const Mushware::tGeometryArray *inpGeometry,
        const Mushware::tTexCoordArrayVector *inpTexVector,
        const Mushware::t2BoxU32 *inpActiveBox)
    {
         m_pGeometry = inpGeometry;
         m_pTexVector = inpTexVector;
         m_pActiveBox = inpActiveBox;
    }
    void SelectionSet(const MushMeshSelection& inSelection) { m_selection = inSelection; }

private:
    const Mushware::tGeometryArray *m_pGeometry;
    const Mushware::tTexCoordArrayVector *m_pTexVector;
    const Mushware::t2BoxU32 *m_pActiveBox;
    MushMeshSelection m_selection;
//%classPrototypes {
public:
    void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } igNZsqh+Ffme42HZCDZW6Q
};

inline
MushMeshStitchable::MushMeshStitchable() :
    m_pGeometry(NULL),
    m_pTexVector(NULL),
    m_pActiveBox(NULL)
{
}
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshStitchable& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Wx3nk1y5jLk1s+0OauoKGQ

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
