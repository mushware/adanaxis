//%includeGuardStart {
#ifndef INFERNALDATA_H
#define INFERNALDATA_H
//%includeGuardStart } KkgAudId1l7zpq/jOAmxHA
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalData.h
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
//%Header } Z0YYStWHs9b1CqEa6gO+Hg
/*
 * $Id: InfernalData.h,v 1.10 2006/06/01 15:39:01 southa Exp $
 * $Log: InfernalData.h,v $
 * Revision 1.10  2006/06/01 15:39:01  southa
 * DrawArray verification and fixes
 *
 * Revision 1.9  2005/05/19 13:02:04  southa
 * Mac release work
 *
 * Revision 1.8  2005/02/03 21:02:54  southa
 * Build fixes
 *
 * Revision 1.7  2004/01/10 20:29:34  southa
 * Form and rendering work
 *
 * Revision 1.6  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.5  2004/01/02 21:13:08  southa
 * Source conditioning
 *
 * Revision 1.4  2003/10/07 22:40:06  southa
 * Created MeshMover
 *
 * Revision 1.3  2003/10/04 15:32:10  southa
 * Module split
 *
 * Revision 1.1  2003/10/04 12:23:04  southa
 * File renaming
 *
 * Revision 1.30  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.29  2003/08/21 23:08:41  southa
 * Fixed file headers
 *
 * Revision 1.28  2003/02/05 18:49:51  southa
 * Build fixes
 *
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
 * InfernalDialogue added
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
 * Pickleable InfernalContract
 *
 * Revision 1.1  2002/05/30 14:41:12  southa
 * InfernalData and loadtilemap command
 *
 */

#include "mushMushcore.h"

#include "mushPie.h"

class InfernalTileMap;
class InfernalFloorMap;
class InfernalContract;
class InfernalTraits;
class GameController;
class InfernalPiece;
class InfernalPiecePlayer;
class InfernalDialogue;
class InfernalView;
class GameTimer;
class GameRewards;
class MushPiePieceMobile;

class InfernalData
{
public:
    typedef std::map<std::string, InfernalDialogue *> DialogueMap;
    typedef std::map<std::string, InfernalDialogue *>::iterator DialogueMapIterator;
    typedef std::map<std::string, InfernalDialogue *>::const_iterator DialogueMapConstIterator;
    
    typedef MushcoreData<MushPiePieceMobile, Mushware::U32> tProjectileData;
    typedef MushcoreData<MushPiePieceMobile, Mushware::U32>::tMapIterator tProjectileDataIterator;
    typedef MushcoreData<MushPiePieceMobile, Mushware::U32>::tMapConstIterator tProjectileDataConstIterator;
    
    ~InfernalData();
    static InfernalData& Sgl(void) {return *((m_instance==NULL)?m_instance=new InfernalData:m_instance);}

    void Clear(void);
    
    InfernalTileMap *TileMapGetOrCreate(const std::string& inName);
    InfernalTileMap *TileMapGet(const std::string& inName) const;
    InfernalFloorMap *FloorMapGetOrCreate(const std::string& inName);
    InfernalFloorMap *FloorMapGet(const std::string& inName) const;
    InfernalContract *ContractGetOrCreate(const std::string& inName);
    InfernalContract *ContractGet(const std::string& inName) const;
    bool ContractExists(const std::string& inName) const;
    void ContractsClear(void);
    InfernalTraits *TraitsDeleteAndCreate(const std::string& inName, InfernalTraits *inTraits);
    InfernalTraits *TraitsGet(const std::string& inName) const;
    GameController *ControllerGetOrCreate(const std::string& inName);
    GameController *ControllerGet(const std::string& inName) const;
    const InfernalPiece *TemplateDeleteAndCreate(const std::string& inName, InfernalPiece *inPiece);
    const InfernalPiece *TemplateGet(const std::string& inName) const;
    InfernalPiece *PieceDeleteAndCreate(const std::string& inName, InfernalPiece *inPiece);
    InfernalPiece *PieceGet(const std::string& inName) const;
    InfernalDialogue *DialogueDeleteAndCreate(const std::string& inName, InfernalDialogue *inDialogue);
    InfernalDialogue *DialogueGet(const std::string& inName) const;
    const DialogueMap& DialogueMapGet(void) const { return m_dialogues; }
    InfernalView *ViewGetOrCreate(const std::string& inName);
    InfernalView *ViewGet(const std::string& inName) const;
    InfernalView *CurrentViewGet(void) const;

    MushcoreData<InfernalPiecePlayer>& PlayerGet(void) { return m_playerData; }
    
    GameTimer& TimerGet(void);
    GameRewards& RewardsGet(void) const;
    void RewardsSet(GameRewards *inRewards);

    InfernalDialogue *CurrentDialogueAdd(const std::string& inName, const InfernalDialogue& inDialogue);
    void CurrentDialogueDelete(const std::string& inName);
    const DialogueMap& CurrentDialogueMapGet(void) const { return m_currentDialogues; }
    void CurrentDialoguesClear(void);

    tProjectileData& ProjectileDataGet(void) { return m_projectileData; }
    
    void DumpAll(std::ostream& inOut) const;

private:
    InfernalData();
    std::map<std::string, InfernalTileMap *> m_tilemaps;
    std::map<std::string, InfernalFloorMap *> m_floormaps;
    std::map<std::string, InfernalContract *> m_contracts;
    std::map<std::string, InfernalTraits *> m_traits;
    std::map<std::string, GameController *> m_controllers;
    DialogueMap m_dialogues;
    std::map<std::string, InfernalPiece *> m_templates;
    std::map<std::string, InfernalPiece *> m_pieces;
    std::map<std::string, InfernalView *> m_views;

    MushcoreData<InfernalPiecePlayer> m_playerData;
    tProjectileData m_projectileData;
    GameTimer *m_timer;
    GameRewards *m_gameRewards;
    
    DialogueMap m_currentDialogues;

    static InfernalData *m_instance;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
