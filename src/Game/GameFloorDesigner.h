#ifndef GAMEFLOORDESIGNER_H
#define GAMEFLOORDESIGNER_H
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
 * $Id: GameFloorDesigner.h,v 1.10 2002/10/22 20:42:04 southa Exp $
 * $Log: GameFloorDesigner.h,v $
 * Revision 1.10  2002/10/22 20:42:04  southa
 * Source conditioning
 *
 * Revision 1.9  2002/10/08 17:13:17  southa
 * Tiered maps
 *
 * Revision 1.8  2002/08/27 08:56:23  southa
 * Source conditioning
 *
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
 * First floor std::map designer build
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
        kUndoBufferSize=8,
        kNumTiers=5,
    };
    
    const GLPoint TranslateWindowToMap(const GLPoint& inPoint);
    void Paste(const GLPoint& inDest);
    void SaveForUndo(void);
    void Undo(void);
    void Redo(void);
    void Save(void);
    void MoveTiers(Mushware::S32 inStep);
    
    std::vector<GLPoint> m_pos;
    string m_controllerName;
    mutable GameController *m_controller; // in GameData
    GameTileMap *m_tileMap;
    std::vector<GameFloorMap *> m_floorMaps;
    Mushware::U32 m_currentMap;
    Mushware::U32 m_highlightMap;
    GLRectangle m_highlight;
    bool m_primaryButtonState;
    bool m_secondaryButtonState;
    GLPoint m_downPoint;
    Mushware::tVal m_width;
    Mushware::tVal m_height;
    std::vector<GameFloorMap> m_undoBuffer;
    Mushware::U32 m_currentUndoBuffer;
    Mushware::U32 m_lastUndoBuffer;
    GameFloorMap m_scratchArea;
    Mushware::tVal m_masterScale;
    std::vector<bool> m_tierFlags;
};
#endif
