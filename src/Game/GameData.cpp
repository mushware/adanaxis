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
 * $Id: GameData.cpp,v 1.14 2002/08/20 11:43:25 southa Exp $
 * $Log: GameData.cpp,v $
 * Revision 1.14  2002/08/20 11:43:25  southa
 * GameRewards added
 *
 * Revision 1.13  2002/08/18 20:44:34  southa
 * Initial chequepoint work
 *
 * Revision 1.12  2002/08/10 12:34:48  southa
 * Added current dialogues
 *
 * Revision 1.11  2002/08/09 17:09:04  southa
 * GameDialogue added
 *
 * Revision 1.10  2002/08/07 13:36:49  southa
 * Conditioned source
 *
 * Revision 1.9  2002/07/18 11:40:35  southa
 * Overplotting and movement
 *
 * Revision 1.8  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.7  2002/06/27 12:36:06  southa
 * Build process fixes
 *
 * Revision 1.6  2002/06/05 15:53:26  southa
 * Player and keyboard control
 *
 * Revision 1.5  2002/06/05 12:28:05  southa
 * Map rendered using traits
 *
 * Revision 1.4  2002/06/04 20:27:36  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
 * Revision 1.3  2002/06/04 14:12:25  southa
 * Traits loader first stage
 *
 * Revision 1.2  2002/05/30 16:21:53  southa
 * Pickleable GameContract
 *
 * Revision 1.1  2002/05/30 14:41:12  southa
 * GameData and loadtilemap command
 *
 */

#include "GameData.h"
#include "GameTileMap.h"
#include "GameFloorMap.h"
#include "GameContract.h"
#include "GameTraits.h"
#include "GameController.h"
#include "GamePiece.h"
#include "GameDialogue.h"
#include "GameView.h"
#include "GameTimer.h"
#include "GameType.h"
#include "GameRewards.h"

GameData *GameData::m_instance=NULL;

GameData::GameData():
    m_timer(NULL),
    m_gameType(NULL)
{
}

GameData::~GameData()
{
    for (map<string, GameTileMap *>::iterator p = m_tilemaps.begin();
         p != m_tilemaps.end(); ++p)
    {
        delete p->second;
    }
    for (map<string, GameFloorMap *>::iterator p = m_floormaps.begin();
         p != m_floormaps.end(); ++p)
    {
        delete p->second;
    }
    for (map<string, GameContract *>::iterator p = m_contracts.begin();
         p != m_contracts.end(); ++p)
    {
        delete p->second;
    }
    for (map<string, GameTraits *>::iterator p = m_traits.begin();
         p != m_traits.end(); ++p)
    {
        delete p->second;
    }
    for (map<string, GameController *>::iterator p = m_controllers.begin();
         p != m_controllers.end(); ++p)
    {
        delete p->second;
    }
    for (map<string, GamePiece *>::iterator p = m_pieces.begin();
         p != m_pieces.end(); ++p)
    {
        delete p->second;
    }
    for (map<string, GameDialogue *>::iterator p = m_dialogues.begin();
         p != m_dialogues.end(); ++p)
    {
        delete p->second;
    }
    for (map<string, GameView *>::iterator p = m_views.begin();
         p != m_views.end(); ++p)
    {
        delete p->second;
    }
    if (m_timer != NULL)
    {
        delete m_timer;
    }
    if (m_gameType != NULL)
    {
        delete m_gameType;
    }
    if (m_gameRewards != NULL)
    {
        delete m_gameRewards;
    }
    for (map<string, GameDialogue *>::iterator p = m_currentDialogues.begin();
         p != m_currentDialogues.end(); ++p)
    {
        delete p->second;
    }
}

GameTileMap *
GameData::TileMapGetOrCreate(const string& inName)
{
    map<string, GameTileMap *>::const_iterator p = m_tilemaps.find(inName);
    if (p == m_tilemaps.end())
    {
        GameTileMap *pTileMap(new GameTileMap);
        m_tilemaps[inName]=pTileMap;
        return pTileMap;
    }
    else
    {
        return p->second;
    }
}

GameTileMap *
GameData::TileMapGet(const string& inName) const
{
    map<string, GameTileMap *>::const_iterator p = m_tilemaps.find(inName);
    if (p == m_tilemaps.end())
    {
        throw(GameDataNotPresent("Access to non-existent tilemap '"+inName+"'"));
    }
    return p->second;
}

