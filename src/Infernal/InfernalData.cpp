//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalData.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } KDC8pImwjeHS5CqhZ3lPPQ
/*
 * $Id: InfernalData.cpp,v 1.1 2003/10/04 12:23:04 southa Exp $
 * $Log: InfernalData.cpp,v $
 * Revision 1.1  2003/10/04 12:23:04  southa
 * File renaming
 *
 * Revision 1.31  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.30  2003/08/21 23:08:41  southa
 * Fixed file headers
 *
 * Revision 1.29  2003/02/05 18:49:51  southa
 * Build fixes
 *
 * Revision 1.28  2003/02/05 17:06:36  southa
 * Build fixes
 *
 * Revision 1.27  2003/01/18 13:33:56  southa
 * Created MushcoreSingleton
 *
 * Revision 1.26  2003/01/13 14:31:57  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.25  2003/01/12 17:32:53  southa
 * Mushcore work
 *
 * Revision 1.24  2003/01/09 14:57:00  southa
 * Created Mushcore
 *
 * Revision 1.23  2002/12/29 20:59:54  southa
 * More build fixes
 *
 * Revision 1.22  2002/12/20 13:17:38  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.21  2002/12/09 23:59:57  southa
 * Network control
 *
 * Revision 1.20  2002/12/03 20:28:16  southa
 * Network, player and control work
 *
 * Revision 1.19  2002/11/18 18:55:57  southa
 * Game resume and quit
 *
 * Revision 1.18  2002/11/17 13:38:30  southa
 * Game selection
 *
 * Revision 1.17  2002/10/22 20:42:03  southa
 * Source conditioning
 *
 * Revision 1.16  2002/08/27 08:56:23  southa
 * Source conditioning
 *
 * Revision 1.15  2002/08/22 10:11:11  southa
 * Save records, spacebar dialogues
 *
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
 * Pickleable InfernalContract
 *
 * Revision 1.1  2002/05/30 14:41:12  southa
 * InfernalData and loadtilemap command
 *
 */

#include "InfernalData.h"
#include "InfernalContract.h"
#include "GameController.h"
#include "GameDialogue.h"
#include "InfernalFloorMap.h"
#include "InfernalPiece.h"
#include "InfernalPiecePlayer.h"
#include "GameRewards.h"
#include "GameSTL.h"
#include "InfernalTileMap.h"
#include "InfernalTimer.h"
#include "GameTraits.h"
#include "GameType.h"
#include "InfernalView.h"

using namespace Mushware;
using namespace std;

InfernalData *InfernalData::m_instance=NULL;

InfernalData::InfernalData():
    m_timer(NULL),
    m_gameType(NULL),
    m_gameRewards(NULL)
{
}

InfernalData::~InfernalData()
{
    Clear();
}

void
InfernalData::Clear(void)
{
    for (map<std::string, InfernalTileMap *>::iterator p = m_tilemaps.begin();
         p != m_tilemaps.end(); ++p)
    {
        delete p->second;
    }
    m_tilemaps.clear();
    
    for (map<std::string, InfernalFloorMap *>::iterator p = m_floormaps.begin();
         p != m_floormaps.end(); ++p)
    {
        delete p->second;
    }
    m_floormaps.clear();

    for (map<std::string, InfernalContract *>::iterator p = m_contracts.begin();
         p != m_contracts.end(); ++p)
    {
        delete p->second;
    }
    m_contracts.clear();

    for (map<std::string, GameTraits *>::iterator p = m_traits.begin();
         p != m_traits.end(); ++p)
    {
        delete p->second;
    }
    m_traits.clear();

    for (map<std::string, GameController *>::iterator p = m_controllers.begin();
         p != m_controllers.end(); ++p)
    {
        delete p->second;
    }
    m_controllers.clear();

    for (map<std::string, InfernalPiece *>::iterator p = m_templates.begin();
         p != m_templates.end(); ++p)
    {
        delete p->second;
    }
    m_templates.clear();

    for (map<std::string, GameDialogue *>::iterator p = m_dialogues.begin();
         p != m_dialogues.end(); ++p)
    {
        delete p->second;
    }
    m_dialogues.clear();

    for (map<std::string, InfernalView *>::iterator p = m_views.begin();
         p != m_views.end(); ++p)
    {
        delete p->second;
    }
    m_views.clear();

    if (m_timer != NULL)
    {
        delete m_timer;
        m_timer=NULL;
    }
    if (m_gameType != NULL)
    {
        delete m_gameType;
        m_gameType=NULL;
    }
    if (m_gameRewards != NULL)
    {
        delete m_gameRewards;
        m_gameRewards=NULL;
    }
    for (map<std::string, GameDialogue *>::iterator p = m_currentDialogues.begin();
         p != m_currentDialogues.end(); ++p)
    {
        delete p->second;
    }
    m_currentDialogues.clear();

    m_playerData.Clear();
}

