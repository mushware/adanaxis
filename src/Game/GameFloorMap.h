#ifndef GAMEFLOORMAP_H
#define GAMEFLOORMAP_H
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
 * $Id: GameFloorMap.h,v 1.24 2002/12/20 13:17:40 southa Exp $
 * $Log: GameFloorMap.h,v $
 * Revision 1.24  2002/12/20 13:17:40  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.23  2002/11/24 23:18:16  southa
 * Added type name accessor to CorePickle
 *
 * Revision 1.22  2002/11/18 11:31:14  southa
 * Return to game mode
 *
 * Revision 1.21  2002/10/22 20:42:04  southa
 * Source conditioning
 *
 * Revision 1.20  2002/10/17 15:50:59  southa
 * Config saving, pause and quit
 *
 * Revision 1.19  2002/10/11 14:01:12  southa
 * Lighting work
 *
 * Revision 1.18  2002/10/10 18:25:15  southa
 * Light links and test lights
 *
 * Revision 1.17  2002/10/08 17:13:18  southa
 * Tiered maps
 *
 * Revision 1.16  2002/10/07 17:49:46  southa
 * Multiple values per std::map element
 *
 * Revision 1.15  2002/08/27 08:56:24  southa
 * Source conditioning
 *
 * Revision 1.14  2002/08/18 20:44:34  southa
 * Initial chequepoint work
 *
 * Revision 1.13  2002/08/18 15:13:15  southa
 * Adhesion handling
 *
 * Revision 1.12  2002/08/17 10:41:51  southa
 * Designer fixes
 *
 * Revision 1.11  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.10  2002/07/31 16:27:16  southa
 * Collision checking work
 *
 * Revision 1.9  2002/07/16 19:30:09  southa
 * Simplistic collision checking
 *
 * Revision 1.8  2002/07/16 17:48:08  southa
 * Collision and optimisation work
 *
 * Revision 1.7  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.6  2002/07/02 18:36:56  southa
 * Selection in designer, mouse buttons
 *
 * Revision 1.5  2002/07/02 14:27:10  southa
 * First floor std::map designer build
 *
 * Revision 1.4  2002/06/27 12:36:07  southa
 * Build process fixes
 *
 * Revision 1.3  2002/06/04 20:27:37  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
 * Revision 1.2  2002/06/04 14:12:26  southa
 * Traits loader first stage
 *
 * Revision 1.1  2002/05/30 16:21:53  southa
 * Pickleable GameContract
 *
 * Revision 1.5  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 * Revision 1.4  2002/05/28 13:05:55  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.3  2002/05/26 16:08:49  southa
 * CoreXML loader
 *
 * Revision 1.2  2002/05/25 17:16:15  southa
 * CoreXML implementation
 *
 * Revision 1.1  2002/05/24 18:08:35  southa
 * CoreXML and game map
 *
 */

#include "GameLightLinks.h"
#include "GameMap.h"
#include "GameSolidMap.h"
#include "mushCore.h"
#include "mushGL.h"

class GameTileMap;
class GameMapArea;
class GameMapPoint;

class GameFloorMap : public CorePickle, private CoreXMLHandler
{
public:

    typedef Mushware::U32 tMapValue;
    typedef std::vector<tMapValue> tMapVector;
    
    GameFloorMap(): m_state(kInit), m_solidMapValid(false), m_tileMap(NULL), m_lightMapValid(false) {}
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual char *TypeNameGet(void) const;
    
    const tMapVector& At(Mushware::U32 inX, Mushware::U32 inY) {COREASSERT(inX<m_xsize);COREASSERT(inY<m_ysize);return m_map[inY][inX];}
    Mushware::U32 XSize(void) {return m_xsize;}
    Mushware::U32 YSize(void) {return m_ysize;}
    Mushware::tVal XStep(void) {return m_xstep;}
    Mushware::tVal YStep(void) {return m_ystep;}
    GLPoint SizeGet(void) { return GLPoint(m_xsize, m_ysize); }
    GLPoint StepGet(void) { return GLPoint(m_xstep, m_ystep); }

    const GameMapPoint SpaceToMap(const GameSpacePoint inPoint) const;
    const GameMapPoint SpaceToMapFractional(const GameSpacePoint inPoint) const;
    const GameSpacePoint MapToSpace(const GameMapPoint inPoint) const;
    bool IsInMap(const GameMapPoint inPoint) const;

    void Render(const GameMapArea& inArea, const GameMapArea& inHighlight, const std::vector<bool>& inTierHighlight);
    void RenderSolidMap(const GameMapArea& inArea) const;
    void RenderAdhesionMap(const GameMapArea& inArea) const;
    void RenderLightMap(const GameMapArea& inArea) const;
        
    const tMapVector& ElementGet(const GLPoint &inPoint) const;
    const tMapVector& ElementGet(const GameSpacePoint &inPoint) const;
    const tMapVector& ElementGet(const GameMapPoint &inPoint) const;
    void ElementSet(const GLPoint &inPoint, const tMapVector& inValue);
    Mushware::tVal PermeabilityGet(const GameMapPoint &inPoint) const;
    Mushware::tVal AdhesionGet(const GameSpacePoint &inPoint) const;
    Mushware::tVal AdhesionGet(const GameMapPoint &inPoint) const;
    void SetLightingFor(const GameSpacePoint &inPoint) const;
    void SetLightingFor(const GameMapPoint &inPoint) const;
    void AttachTileMap(GameTileMap *inTileMap) { m_tileMap=inTileMap; }
    const GameSolidMap& SolidMapGet(void) const;
    void SolidMapInvalidate(void) { m_solidMapValid=false; }
    void LightMapInvalidate(void) { m_lightMapValid=false; }
   
    static CoreScalar LoadFloorMap(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static void Install(void);

protected:
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

    void HandleDataEnd(CoreXML& inXML);
    void HandleGameFloorMapStart(CoreXML& inXML);
    void HandleGameFloorMapEnd(CoreXML& inXML);
    void NullHandler(CoreXML& inXML);

    enum
    {
        kInvalid,
        kInit,
        kData,
        kNumStates
    };

private:
    void RebuildSolidMap(void) const;
    void RebuildLightMap(void) const;

    typedef std::map<string, void (GameFloorMap::*)(CoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    Mushware::U32 m_state;
    
    std::vector< std::vector< tMapVector > > m_map;
    Mushware::U32 m_xsize;
    Mushware::U32 m_ysize;
    Mushware::tVal m_xstep;
    Mushware::tVal m_ystep;
    mutable GameSolidMap m_solidMap;
    mutable bool m_solidMapValid;
    GameTileMap *m_tileMap;
    
    mutable GameMap<GameLightLinks> m_lightMap;
    mutable bool m_lightMapValid;
    
    static tMapVector m_emptyMapVector;
};

inline std::ostream& operator<<(std::ostream &inOut, const GameFloorMap& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
#endif
