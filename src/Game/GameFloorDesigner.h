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
 * $Id: GameFloorDesigner.h,v 1.7 2002/08/17 10:41:51 southa Exp $
 * $Log: GameFloorDesigner.h,v $
 * Revision 1.7  2002/08/17 10:41:51  southa
 * Designer fixes
 *
 * Revision 1.6  2002/08/07 13:36:49  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/07 13:25:56  southa
 * Template designer
 *
 * Revision 1.4  2002/07/07 11:16:07  southa
 * More designer work
 *
 * Revision 1.3  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.2  2002/07/02 18:36:56  southa
 * Selection in designer, mouse buttons
 *
 * Revision 1.1  2002/07/02 14:27:09  southa
 * First floor map designer build
 *
 */

#include "mushCore.h"
#include "mushGL.h"

#include "GameFloorMap.h"

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

    enum
    {
        kUndoBufferSize=8
    };
    
    const GLPoint TranslateWindowToMap(const GLPoint& inPoint);
    void Paste(const GLPoint& inDest);
    void SaveForUndo(void);
    void Undo(void);
    void Redo(void);
    void Save(void);
    
    vector<GLPoint> m_pos;
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
    bool m_lastRedoKeyState;
    bool m_lastSaveKeyState;
    vector<GameFloorMap> m_undoBuffer;
    U32 m_currentUndoBuffer;
    U32 m_lastUndoBuffer;
    GameFloorMap m_scratchArea;
    tVal m_masterScale;
};
#endif
