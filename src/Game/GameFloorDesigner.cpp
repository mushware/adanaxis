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
 * $Id: GameFloorDesigner.cpp,v 1.7 2002/07/08 14:22:02 southa Exp $
 * $Log: GameFloorDesigner.cpp,v $
 * Revision 1.7  2002/07/08 14:22:02  southa
 * Rotated desks
 *
 * Revision 1.6  2002/07/07 13:25:56  southa
 * Template designer
 *
 * Revision 1.5  2002/07/07 11:16:07  southa
 * More designer work
 *
 * Revision 1.4  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.3  2002/07/02 19:29:01  southa
 * Tidied up selection effect in designer
 *
 * Revision 1.2  2002/07/02 18:36:56  southa
 * Selection in designer, mouse buttons
 *
 * Revision 1.1  2002/07/02 14:27:09  southa
 * First floor map designer build
 *
 */

#include "GameFloorDesigner.h"

#include "mushGL.h"
#include "GameData.h"
#include "GameController.h"
#include "GameMapArea.h"

GameFloorDesigner::GameFloorDesigner():
    m_controller(NULL),
    m_tileMap(NULL)
    {}

void
GameFloorDesigner::Init(void)
{
    GLAppHandler& glHandler=dynamic_cast<GLAppHandler &>(CoreAppHandler::Instance());
    m_controllerName="controller1";
    m_tileMap=GameData::Instance().TileMapGet("tiles");
    m_floorMaps.push_back(GameData::Instance().FloorMapGet("floor"));
    m_floorMaps.push_back(GameData::Instance().FloorMapGet("floor"));
    m_floorMaps.push_back(GameData::Instance().FloorMapGet("floormap-template"));
    m_floorMaps.push_back(&m_scratchArea);
    m_scratchArea=*m_floorMaps[0];
    COREASSERT(m_tileMap != NULL);
    COREASSERT(m_floorMaps[0] != NULL);
    GameData::Instance().ControllerGetOrCreate(m_controllerName);
    m_width=glHandler.WidthGet();
    m_height=glHandler.HeightGet();
    for (U32 i=0; i<12;++i)
    {
        m_xPos.push_back(glHandler.WidthGet()/2);
        m_yPos.push_back(glHandler.HeightGet()/2);
    }
    for (U32 i=0; i<kUndoBufferSize; ++i)
    {
        m_undoBuffer.push_back(*m_floorMaps[0]);
    }
        
    m_highlight=GLRectangle();
    m_highlightMap=0;
    m_currentMap=0;
    m_currentUndoBuffer=0;
    m_lastUndoBuffer=0;
    m_primaryButtonState=false;
    m_secondaryButtonState=false;
    m_lastUndoKeyState=false;
    m_lastSaveKeyState=false;
}

void
GameFloorDesigner::Display(void)
{
    COREASSERT(m_currentMap < m_floorMaps.size());
    COREASSERT(m_currentMap < m_xPos.size());
    COREASSERT(m_currentMap < m_yPos.size());
    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    GLUtils::IdentityPrologue();
    GLUtils::OrthoLookAt(m_xPos[m_currentMap], m_yPos[m_currentMap], 0);
    GLPoint aimingPoint=GLPoint(m_xPos[m_currentMap] / m_floorMaps[m_currentMap]->XStep(),
                                m_yPos[m_currentMap] / m_floorMaps[m_currentMap]->YStep());
    GameMapArea visibleArea;
    tVal xRadius=(gameHandler.WidthGet() / 2) / m_floorMap->XStep();
    tVal yRadius=(gameHandler.HeightGet() / 2) / m_floorMap->YStep();
    tVal circleRadius=1+sqrt(xRadius*xRadius + yRadius*yRadius);
    visibleArea.CircleAdd(aimingPoint, circleRadius);

    GameMapArea highlightArea;
    if (m_highlightMap == m_currentMap)
    {
        highlightArea.RectangleAdd(m_highlight);
    }
    
    m_floorMaps[m_currentMap]->Render(visibleArea, highlightArea);

    GLUtils::IdentityEpilogue();
    GLUtils::DisplayEpilogue();
}