GameFloorMap *
GameData::FloorMapGetOrCreate(const string& inName)
{
    map<string, GameFloorMap *>::const_iterator p = m_floormaps.find(inName);
    if (p == m_floormaps.end())
    {
        GameFloorMap *pFloorMap(new GameFloorMap);
        m_floormaps[inName]=pFloorMap;
        return pFloorMap;
    }
    else
    {
        return p->second;
    }
}

GameFloorMap *
GameData::FloorMapGet(const string& inName) const
{
    map<string, GameFloorMap *>::const_iterator p = m_floormaps.find(inName);
    if (p == m_floormaps.end())
    {
        throw(GameDataNotPresent("Access to non-existent floormap '"+inName+"'"));
    }
    return p->second;
}

GameContract *
GameData::ContractGetOrCreate(const string& inName)
{
    map<string, GameContract *>::const_iterator p = m_contracts.find(inName);
    if (p == m_contracts.end())
    {
        GameContract *pContract(new GameContract);
        m_contracts[inName]=pContract;
        return pContract;
    }
    else
    {
        return p->second;
    }
}

GameContract *
GameData::ContractGet(const string& inName) const
{
    map<string, GameContract *>::const_iterator p = m_contracts.find(inName);
    if (p == m_contracts.end())
    {
        throw(GameDataNotPresent("Access to non-existent contract '"+inName+"'"));
    }
    return p->second;
}

GameTraits *
GameData::TraitsDeleteAndCreate(const string& inName, GameTraits *inTraits)
{
    map<string, GameTraits *>::iterator p = m_traits.find(inName);
    if (p != m_traits.end())
    {
        delete p->second;
        p->second=inTraits;
    }
    else
    {
        m_traits[inName]=inTraits;
    }
    return inTraits;
}

GameTraits *
GameData::TraitsGet(const string& inName) const
{
    map<string, GameTraits *>::const_iterator p = m_traits.find(inName);
    if (p == m_traits.end())
    {
        throw(GameDataNotPresent("Access to non-existent trait '"+inName+"'"));
    }
    return p->second;
}

GameController *
GameData::ControllerGetOrCreate(const string& inName)
{
    map<string, GameController *>::const_iterator p = m_controllers.find(inName);
    if (p == m_controllers.end())
    {
        GameController *pController(new GameController);
        m_controllers[inName]=pController;
        return pController;
    }
    else
    {
        return p->second;
    }
}

GameController *
GameData::ControllerGet(const string& inName) const
{
    map<string, GameController *>::const_iterator p = m_controllers.find(inName);
    if (p == m_controllers.end())
    {
        throw(GameDataNotPresent("Access to non-existent controller '"+inName+"'"));
    }
    return p->second;
}

GamePiece *
GameData::PieceDeleteAndCreate(const string& inName, GamePiece *inPiece)
{
    map<string, GamePiece *>::iterator p = m_pieces.find(inName);
    if (p != m_pieces.end())
    {
        delete p->second;
        p->second=inPiece;
    }
    else
    {
        m_pieces[inName]=inPiece;
    }
    return inPiece;
}

GamePiece *
GameData::PieceGet(const string& inName) const
{
    map<string, GamePiece *>::const_iterator p = m_pieces.find(inName);
    if (p == m_pieces.end())
    {
        throw(GameDataNotPresent("Access to non-existent piece '"+inName+"'"));
    }
    return p->second;
}

GameDialogue *
GameData::DialogueDeleteAndCreate(const string& inName, GameDialogue *inDialogue)
{
    map<string, GameDialogue *>::iterator p = m_dialogues.find(inName);
    if (p != m_dialogues.end())
    {
        delete p->second;
        p->second=inDialogue;
    }
    else
    {
        m_dialogues[inName]=inDialogue;
    }
    return inDialogue;
}

GameDialogue *
GameData::DialogueGet(const string& inName) const
{
    map<string, GameDialogue *>::const_iterator p = m_dialogues.find(inName);
    if (p == m_dialogues.end())
    {
        throw(GameDataNotPresent("Access to non-existent dialogue '"+inName+"'"));
    }
    return p->second;
}

GameView *
GameData::ViewGetOrCreate(const string& inName)
{
    map<string, GameView *>::const_iterator p = m_views.find(inName);
    if (p == m_views.end())
    {
        GameView *pView(new GameView);
        m_views[inName]=pView;
        return pView;
    }
    else
    {
        return p->second;
    }
}

