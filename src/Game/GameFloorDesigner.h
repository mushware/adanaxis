/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class GameFloorMap;
class GameTileMap;
class GameController;

class GameFloorDesigner
{
public:
    void Display(void);
    void Move(void);
    void Init(void);
    
private:
    tVal m_x;
    tVal m_y;
    string m_controllerName;
    mutable GameController *m_controller; // in GameData
    GameTileMap *m_tileMap;
    vector<GameFloorMap *>m_floorMaps;
};
