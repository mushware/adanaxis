/*
 * $Id: GameFloorDesigner.h,v 1.1 2002/07/02 14:27:09 southa Exp $
 * $Log: GameFloorDesigner.h,v $
 * Revision 1.1  2002/07/02 14:27:09  southa
 * First floor map designer build
 *
 */

#include "mushCore.h"
#include "mushGL.h"

class GameFloorMap;
class GameTileMap;
class GameController;

class GameFloorDesigner
{
public:
    GameFloorDesigner();
    void Display(void);
    void Move(void);
    void Init(void);
    
private:
    const GLPoint TranslateWindowToMap(const GLPoint& inPoint);

    tVal m_xPos;
    tVal m_yPos;
    string m_controllerName;
    mutable GameController *m_controller; // in GameData
    GameTileMap *m_tileMap;
    vector<GameFloorMap *> m_floorMaps;
    U32 m_currentMap;
    U32 m_highlightMap;
    GLRectangle m_highlight;
    bool m_primaryButtonState;
    bool m_secondaryButtonState;
    GLPoint m_downPoint;
    tVal m_width;
    tVal m_height;
};