GameView *
GameData::ViewGet(const string& inName) const
{
    map<string, GameView *>::const_iterator p = m_views.find(inName);
    if (p == m_views.end())
    {
        throw(GameDataNotPresent("Access to non-existent view '"+inName+"'"));
    }
    return p->second;
}

GameView *
GameData::CurrentViewGet(void) const
{
    // Just return the first one for now
    for (map<string, GameView *>::const_iterator p = m_views.begin();
         p != m_views.end(); ++p)
    {
        return p->second;
    }
    throw(GameDataNotPresent("Access to non-existent current view"));
}

GameTimer&
GameData::TimerGet(void)
{
    if (m_timer == NULL)
    {
        m_timer = new GameTimer;
    }
    return *m_timer;
}

GameType&
GameData::TypeGet(void) const
{
    if (m_gameType == NULL)
    {
        throw(GameDataNotPresent("Access to non-existent current type"));
    }
    return *m_gameType;
}

void
GameData::TypeSet(GameType *inType)
{
    if (m_gameType == NULL)
    {
        delete m_gameType;
    }
    m_gameType=inType;
}

GameRewards&
GameData::RewardsGet(void) const
{
    if (m_gameRewards == NULL)
    {
        throw(GameDataNotPresent("Access to non-existent rewards"));
    }
    return *m_gameRewards;
}

void
GameData::RewardsSet(GameRewards *inRewards)
{
    if (m_gameRewards == NULL)
    {
        delete m_gameRewards;
    }
    m_gameRewards=inRewards;
}

GameDialogue *
GameData::CurrentDialogueAdd(const string& inName, const GameDialogue& inDialogue)
{
    GameDialogue *newDialogue = new GameDialogue(inDialogue);
    map<string, GameDialogue *>::iterator p = m_currentDialogues.find(inName);
    if (p == m_currentDialogues.end())
    {
        m_currentDialogues[inName] = newDialogue;
    }
    else
    {
        delete p->second;
        p->second = newDialogue;
    }
    return newDialogue;
}

void
GameData::CurrentDialogueDelete(const string& inName)
{
    map<string, GameDialogue *>::iterator p = m_currentDialogues.find(inName);
    if (p == m_currentDialogues.end())
    {
        throw(LogicFail("Attempt to delete non-existent current dialogue '"+inName+"'"));
    }
    else
    {
        delete p->second;
        m_currentDialogues.erase(p);
    }    
}

void
GameData::CurrentDialoguesClear(void)
{
    for (GameData::DialogueMapIterator p = m_currentDialogues.begin(); p != m_currentDialogues.end(); ++p)
    {
        p->second->ExpireNow();
        delete p->second;
    }
    m_currentDialogues.clear();
}

void
GameData::DumpAll(ostream& inOut) const
{
    inOut << "<chunk type=\"tilemap\">" << endl;
    for (map<string, GameTileMap *>::const_iterator p = m_tilemaps.begin();
         p != m_tilemaps.end(); ++p)
    {
        inOut << "  <tilemap name=\"" << p->first << "\">" << endl;
        p->second->Pickle(inOut, "    ");
        inOut << "  </tilemap>" << endl;
    }
    inOut << "</chunk>" << endl;
    inOut << "<chunk type=\"floormap\">" << endl;
    for (map<string, GameFloorMap *>::const_iterator p = m_floormaps.begin();
         p != m_floormaps.end(); ++p)
    {
        inOut << "  <floormap name=\"" << p->first << "\">" << endl;
        p->second->Pickle(inOut, "    ");
        inOut << "  </floormap>" << endl;
    }
    inOut << "</chunk>" << endl;
    inOut << "<chunk type=\"contract\">" << endl;
    for (map<string, GameContract *>::const_iterator p = m_contracts.begin();
         p != m_contracts.end(); ++p)
    {
        inOut << "  <contract name=\"" << p->first << "\">" << endl;
        p->second->Pickle(inOut, "    ");
        inOut << "  </contract>" << endl;
    }
    inOut << "</chunk>" << endl;
    inOut << "<chunk type=\"traits\">" << endl;
    for (map<string, GameTraits *>::const_iterator p = m_traits.begin();
         p != m_traits.end(); ++p)
    {
        inOut << "  <traits type=\"" << p->second->TypeNameGet() << "\" name=\"" << p->first << "\">" << endl;
        p->second->Pickle(inOut, "    ");
        inOut << "  </traits>" << endl;
    }
    inOut << "</chunk>" << endl;
    inOut << "<!-- Incomplete -->" << endl;

}    
