#ifndef GAMEFLOORMAP_H
#define GAMEFLOORMAP_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/



/*
 * $Id: GameFloorMap.h,v 1.10 2002/07/31 16:27:16 southa Exp $
 * $Log: GameFloorMap.h,v $
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
 * First floor map designer build
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

#include "mushCore.h"
#include "mushGL.h"
#include "GameSolidMap.h"

class GameTileMap;
class GameMapArea;
class GameMapPoint;

class GameFloorMap : public CorePickle, private CoreXMLHandler
{
public:
    GameFloorMap(): m_state(kInit), m_solidMapValid(false), m_tileMap(NULL) {}
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    U32 At(U32 inX, U32 inY) {COREASSERT(inX<m_xsize);COREASSERT(inY<m_ysize);return m_map[inY][inX];}
    U32 XSize(void) {return m_xsize;}
    U32 YSize(void) {return m_ysize;}
    tVal XStep(void) {return m_xstep;}
    tVal YStep(void) {return m_ystep;}
    void Render(const GameMapArea& inArea, const GameMapArea& inHighlight);
    void RenderSolidMap(const GameMapArea& inArea);
    
    U32 ElementGet(const GLPoint &inPoint) const;
    void ElementSet(const GLPoint &inPoint, U32 inValue);
    tVal PermeabilityGet(const GameMapPoint &inPoint) const;
    void AttachTileMap(GameTileMap *inTileMap) { m_tileMap=inTileMap; }
    const GameSolidMap& SolidMapGet(void) const;
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
        kInit,
        kData,
        kNumStates
    };

private:
    void RebuildSolidMap(void) const;

    typedef map<string, void (GameFloorMap::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    U32 m_state;

    vector< vector<U32> > m_map;
    tSize m_xsize;
    tSize m_ysize;
    tVal m_xstep;
    tVal m_ystep;
    mutable GameSolidMap m_solidMap;
    mutable bool m_solidMapValid;
    GameTileMap *m_tileMap;
};

inline ostream& operator<<(ostream &inOut, const GameFloorMap& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
#endif
