#ifndef GAMETILESPEC_H
#define GAMETILESPEC_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GameTileSpec.h,v 1.3 2002/10/22 20:42:06 southa Exp $
 * $Log: GameTileSpec.h,v $
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

#include "mushCore.h"
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
    COREASSERT(m_pTraits != NULL);
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

ostream& operator<<(std::ostream &inOut, const GameTileSpec& inSpec);
#endif
