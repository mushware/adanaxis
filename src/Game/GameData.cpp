/*
 * $Id: GameData.cpp,v 1.1 2002/05/30 14:41:12 southa Exp $
 * $Log: GameData.cpp,v $
 * Revision 1.1  2002/05/30 14:41:12  southa
 * GameData and loadtilemap command
 *
 */

#include "GameData.h"
#include "GameTileMap.h"
#include "GameFloorMap.h"
#include "GameContract.h"

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
        throw(LogicFail("Access to non-existent tilemap '"+inName+"'"));
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
        throw(LogicFail("Access to non-existent floormap '"+inName+"'"));
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
        throw(LogicFail("Access to non-existent contract '"+inName+"'"));
    }
    return p->second;
}