InfernalTileMap *
InfernalData::TileMapGetOrCreate(const string& inName)
{
    map<std::string, InfernalTileMap *>::const_iterator p = m_tilemaps.find(inName);
    if (p == m_tilemaps.end())
    {
        InfernalTileMap *pTileMap(new InfernalTileMap);
        m_tilemaps[inName]=pTileMap;
        return pTileMap;
    }
    else
    {
        return p->second;
    }
}

InfernalTileMap *
InfernalData::TileMapGet(const string& inName) const
{
    map<std::string, InfernalTileMap *>::const_iterator p = m_tilemaps.find(inName);
    if (p == m_tilemaps.end())
    {
        throw(MushcoreDataFail("Access to non-existent tilemap '"+inName+"'"));
    }
    return p->second;
}

InfernalFloorMap *
InfernalData::FloorMapGetOrCreate(const string& inName)
{
    map<std::string, InfernalFloorMap *>::const_iterator p = m_floormaps.find(inName);
    if (p == m_floormaps.end())
    {
        InfernalFloorMap *pFloorMap(new InfernalFloorMap);
        m_floormaps[inName]=pFloorMap;
        return pFloorMap;
    }
    else
    {
        return p->second;
    }
}

InfernalFloorMap *
InfernalData::FloorMapGet(const string& inName) const
{
    map<std::string, InfernalFloorMap *>::const_iterator p = m_floormaps.find(inName);
    if (p == m_floormaps.end())
    {
        throw(MushcoreDataFail("Access to non-existent floormap '"+inName+"'"));
    }
    return p->second;
}

InfernalContract *
InfernalData::ContractGetOrCreate(const string& inName)
{
    map<std::string, InfernalContract *>::const_iterator p = m_contracts.find(inName);
    if (p == m_contracts.end())
    {
        InfernalContract *pContract(new InfernalContract);
        m_contracts[inName]=pContract;
        return pContract;
    }
    else
    {
        return p->second;
    }
}

InfernalContract *
InfernalData::ContractGet(const string& inName) const
{
    map<std::string, InfernalContract *>::const_iterator p = m_contracts.find(inName);
    if (p == m_contracts.end())
    {
        throw(MushcoreDataFail("Access to non-existent contract '"+inName+"'"));
    }
    return p->second;
}

bool
InfernalData::ContractExists(const string& inName) const
{
    return (m_contracts.find(inName) != m_contracts.end());
}

void
InfernalData::ContractsClear(void)
{
    for (map<std::string, InfernalContract *>::iterator p = m_contracts.begin();
         p != m_contracts.end(); ++p)
    {
        delete p->second;
        p->second=NULL;
    }
    m_contracts.clear();
}

