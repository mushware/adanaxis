/*
 * $Id: GameFloorDesigner.cpp,v 1.2 2002/07/02 18:36:56 southa Exp $
 * $Log: GameFloorDesigner.cpp,v $
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
#include "GameFloorMap.h"
#include "GameController.h"

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
    COREASSERT(m_tileMap != NULL);
    COREASSERT(m_floorMaps[0] != NULL);
    GameData::Instance().ControllerGetOrCreate(m_controllerName);
    m_width=glHandler.WidthGet();
    m_height=glHandler.HeightGet();
    m_xPos=glHandler.WidthGet()/2;
    m_yPos=glHandler.HeightGet()/2;
    m_highlight=GLRectangle();
    m_highlightMap=0;
    m_currentMap=0;
    m_primaryButtonState=false;
    m_secondaryButtonState=false;
}

void
GameFloorDesigner::Display(void)
{
    COREASSERT(m_floorMaps.size() > 0);
    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    GLUtils::IdentityPrologue();
    GLUtils::OrthoLookAt(m_xPos, m_yPos, 0);
    m_floorMaps[0]->Render(*m_tileMap, m_highlight);
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

    bool primaryState(glHandler.KeyStateGet(GLKeys::kKeyMouse1));
    bool secondaryState(glHandler.KeyStateGet(GLKeys::kKeyMouse3));
    bool tertiaryState(glHandler.KeyStateGet(GLKeys::kKeyMouse2));

    if (m_secondaryButtonState != secondaryState)
    {
        if (secondaryState)
        {
            m_downPoint=GLPoint(controlState.mouseX, controlState.mouseY);
        }
    }
    m_primaryButtonState = primaryState;
    m_secondaryButtonState = secondaryState;

    if (secondaryState)
    {
        GLPoint start(m_downPoint);
        GLPoint end(controlState.mouseX, controlState.mouseY);
        m_highlight=GLRectangle(TranslateWindowToMap(start), TranslateWindowToMap(end));
        m_highlight.FixUp();
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
        deltaY=controlState.mouseYDelta;
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
    m_xPos += deltaX;
    m_yPos += deltaY;
}

const GLPoint
GameFloorDesigner::TranslateWindowToMap(const GLPoint& inPoint)
{
    COREASSERT(m_floorMaps.size() > m_currentMap);
    GLPoint outPoint;
    outPoint.x = (inPoint.x+m_xPos-m_width/2)/m_floorMaps[m_currentMap]->XStep();
    outPoint.y = (m_height/2-inPoint.y+m_yPos)/m_floorMaps[m_currentMap]->YStep();
    return outPoint;
}
