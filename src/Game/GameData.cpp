/*
 * $Id$
 * $Log$
 */

#include "GameData.h"
#include "GameTileMap.h"

GameData *GameData::m_instance=NULL;

GameData::~GameData()
{
    for (map<string, GameTileMap *>::iterator p = m_tilemaps.begin();
         p != m_tilemaps.end(); ++p)
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