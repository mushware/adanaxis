#ifndef GAMEDATA_H
#define GAMEDATA_H
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
 * $Id: GameData.h,v 1.27 2003/02/05 16:19:45 southa Exp $
 * $Log: GameData.h,v $
 * Revision 1.27  2003/02/05 16:19:45  southa
 * Build fixes
 *
 * Revision 1.26  2003/01/20 10:45:25  southa
 * Singleton tidying
 *
 * Revision 1.25  2003/01/18 13:33:57  southa
 * Created MushcoreSingleton
 *
 * Revision 1.24  2003/01/11 13:03:13  southa
 * Use Mushcore header
 *
 * Revision 1.23  2003/01/09 14:57:01  southa
 * Created Mushcore
 *
 * Revision 1.22  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.21  2002/12/20 13:17:38  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.20  2002/12/05 13:20:12  southa
 * Client link handling
 *
 * Revision 1.19  2002/12/03 20:28:16  southa
 * Network, player and control work
 *
 * Revision 1.18  2002/11/18 18:55:58  southa
 * Game resume and quit
 *
 * Revision 1.17  2002/11/17 13:38:30  southa
 * Game selection
 *
 * Revision 1.16  2002/10/22 20:42:03  southa
 * Source conditioning
 *
 * Revision 1.15  2002/08/27 08:56:23  southa
 * Source conditioning
 *
 * Revision 1.14  2002/08/22 10:11:11  southa
 * Save records, spacebar dialogues
 *
 * Revision 1.13  2002/08/20 11:43:25  southa
 * GameRewards added
 *
 * Revision 1.12  2002/08/18 20:44:34  southa
 * Initial chequepoint work
 *
 * Revision 1.11  2002/08/10 12:34:48  southa
 * Added current dialogues
 *
 * Revision 1.10  2002/08/09 17:09:04  southa
 * GameDialogue added
 *
 * Revision 1.9  2002/08/07 13:36:49  southa
 * Conditioned source
 *
 * Revision 1.8  2002/07/18 11:40:35  southa
 * Overplotting and movement
 *
 * Revision 1.7  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.6  2002/06/27 12:36:06  southa
 * Build process fixes
 *
 * Revision 1.5  2002/06/05 15:53:26  southa
 * Player and keyboard control
 *
 * Revision 1.4  2002/06/04 20:27:37  southa
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

#include "Mushcore.h"

class GameTileMap;
class GameFloorMap;
class GameContract;
class GameTraits;
class GameController;
class GamePiece;
class GamePiecePlayer;
class GameDialogue;
class GameView;
class GameTimer;
class GameType;
class GameRewards;

class GameData
{
public:
    typedef std::map<std::string, GameDialogue *> DialogueMap;
    typedef std::map<std::string, GameDialogue *>::iterator DialogueMapIterator;
    typedef std::map<std::string, GameDialogue *>::const_iterator DialogueMapConstIterator;
    ~GameData();
    static GameData& Sgl(void) {return *((m_instance==NULL)?m_instance=new GameData:m_instance);}

    void Clear(void);
    
    GameTileMap *TileMapGetOrCreate(const std::string& inName);
    GameTileMap *TileMapGet(const std::string& inName) const;
    GameFloorMap *FloorMapGetOrCreate(const std::string& inName);
    GameFloorMap *FloorMapGet(const std::string& inName) const;
    GameContract *ContractGetOrCreate(const std::string& inName);
    GameContract *ContractGet(const std::string& inName) const;
    bool ContractExists(const std::string& inName) const;
    void ContractsClear(void);
    GameTraits *TraitsDeleteAndCreate(const std::string& inName, GameTraits *inTraits);
    GameTraits *TraitsGet(const std::string& inName) const;
    GameController *ControllerGetOrCreate(const std::string& inName);
    GameController *ControllerGet(const std::string& inName) const;
    const GamePiece *TemplateDeleteAndCreate(const std::string& inName, GamePiece *inPiece);
    const GamePiece *TemplateGet(const std::string& inName) const;
    GamePiece *PieceDeleteAndCreate(const std::string& inName, GamePiece *inPiece);
    GamePiece *PieceGet(const std::string& inName) const;
    GameDialogue *DialogueDeleteAndCreate(const std::string& inName, GameDialogue *inDialogue);
    GameDialogue *DialogueGet(const std::string& inName) const;
    const DialogueMap& DialogueMapGet(void) const { return m_dialogues; }
    GameView *ViewGetOrCreate(const std::string& inName);
    GameView *ViewGet(const std::string& inName) const;
    GameView *CurrentViewGet(void) const;

    MushcoreData<GamePiecePlayer>& PlayerGet(void) { return m_playerData; }
    
    GameTimer& TimerGet(void);
    GameType& TypeGet(void) const;
    void TypeSet(GameType *inType);
    GameRewards& RewardsGet(void) const;
    void RewardsSet(GameRewards *inRewards);

    GameDialogue *CurrentDialogueAdd(const std::string& inName, const GameDialogue& inDialogue);
    void CurrentDialogueDelete(const std::string& inName);
    const DialogueMap& CurrentDialogueMapGet(void) const { return m_currentDialogues; }
    void CurrentDialoguesClear(void);


    
    void DumpAll(std::ostream& inOut) const;

private:
    GameData();
    std::map<std::string, GameTileMap *> m_tilemaps;
    std::map<std::string, GameFloorMap *> m_floormaps;
    std::map<std::string, GameContract *> m_contracts;
    std::map<std::string, GameTraits *> m_traits;
    std::map<std::string, GameController *> m_controllers;
    DialogueMap m_dialogues;
    std::map<std::string, GamePiece *> m_templates;
    std::map<std::string, GamePiece *> m_pieces;
    std::map<std::string, GameView *> m_views;

    MushcoreData<GamePiecePlayer> m_playerData;
    
    GameTimer *m_timer;
    GameType *m_gameType;
    GameRewards *m_gameRewards;
    
    DialogueMap m_currentDialogues;

    static GameData *m_instance;
};

#endif