GameTraits *
InfernalData::TraitsDeleteAndCreate(const string& inName, GameTraits *inTraits)
{
    map<std::string, GameTraits *>::iterator p = m_traits.find(inName);
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
InfernalData::TraitsGet(const string& inName) const
{
    map<std::string, GameTraits *>::const_iterator p = m_traits.find(inName);
    if (p == m_traits.end())
    {
        throw(MushcoreDataFail("Access to non-existent trait '"+inName+"'"));
    }
    return p->second;
}

GameController *
InfernalData::ControllerGetOrCreate(const string& inName)
{
    map<std::string, GameController *>::const_iterator p = m_controllers.find(inName);
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
InfernalData::ControllerGet(const string& inName) const
{
    map<std::string, GameController *>::const_iterator p = m_controllers.find(inName);
    if (p == m_controllers.end())
    {
        throw(MushcoreDataFail("Access to non-existent controller '"+inName+"'"));
    }
    return p->second;
}

const InfernalPiece *
InfernalData::TemplateDeleteAndCreate(const string& inName, InfernalPiece *inPiece)
{
    map<std::string, InfernalPiece *>::iterator p = m_templates.find(inName);
    if (p != m_templates.end())
    {
        delete p->second;
        p->second=inPiece;
    }
    else
    {
        m_templates[inName]=inPiece;
    }
    return inPiece;
}

const InfernalPiece *
InfernalData::TemplateGet(const string& inName) const
{
    map<std::string, InfernalPiece *>::const_iterator p = m_templates.find(inName);
    if (p == m_templates.end())
    {
        throw(MushcoreDataFail("Access to non-existent template '"+inName+"'"));
    }
    return p->second;
}

GameDialogue *
InfernalData::DialogueDeleteAndCreate(const string& inName, GameDialogue *inDialogue)
{
    map<std::string, GameDialogue *>::iterator p = m_dialogues.find(inName);
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
InfernalData::DialogueGet(const string& inName) const
{
    map<std::string, GameDialogue *>::const_iterator p = m_dialogues.find(inName);
    if (p == m_dialogues.end())
    {
        throw(MushcoreDataFail("Access to non-existent dialogue '"+inName+"'"));
    }
    return p->second;
}

InfernalView *
InfernalData::ViewGetOrCreate(const string& inName)
{
    map<std::string, InfernalView *>::const_iterator p = m_views.find(inName);
    if (p == m_views.end())
    {
        InfernalView *pView(new InfernalView);
        m_views[inName]=pView;
        return pView;
    }
    else
    {
        return p->second;
    }
}

InfernalView *
InfernalData::ViewGet(const string& inName) const
{
    map<std::string, InfernalView *>::const_iterator p = m_views.find(inName);
    if (p == m_views.end())
    {
        throw(MushcoreDataFail("Access to non-existent view '"+inName+"'"));
    }
    return p->second;
}

InfernalView *
InfernalData::CurrentViewGet(void) const
{
    // Just return the first one for now
    for (map<std::string, InfernalView *>::const_iterator p = m_views.begin();
         p != m_views.end(); ++p)
    {
        return p->second;
    }
    throw(MushcoreDataFail("Access to non-existent current view"));
}

InfernalTimer&
InfernalData::TimerGet(void)
{
    if (m_timer == NULL)
    {
        m_timer = new InfernalTimer;
    }
    return *m_timer;
}

GameType&
InfernalData::TypeGet(void) const
{
    if (m_gameType == NULL)
    {
        throw(MushcoreDataFail("Access to non-existent current type"));
    }
    return *m_gameType;
}

void
InfernalData::TypeSet(GameType *inType)
{
    if (m_gameType == NULL)
    {
        delete m_gameType;
    }
    m_gameType=inType;
}

GameRewards&
InfernalData::RewardsGet(void) const
{
    if (m_gameRewards == NULL)
    {
        throw(MushcoreDataFail("Access to non-existent rewards"));
    }
    return *m_gameRewards;
}

void
InfernalData::RewardsSet(GameRewards *inRewards)
{
    if (m_gameRewards == NULL)
    {
        delete m_gameRewards;
    }
    m_gameRewards=inRewards;
}

GameDialogue *
InfernalData::CurrentDialogueAdd(const string& inName, const GameDialogue& inDialogue)
{
    GameDialogue *newDialogue = new GameDialogue(inDialogue);
    map<std::string, GameDialogue *>::iterator p = m_currentDialogues.find(inName);
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
InfernalData::CurrentDialogueDelete(const string& inName)
{
    map<std::string, GameDialogue *>::iterator p = m_currentDialogues.find(inName);
    if (p == m_currentDialogues.end())
    {
        throw(MushcoreLogicFail("Attempt to delete non-existent current dialogue '"+inName+"'"));
    }
    else
    {
        delete p->second;
        m_currentDialogues.erase(p);
    }    
}

void
InfernalData::CurrentDialoguesClear(void)
{
    for (InfernalData::DialogueMapIterator p = m_currentDialogues.begin(); p != m_currentDialogues.end(); ++p)
    {
        p->second->ExpireNow();
        delete p->second;
    }
    m_currentDialogues.clear();
}

void
InfernalData::DumpAll(ostream& inOut) const
{
    inOut << "<chunk type=\"tilemap\">" << endl;
    for (map<std::string, InfernalTileMap *>::const_iterator p = m_tilemaps.begin();
         p != m_tilemaps.end(); ++p)
    {
        inOut << "  <tilemap name=\"" << p->first << "\">" << endl;
        p->second->Pickle(inOut, "    ");
        inOut << "  </tilemap>" << endl;
    }
    inOut << "</chunk>" << endl;
    inOut << "<chunk type=\"floormap\">" << endl;
    for (map<std::string, InfernalFloorMap *>::const_iterator p = m_floormaps.begin();
         p != m_floormaps.end(); ++p)
    {
        inOut << "  <floormap name=\"" << p->first << "\">" << endl;
        p->second->Pickle(inOut, "    ");
        inOut << "  </floormap>" << endl;
    }
    inOut << "</chunk>" << endl;
    inOut << "<chunk type=\"contract\">" << endl;
    for (map<std::string, InfernalContract *>::const_iterator p = m_contracts.begin();
         p != m_contracts.end(); ++p)
    {
        inOut << "  <contract name=\"" << p->first << "\">" << endl;
        p->second->Pickle(inOut, "    ");
        inOut << "  </contract>" << endl;
    }
    inOut << "</chunk>" << endl;
    inOut << "<chunk type=\"traits\">" << endl;
    for (map<std::string, GameTraits *>::const_iterator p = m_traits.begin();
         p != m_traits.end(); ++p)
    {
        inOut << "  <traits type=\"" << p->second->TypeNameGet() << "\" name=\"" << p->first << "\">" << endl;
        p->second->Pickle(inOut, "    ");
        inOut << "  </traits>" << endl;
    }
    inOut << "</chunk>" << endl;
    inOut << "<!-- Incomplete -->" << endl;
}
