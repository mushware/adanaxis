//%includeGuardStart {
#ifndef INFERNALTILESPEC_H
#define INFERNALTILESPEC_H
//%includeGuardStart } LkXPOgCVQp4N3Nsiy47wpA
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalTileSpec.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } BNjKCsSWcom9cMuDXrAdow
/*
 * $Id: InfernalTileSpec.h,v 1.2 2004/01/02 21:13:09 southa Exp $
 * $Log: InfernalTileSpec.h,v $
 * Revision 1.2  2004/01/02 21:13:09  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/04 12:23:07  southa
 * File renaming
 *
 * Revision 1.9  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:08:56  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/02/05 18:49:51  southa
 * Build fixes
 *
 * Revision 1.6  2003/01/12 17:32:56  southa
 * Mushcore work
 *
 * Revision 1.5  2003/01/11 13:03:15  southa
 * Use Mushcore header
 *
 * Revision 1.4  2002/12/20 13:17:43  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/10/22 20:42:06  southa
 * Source conditioning
 *
 * Revision 1.2  2002/10/15 14:33:39  southa
 * Fixed include
 *
 * Revision 1.1  2002/10/13 12:26:48  southa
 * Facetised std::map rendering
 *
 */

#include "mushMushcore.h"
#include "mushGL.h"

class InfernalTileTraits;

class InfernalTileSpec
{
public:
    InfernalTileSpec() {}
    InfernalTileSpec(InfernalTileTraits *inTraits, Mushware::tVal inRotation) :
        m_pTraits(inTraits),
        m_rotation(inRotation)
    {}

    bool TileTraitsAreNull(void) { return m_pTraits == NULL; }
    InfernalTileTraits& TileTraitsGet(void) const;
    void TileTraitsSet(InfernalTileTraits *inTraits) { m_pTraits=inTraits; }
    Mushware::tVal RotationGet(void) const { return m_rotation; }    
    
    void RenderPrologue(void) const;
    void RenderEpilogue(void) const;
    
private:
    InfernalTileTraits *m_pTraits;
    Mushware::tVal m_rotation;
};

inline InfernalTileTraits&
InfernalTileSpec::TileTraitsGet(void) const
{
    MUSHCOREASSERT(m_pTraits != NULL);
    return *m_pTraits;
}

inline void
InfernalTileSpec::RenderPrologue(void) const
{
    if (m_rotation != 0)
    {
        GLUtils::PushMatrix();
        GLUtils::RotateAboutZ(m_rotation);
    }
}

inline void
InfernalTileSpec::RenderEpilogue(void) const
{
    if (m_rotation != 0)
    {
        GLUtils::PopMatrix();
    }    
}

std::ostream&
operator<<(std::ostream &inOut, const InfernalTileSpec& inSpec);
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
