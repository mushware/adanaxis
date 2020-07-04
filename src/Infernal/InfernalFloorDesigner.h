//%includeGuardStart {
#ifndef INFERNALFLOORDESIGNER_H
#define INFERNALFLOORDESIGNER_H
//%includeGuardStart } a/R0H72dUo9YxBS9NRHlmQ
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalFloorDesigner.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } KagQVpnxwTylPYnwKmLwsw
/*
 * $Id: InfernalFloorDesigner.h,v 1.6 2006/06/01 15:39:02 southa Exp $
 * $Log: InfernalFloorDesigner.h,v $
 * Revision 1.6  2006/06/01 15:39:02  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:04  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.3  2004/01/02 21:13:08  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/04 12:44:34  southa
 * File renaming
 *
 * Revision 1.1  2003/10/04 12:23:05  southa
 * File renaming
 *
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

#include "mushMushcore.h"
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
