#ifndef GAMETILESPEC_H
#define GAMETILESPEC_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GameTileSpec.h,v 1.7 2003/02/05 18:49:51 southa Exp $
 * $Log: GameTileSpec.h,v $
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

#include "Mushcore.h"
#include "mushGL.h"

class GameTileTraits;

class GameTileSpec
{
public:
    GameTileSpec() {}
    GameTileSpec(GameTileTraits *inTraits, Mushware::tVal inRotation) :
        m_pTraits(inTraits),
        m_rotation(inRotation)
    {}

    bool TileTraitsAreNull(void) { return m_pTraits == NULL; }
    GameTileTraits& TileTraitsGet(void) const;
    void TileTraitsSet(GameTileTraits *inTraits) { m_pTraits=inTraits; }
    Mushware::tVal RotationGet(void) const { return m_rotation; }    
    
    void RenderPrologue(void) const;
    void RenderEpilogue(void) const;
    
private:
    GameTileTraits *m_pTraits;
    Mushware::tVal m_rotation;
};

inline GameTileTraits&
GameTileSpec::TileTraitsGet(void) const
{
    MUSHCOREASSERT(m_pTraits != NULL);
    return *m_pTraits;
}

inline void
GameTileSpec::RenderPrologue(void) const
{
    if (m_rotation != 0)
    {
        GLUtils::PushMatrix();
        GLUtils::RotateAboutZ(m_rotation);
    }
}

inline void
GameTileSpec::RenderEpilogue(void) const
{
    if (m_rotation != 0)
    {
        GLUtils::PopMatrix();
    }    
}

std::ostream&
operator<<(std::ostream &inOut, const GameTileSpec& inSpec);
#endif
