/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class GameTileMap;

class GameData
{
public:
    ~GameData();
    static GameData& Instance(void) {return *((m_instance==NULL)?m_instance=new GameData:m_instance);}
    GameTileMap *TileMapGetOrCreate(const string& inName);
    GameTileMap *TileMapGet(const string& inName) const;
    // void Dump(ostream& inOut);

private:
    GameData() {}
    map<string, GameTileMap *> m_tilemaps;
    static GameData *m_instance;
};