void
GameFloorDesigner::Move(void)
{
    COREASSERT(m_floorMaps.size() > 0);
    GLAppHandler& glHandler=dynamic_cast<GLAppHandler &>(CoreAppHandler::Instance());

    if (m_controller == NULL)
    {
        m_controller=GameData::Instance().ControllerGet(m_controllerName);
    }
    GameControllerState controlState;
    m_controller->StateGet(controlState);

    for (U32 i=0; i<m_floorMaps.size() && i<12 ; ++i)
    {
        if (glHandler.KeyStateGet(GLKeys::kKeyF1+i))
        {
            m_currentMap=i;
        }
    }
    if (m_currentMap >= m_floorMaps.size()) m_currentMap=m_floorMaps.size();
    
    bool primaryState(glHandler.KeyStateGet(GLKeys::kKeyMouse1));
    bool secondaryState(glHandler.KeyStateGet(GLKeys::kKeyMouse3));
    bool tertiaryState(glHandler.KeyStateGet(GLKeys::kKeyMouse2));

    // Make all maps apart from 0 read-only
    if (m_currentMap != 0)
    {
        secondaryState |= primaryState;
        primaryState=false;
    }
    
    if (m_secondaryButtonState != secondaryState)
    {
        if (secondaryState)
        {
            m_downPoint=GLPoint(controlState.mouseX, controlState.mouseY);
        }
    }

    if (secondaryState)
    {
        GLPoint start(m_downPoint);
        GLPoint end(controlState.mouseX, controlState.mouseY);
        
        if (end.x > start.x)
        {
            end.x+=m_floorMaps[m_currentMap]->XStep()/2;
        }
        else if (end.x < start.x)
        {
            start.x+=m_floorMaps[m_currentMap]->XStep()/2;
        }

        if (end.y > start.y)
        {
            end.y+=m_floorMaps[m_currentMap]->YStep()/2;
        }
        else if (end.y < start.y)
        {
            start.y+=m_floorMaps[m_currentMap]->YStep()/2;
        }
            
        m_highlight=GLRectangle(TranslateWindowToMap(start),
                                TranslateWindowToMap(end));
        m_highlight.FixUp();
        m_highlightMap=m_currentMap;
#if 0
        cerr << "Start was " << start.x << ", " << start.y;
        cerr << ", end was " << end.x << ", " << end.y << endl;
        cerr << "Translation was " << m_highlight.xmin << ", " <<
            m_highlight.ymin << ", " <<
            m_highlight.xmax << ", " <<
            m_highlight.ymax << endl;
#endif
    }

    tVal deltaX=0;
    tVal deltaY=0;
    if (tertiaryState)
    {
	    deltaX=-controlState.mouseXDelta;
        deltaY=-controlState.mouseYDelta;
    }

    tVal stepSize=m_floorMaps[0]->XStep();
    
    if (controlState.leftPressed)
    {
        deltaX = -stepSize;;
    }
    if (controlState.rightPressed)
    {
        deltaX = stepSize;
    }
    if (controlState.upPressed)
    {
        deltaY = stepSize;
    }
    if (controlState.downPressed)
    {
        deltaY = -stepSize;
    }
    m_xPos[m_currentMap] += deltaX;
    m_yPos[m_currentMap] += deltaY;

    bool undoKeyState=glHandler.KeyStateGet('z');
    if (undoKeyState && !m_lastUndoKeyState)
    {
        Undo();
    }
    m_lastUndoKeyState=undoKeyState;
    bool redoKeyState=glHandler.KeyStateGet('v');
    if (redoKeyState && !m_lastRedoKeyState)
    {
        Redo();
    }
    m_lastRedoKeyState=redoKeyState;
    bool saveKeyState=glHandler.KeyStateGet('s');
    if (saveKeyState && !m_lastSaveKeyState)
    {
        Save();
    }
    m_lastSaveKeyState=saveKeyState;
    
    if (primaryState)
    {
        if (!m_primaryButtonState)
        {
            SaveForUndo();
        }
        Paste(GLPoint(controlState.mouseX, controlState.mouseY));
    }
    m_primaryButtonState = primaryState;
    m_secondaryButtonState = secondaryState;
}

