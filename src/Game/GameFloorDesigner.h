#ifndef GAMEFLOORDESIGNER_H
#define GAMEFLOORDESIGNER_H
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
 * $Id: GameFloorDesigner.h,v 1.2 2002/07/02 18:36:56 southa Exp $
 * $Log: GameFloorDesigner.h,v $
 * Revision 1.2  2002/07/02 18:36:56  southa
 * Selection in designer, mouse buttons
 *
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
    void Paste(const GLPoint& inDest);
    void SaveForUndo(void);
    void Undo(void);
    void Save(void);
    
    vector<tVal> m_xPos;
    vector<tVal> m_yPos;
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
    bool m_lastUndoKeyState;
    bool m_lastSaveKeyState;
};
#endif
