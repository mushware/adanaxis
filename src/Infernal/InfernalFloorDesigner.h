//%includeGuardStart {
#ifndef INFERNALFLOORDESIGNER_H
#define INFERNALFLOORDESIGNER_H
//%includeGuardStart } a/R0H72dUo9YxBS9NRHlmQ
//%Header {
/*****************************************************************************
 *
 * File: src/Game/InfernalFloorDesigner.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } kigtSChfDQWeDlMu3D8u+Q
/*
 * $Id: InfernalFloorDesigner.h,v 1.15 2003/09/17 19:40:32 southa Exp $
 * $Log: InfernalFloorDesigner.h,v $
 * Revision 1.15  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.14  2003/08/21 23:08:44  southa
 * Fixed file headers
 *
 * Revision 1.13  2003/01/11 13:03:13  southa
 * Use Mushcore header
 *
 * Revision 1.12  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.11  2002/12/20 13:17:40  southa
 * Namespace changes, licence changes and source conditioning
 *
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

#include "Mushcore.h"
#include "mushGL.h"

#include "InfernalFloorMap.h"

class InfernalTileMap;
class GameController;

class InfernalFloorDesigner
{
public:
    InfernalFloorDesigner();
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
    std::string m_controllerName;
    mutable GameController *m_controller; // in InfernalData
    InfernalTileMap *m_tileMap;
    std::vector<InfernalFloorMap *> m_floorMaps;
    Mushware::U32 m_currentMap;
    Mushware::U32 m_highlightMap;
    GLRectangle m_highlight;
    bool m_primaryButtonState;
    bool m_secondaryButtonState;
    GLPoint m_downPoint;
    Mushware::tVal m_width;
    Mushware::tVal m_height;
    std::vector<InfernalFloorMap> m_undoBuffer;
    Mushware::U32 m_currentUndoBuffer;
    Mushware::U32 m_lastUndoBuffer;
    InfernalFloorMap m_scratchArea;
    Mushware::tVal m_masterScale;
    std::vector<bool> m_tierFlags;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
