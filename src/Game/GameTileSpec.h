/*
 * $Id: GameTileSpec.h,v 1.1 2002/10/13 12:26:48 southa Exp $
 * $Log: GameTileSpec.h,v $
 * Revision 1.1  2002/10/13 12:26:48  southa
 * Facetised map rendering
 *
 */

#include "mushCore.h"
#include "mushGL.h"

class GameTileTraits;

class GameTileSpec
{
public:
    GameTileSpec() {}
    GameTileSpec(GameTileTraits *inTraits, tVal inRotation) :
        m_pTraits(inTraits),
        m_rotation(inRotation)
    {}

    bool TileTraitsAreNull(void) { return m_pTraits == NULL; }
    GameTileTraits& TileTraitsGet(void) const;
    void TileTraitsSet(GameTileTraits *inTraits) { m_pTraits=inTraits; }
    tVal RotationGet(void) const { return m_rotation; }    
    
    void RenderPrologue(void) const;
    void RenderEpilogue(void) const;
    
private:
    GameTileTraits *m_pTraits;
    tVal m_rotation;
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

ostream& operator<<(ostream &inOut, const GameTileSpec& inSpec);
