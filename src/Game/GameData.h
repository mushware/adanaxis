/*
 * $Id: GameData.h,v 1.1 2002/05/30 14:41:12 southa Exp $
 * $Log: GameData.h,v $
 * Revision 1.1  2002/05/30 14:41:12  southa
 * GameData and loadtilemap command
 *
 */

#include "mushCore.h"

class GameTileMap;
class GameFloorMap;
class GameContract;

class GameData
{
public:
    ~GameData();
    static GameData& Instance(void) {return *((m_instance==NULL)?m_instance=new GameData:m_instance);}
    GameTileMap *TileMapGetOrCreate(const string& inName);
    GameTileMap *TileMapGet(const string& inName) const;
    GameFloorMap *FloorMapGetOrCreate(const string& inName);
    GameFloorMap *FloorMapGet(const string& inName) const;
    GameContract *ContractGetOrCreate(const string& inName);
    GameContract *ContractGet(const string& inName) const;
    // void Dump(ostream& inOut);

private:
    GameData() {}
    map<string, GameTileMap *> m_tilemaps;
    map<string, GameFloorMap *> m_floormaps;
    map<string, GameContract *> m_contracts;
    static GameData *m_instance;
};
