/*
 * $Id$
 * $Log$
 */

#include "GameFloorDesigner.h"

#include "mushGL.h"
#include "GameData.h"
#include "GameFloorMap.h"
#include "GameController.h"

void
GameFloorDesigner::Init(void)
{
    m_controllerName="controller1";
    m_tileMap=GameData::Instance().TileMapGet("tiles");
    m_floorMaps.push_back(GameData::Instance().FloorMapGet("floor"));
    COREASSERT(m_tileMap != NULL);
    COREASSERT(m_floorMaps[0] != NULL);
    GameData::Instance().ControllerGetOrCreate("controller1");
    // GameData::Instance().DumpAll(cout);
}

void
GameFloorDesigner::Display(void)
{
    COREASSERT(m_floorMaps.size() > 0);
    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    GLUtils::IdentityPrologue();
    GLUtils::OrthoLookAt(0, 0, 0);
    m_floorMaps[0]->Render(*m_tileMap, GLRectangle(5,5,7,9));
    GLUtils::IdentityEpilogue();
    GLUtils::DisplayEpilogue();
}

void
GameFloorDesigner::Move(void)
{
    if (m_controller == NULL)
    {
        m_controller=GameData::Instance().ControllerGet(m_controllerName);
    }
    GameControllerState controlState;
    m_controller->StateGet(controlState);
}
