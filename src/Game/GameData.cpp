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
 * $Id: GameData.cpp,v 1.7 2002/06/27 12:36:06 southa Exp $
 * $Log: GameData.cpp,v $
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

GameData *GameData::m_instance=NULL;

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
        throw(GameDataNotPresent("Access to non-existent floormap '"+inName+"'"));
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
}    
