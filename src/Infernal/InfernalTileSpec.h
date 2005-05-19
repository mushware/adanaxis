//%includeGuardStart {
#ifndef INFERNALTILESPEC_H
#define INFERNALTILESPEC_H
//%includeGuardStart } LkXPOgCVQp4N3Nsiy47wpA
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalTileSpec.h
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
//%Header } OJHDDbuKrOuabNemmb2N/w
/*
 * $Id: InfernalTileSpec.h,v 1.3 2004/01/06 20:46:51 southa Exp $
 * $Log: InfernalTileSpec.h,v $
 * Revision 1.3  2004/01/06 20:46:51  southa
 * Build fixes
 *
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
