/*
 * $Id: GameData.h,v 1.4 2002/06/04 20:27:37 southa Exp $
 * $Log: GameData.h,v $
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

#include "mushCore.h"

class GameTileMap;
class GameFloorMap;
class GameContract;
class GameTraits;
class GameController;
class GamePiece;

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
    GameTraits *TraitsDeleteAndCreate(const string& inName, GameTraits *inTraits);
    GameTraits *TraitsGet(const string& inName) const;
    GameController *ControllerGetOrCreate(const string& inName);
    GameController *ControllerGet(const string& inName) const;
    GamePiece *PieceDeleteAndCreate(const string& inName, GamePiece *inPiece);
    GamePiece *PieceGet(const string& inName) const;
    void DumpAll(ostream& inOut) const;

private:
    GameData() {}
    map<string, GameTileMap *> m_tilemaps;
    map<string, GameFloorMap *> m_floormaps;
    map<string, GameContract *> m_contracts;
    map<string, GameTraits *> m_traits;
    map<string, GameController *> m_controllers;
    map<string, GamePiece *> m_pieces;
    static GameData *m_instance;
};

class GameDataNotPresent: public exception
{
public:
    GameDataNotPresent(const string &inMessage) {m_message=inMessage;}
    ~GameDataNotPresent() throw() {}
    const string& StringGet(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    string m_message;
};

inline ostream& operator<<(ostream &s, GameDataNotPresent f)
{
    return s << f.StringGet();
}