void
GameFloorDesigner::Paste(const GLPoint& inDest)
{
    COREASSERT(m_currentMap < m_floorMaps.size());
    COREASSERT(m_highlightMap < m_floorMaps.size());
    GameFloorMap *srcMap;
    if (m_currentMap == m_highlightMap)
    {
        // Read from the undo buffer if we're copying back to the same map
        srcMap=&m_undoBuffer[m_lastUndoBuffer];
    }
    else
    {
        srcMap=m_floorMaps[m_highlightMap];
    }
    GameFloorMap *destMap=m_floorMaps[m_currentMap];
    
    GLRectangle src(m_highlight); // Source rectangle
    GLPoint destPoint(TranslateWindowToMap(inDest));
    GLRectangle dest(destPoint, destPoint+src.Size());
    GLRectangle srcClip(0, 0, srcMap->XSize(), srcMap->YSize());
    GLRectangle destClip(0, 0, destMap->XSize(), destMap->YSize());

    src.Clip(srcClip);
    dest.Clip(destClip);

    for (S32 x=0; x<src.XSize() && x<dest.XSize(); ++x)
    {
        for (S32 y=0; y<src.YSize() && y<dest.YSize(); ++y)
        {
            GLPoint offset(x,y);
            // cerr << "Copying from " << (src.MinPoint()+offset) << " to " << (dest.MinPoint()+offset) << endl;
            destMap->ElementSet(dest.MinPoint()+offset,
                                srcMap->ElementGet(src.MinPoint()+offset));
        }
    }
}

void
GameFloorDesigner::SaveForUndo(void)
{
    m_lastUndoBuffer=m_currentUndoBuffer;
    m_undoBuffer[m_currentUndoBuffer]=*m_floorMaps[m_currentMap];
    m_lastUndoBuffer=m_currentUndoBuffer;
    m_currentUndoBuffer = (m_currentUndoBuffer+1) % kUndoBufferSize;
}

void
GameFloorDesigner::Undo(void)
{
    m_undoBuffer[m_currentUndoBuffer]=*m_floorMaps[m_currentMap]; // save for redo
    m_currentUndoBuffer = (m_currentUndoBuffer+kUndoBufferSize-1) % kUndoBufferSize;
    *m_floorMaps[m_currentMap]=m_undoBuffer[m_currentUndoBuffer];
}

void
GameFloorDesigner::Redo(void)
{
    m_currentUndoBuffer = (m_currentUndoBuffer+1) % kUndoBufferSize;
    *m_floorMaps[m_currentMap]=m_undoBuffer[m_currentUndoBuffer];
}

void
GameFloorDesigner::Save(void)
{
    string filename;
    const CoreScalar *pScalar;
    if (CoreEnv::Instance().VariableGetIfExists(&pScalar, "DESIGNER_MAP_NAME"))
    {
        filename=pScalar->StringGet();
    }
    else
    {
        filename=CoreEnv::Instance().VariableGet("CONTRACT_PATH").StringGet()+"/designer_map.xml";
    }
    cout << "Saving F1 buffer to file '" << filename << "'" << endl;

    ofstream outputFile(filename.c_str());
    if (!outputFile) throw(LoaderFail(filename, "Could not open file"));
    time_t now(time(NULL));
    outputFile << "<!-- Map saved by designer " << ctime(&now) << " -->" << endl;
    m_floorMaps[0]->Pickle(outputFile);
    // m_floorMap[0]->Save(fileStream);
}

const GLPoint
GameFloorDesigner::TranslateWindowToMap(const GLPoint& inPoint)
{
    COREASSERT(m_currentMap < m_floorMaps.size());
    COREASSERT(m_currentMap < m_xPos.size());
    COREASSERT(m_currentMap < m_yPos.size());
    GLPoint outPoint;
    outPoint.x = (S32)(0.5 + (inPoint.x+m_xPos[m_currentMap]-m_width/2) / m_floorMaps[m_currentMap]->XStep());
    outPoint.y = (S32)(0.5 + (inPoint.y+m_yPos[m_currentMap]-m_height/2) / m_floorMaps[m_currentMap]->YStep());
    return outPoint;
}
